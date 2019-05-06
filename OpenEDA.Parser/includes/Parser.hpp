/**
 * @file Parser.hpp
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-01-02
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef Parser_hpp
#define Parser_hpp

#include "FaultStructures.hpp"
#include "TraceStructures.hpp"

#include <string>
#include <utility> //std::pair
#include <set>
#include <map>

#include "Circuit.h"
#include "Level.h"

#include <algorithm> //std::transform
#include <cctype> //std::tolower
#include <fstream> //File handeling. 
#include <string> //String, getline

 /*
  * An object which converts a text file into a Circuit object.
  *
  * A Parser takes a text string and processes the file it points to. After
  * processing, a circuit object can be returned.
  *
  * A Parser may have internal options which can be set, if necessary.
  *
  * The defaut (base) Parser takes a simple netlist format and returns a circuit
  * with simulation capibilities only.
  *
  * To add extra information at the time of parsing, change the virtual methods
  * (which create new Nodes and Lines) to create the appropriate type of
  * objects.
  */
template <class _lineType>
class Parser {
public:
	/*
	 * Parse a text file and return a Circuit.
	 *
	 * @param _filePath The path of the text file to parse.
	 * @return A new circuit object.
	 */
	Circuit* Parse(std::string _filePath);

private:
	/*
	 * Create a new Line from a given name.
	 *
	 * @param _name The name of the Line.
	 * @return The newly created Line.
	 */
	virtual Levelized* newLine(std::string _name);

	/*
	 * Create a new Node from the given information.
	 *
	 * @param _functionName The name of the function to create.
	 * @param _inputs Input lines to the given node. It is presumed these will be cast.
	 * @param _outputs Output lines of the given node. It is presumed these will be cast.
	 * @return The newly created Node.
	 */
	virtual Levelized* newNode(std::string _functionName, std::unordered_set<Levelized*> _inputs, std::unordered_set<Levelized*> _outputs);

	/*
	 * Adds a Line to the "Line tracking" data structure.
	 *
	 * @param _line The Line to add.
	 */
	void addLine(Levelized* _line);

	/*
	 * Convert a given line of into corresponding Lines and Nodes.
	 *
	 * @param _textLine A line of text to convert to Lines and Nodes./
	 * @return The number of Lines created.
	 */
	size_t ParseLine(std::string _textLine);

	/*
	 * Merge all Lines in the Circuit to be created.
	 *
	 * For all the lines in the "Line tracking" data structure, merge them through
	 * connecting and delecting.
	 */
	void MergeLines();

	/*
	 * A local copy of all PIs, which will eventually be used to create the Circuit.
	 */
	std::unordered_set<Levelized*> pis_;

	/*
	 * A local copy of all POs, which will eventually be used to create the Circuit.
	 */
	std::unordered_set<Levelized*> pos_;

	/*
	 * A local copy of all Nodes, which will eventually be used to create the Circuit.
	 */
	std::unordered_set<Levelized*> nodes_;

	/*
	 * A data structure used to keep track of (identical) Lines.
	 *
	 * The map is used to return all Lines matching a given name. The returned
	 * set is all Lines which match that name.
	 */
	std::map<std::string, std::set<Levelized*>> lines_;

	/*
	 * Clean all local storage (after parsing a file).
	 */
	void Clean();


};


/*
 * Split a string into a serries of sub-strings seperated by a set of deliminter characters.
 *
 * @param source The string to split.
 * @param delimiter One or more characters to split the string based off of.
 * @param keepEmpty Should "empty entries" be thrown away?
 * @return A vector of strings created after the string is split.
 */
std::vector<std::string> StringToTokins(const std::string &source, const char *delimiter, bool keepEmpty) {
	std::vector<std::string> results;

	size_t prev = 0;
	size_t next = 0;

	while ((next = source.find_first_of(delimiter, prev)) != std::string::npos) {
		if (keepEmpty || (next - prev != 0)) {
			results.push_back(source.substr(prev, next - prev));
		}
		prev = next + 1;
	}

	if (prev < source.size()) {
		results.push_back(source.substr(prev));
	}

	return results;
}

template <class _lineType>
Circuit * Parser<_lineType>::Parse(std::string _filePath) {
	//Open the file.
	std::string currentLine;
	std::ifstream file(_filePath);
	if (file.is_open() == false) { throw "Failed to open file for parsing."; }
	while (std::getline(file, currentLine)) {
		this->ParseLine(currentLine);
	}
	file.close();
	this->MergeLines();

	Circuit* toReturn = new Circuit(this->nodes_, this->pis_, this->pos_);
	this->Clean();

	return toReturn;
}

template <class _lineType>
Levelized * Parser<_lineType>::newLine(std::string _name) {
	return new _lineType(_name);
}

template <class _lineType>
Levelized * Parser<_lineType>::newNode(std::string _functionName, std::unordered_set<Levelized*> _inputs, std::unordered_set<Levelized*> _outputs) {
	Function<bool>* function;
	if (
		!_functionName.compare("copy") ||
		!_functionName.compare("pi") ||
		!_functionName.compare("po") ||
		!_functionName.compare("const")
		) {
		function = new CopyFunction<bool>(_functionName);
	}
	else {
		function = new BooleanFunction(_functionName);
	}
	std::unordered_set <SimulationLine<bool>*> inputs;
	std::unordered_set <SimulationLine<bool>*> outputs;
	for (Levelized* input : _inputs) {
		inputs.emplace(dynamic_cast<SimulationLine<bool>*>(input));
	}
	for (Levelized* output : _outputs) {
		outputs.emplace(dynamic_cast<SimulationLine<bool>*>(output));
	}
	Levelized* newNode = new SimulationNode<bool>(function, inputs, outputs);
	return newNode;
}

template <class _lineType>
void Parser<_lineType>::addLine(Levelized * _line) {
	std::string name = _line->name();
	if (lines_.count(name) == 0) {//Name is not in use yet.
		lines_[name] = std::set<Levelized*>({ _line });
	}
	else {
		lines_.at(name).emplace(_line);
	}
}

template <class _lineType>
size_t Parser<_lineType>::ParseLine(std::string _textLine) {
	//Reminder: the line format:
	//  #comment
	//  GATE_NAME = PRIMITIVE(INPUT1, INPUT2, ... INPUTX)
	//  INPUT(GX)
	//  OUTPUT(GX)
	std::vector<std::string> tokins = StringToTokins(_textLine, " (,)=\r", false);
	if (tokins.size() == 0) { //Blank line.
		return 0;
	}
	if (!tokins.at(0).compare("#")) { //Comment
		return 0;
	}
	if (!tokins.at(0).compare("OUTPUT") || !tokins.at(0).compare("INPUT")) { //WE HAVE AN OUTPUT/INPUT
		std::string name = tokins.at(1);
		Levelized* line = this->newLine(name);
		this->addLine(line);
		if (!tokins.at(0).compare("OUTPUT")) { //po
			Levelized* newNode = this->newNode("po", std::unordered_set<Levelized*>({ line }), std::unordered_set<Levelized*>());
			pos_.emplace(newNode);
			nodes_.emplace(newNode);
			line->addOutput(newNode);
		}
		else { //pi
			Levelized* newNode = this->newNode("pi", std::unordered_set<Levelized*>(), std::unordered_set<Levelized*>({ line }));
			pis_.emplace(newNode);
			nodes_.emplace(newNode);
			line->addInput(newNode);
		}
		return 1;
	}
	else { //WE HAVE A GENERIC NODE
		std::string nodeFunctionName = tokins.at(1); std::transform(nodeFunctionName.begin(), nodeFunctionName.end(), nodeFunctionName.begin(), (int(*)(int))std::tolower);
		Levelized* outputLine = this->newLine(tokins.at(0));
		this->addLine(outputLine);
		std::unordered_set<Levelized*> intputLines;
		for (size_t i = 2; i < tokins.size(); ++i) {
			std::string inputLineName = tokins.at(i);
			Levelized* inputLine = this->newLine(inputLineName);
			this->addLine(inputLine);
			intputLines.emplace(inputLine);
		}

		Levelized* newNode = this->newNode(nodeFunctionName, intputLines, std::unordered_set<Levelized*>({ outputLine }));
		this->nodes_.emplace(newNode);

		return intputLines.size() + 1;
	}
}


template <class _lineType>
void Parser<_lineType>::MergeLines() {
	for (auto it = lines_.begin(); it != lines_.end(); ++it) {
		std::string lineName = it->first;
		std::set<Levelized*> lines = it->second;
		Levelized* base = nullptr;
		for (Levelized* line : lines) {
			if (line->outputs().size() == 0) { base = line; lines.erase(line); break; }
		}
		if (base == nullptr) { throw "Could not merge lines: there is no base."; }
		if (lines.size() == 0) { throw "Not enough lines to do a merge, which should not happen."; }
		if (lines.size() == 1) { //Same non-fanout line, so delete.
			Levelized* toDelete = *lines.begin();
			base->addOutput(*toDelete->outputs().begin());
			delete toDelete; //This will automatically delete its connections.
			continue;
		}
		//All other lines are fanouts.
		for (auto otherLineIterator = lines.begin(); otherLineIterator != lines.end(); ++otherLineIterator) {
			base->addOutput(*otherLineIterator);
		}
	}
}

template <class _lineType>
void Parser<_lineType>::Clean() {
	pis_.clear();
	pos_.clear();
	nodes_.clear();
	lines_.clear();
}

#endif
