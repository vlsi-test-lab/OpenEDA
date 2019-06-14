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

#include <string>
#include <utility> //std::pair
#include <set>
#include <map>

#include "Circuit.h"
#include "Level.h"
#include "Function.h"

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
  *
  * @param _lineType The line type to create during parsing. The line type must
  *                  have a constructor which takes a string for a name and
  *                  nothing else.
  * @param _nodeType The node type to create during parsing. This node type
  *                  must have a constructor which takes in a Function
  *                  pointer, a set of _lineTypes for inputs, and a set of 
  *                  _lineTypes for outputs.
  */
template <class _lineType, class _nodeType>
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
	virtual _lineType* newLine(std::string _name);

	/*
	 * Create a new Node from the given information.
	 *
	 * @param _functionName The name of the function to create.
	 * @param _inputs Input lines to the given node. It is presumed these will be cast.
	 * @param _outputs Output lines of the given node. It is presumed these will be cast.
	 * @return The newly created Node.
	 */
	virtual _nodeType* newNode(std::string _functionName, std::unordered_set<_lineType*> _inputs, std::unordered_set<_lineType*> _outputs);

	/*
	 * Adds a Line to the "Line tracking" data structure.
	 *
	 * @param _line The Line to add.
	 */
	void addLine(_lineType* _line);

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
	std::unordered_set<_nodeType*> pis_;

	/*
	 * A local copy of all POs, which will eventually be used to create the Circuit.
	 */
	std::unordered_set<_nodeType*> pos_;

	/*
	 * A local copy of all Nodes, which will eventually be used to create the Circuit.
	 */
	std::unordered_set<_nodeType*> nodes_;

	/*
	 * A data structure used to keep track of (identical) Lines.
	 *
	 * The map is used to return all Lines matching a given name. The returned
	 * set is all Lines which match that name.
	 */
	std::map<std::string, std::set<_lineType*>> lines_;

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

template <class _lineType, class _nodeType>
Circuit * Parser<_lineType, _nodeType>::Parse(std::string _filePath) {
	//Open the file.
	std::string currentLine;
	std::ifstream file(_filePath);
	if (file.is_open() == false) { throw "Failed to open file for parsing."; }
	while (std::getline(file, currentLine)) {
		this->ParseLine(currentLine);
	}
	file.close();
	this->MergeLines();

	std::unordered_set<Levelized*> nodes = std::unordered_set<Levelized*>(this->nodes_.begin(), this->nodes_.end());
	std::unordered_set<Levelized*> pis = std::unordered_set<Levelized*>(this->pis_.begin(), this->pis_.end());
	std::unordered_set<Levelized*> pos = std::unordered_set<Levelized*>(this->pos_.begin(), this->pos_.end());
	Circuit* toReturn = new Circuit(nodes, pis, pos);
	this->Clean();

	return toReturn;
}

template <class _lineType, class _nodeType>
_lineType * Parser<_lineType, _nodeType>::newLine(std::string _name) {
	return new _lineType(_name);
}

template <class _lineType, class _nodeType>
_nodeType * Parser<_lineType, _nodeType>::newNode(std::string _functionName, std::unordered_set<_lineType*> _inputs, std::unordered_set<_lineType*> _outputs) {
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
	_nodeType* newNode = new _nodeType(function, _inputs, _outputs);
	return newNode;
}

template <class _lineType, class _nodeType>
void Parser<_lineType, _nodeType>::addLine(_lineType * _line) {
	std::string name = _line->name();
	if (lines_.count(name) == 0) {//Name is not in use yet.
		lines_[name] = std::set<_lineType*>({ _line });
	}
	else {
		lines_.at(name).emplace(_line);
	}
}

template <class _lineType, class _nodeType>
size_t Parser<_lineType, _nodeType>::ParseLine(std::string _textLine) {
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
		_lineType* line = this->newLine(name);
		this->addLine(line);
		if (!tokins.at(0).compare("OUTPUT")) { //po
			_nodeType* newNode = this->newNode("po", std::unordered_set<_lineType*>({ line }), std::unordered_set<_lineType*>());
			pos_.emplace(newNode);
			nodes_.emplace(newNode);
			line->addOutput(newNode);
		}
		else { //pi
			_nodeType* newNode = this->newNode("pi", std::unordered_set<_lineType*>(), std::unordered_set<_lineType*>({ line }));
			pis_.emplace(newNode);
			nodes_.emplace(newNode);
			line->addInput(newNode);
		}
		return 1;
	}
	else { //WE HAVE A GENERIC NODE
		std::string nodeFunctionName = tokins.at(1); std::transform(nodeFunctionName.begin(), nodeFunctionName.end(), nodeFunctionName.begin(), (int(*)(int))std::tolower);
		_lineType* outputLine = this->newLine(tokins.at(0));
		this->addLine(outputLine);
		std::unordered_set<_lineType*> intputLines;
		for (size_t i = 2; i < tokins.size(); ++i) {
			std::string inputLineName = tokins.at(i);
			_lineType* inputLine = this->newLine(inputLineName);
			this->addLine(inputLine);
			intputLines.emplace(inputLine);
		}

		_nodeType* newNode = this->newNode(nodeFunctionName, intputLines, std::unordered_set<_lineType*>({ outputLine }));
		if (intputLines.size() != newNode->inputs().size() || newNode->outputs().size() != 1) {
			throw "Your _nodeType constructor is flawed: it most likely needs to call 'Connecting'.";
		}

		//If you need the followign code, your _nodeType needs to call "Connecting" in its constructor.
		//for (_lineType* inputLine : intputLines) {
		//	inputLine->addOutput(newNode);
		//}

		this->nodes_.emplace(newNode);
		
		return intputLines.size() + 1;
	}
}


template <class _lineType, class _nodeType>
void Parser<_lineType, _nodeType>::MergeLines() {
	for (auto it = lines_.begin(); it != lines_.end(); ++it) {
		std::string lineName = it->first;
		std::set<_lineType*> lines = it->second;
		_lineType* base = nullptr;
		for (_lineType* line : lines) {
			if (line->outputs().size() == 0) { base = line; lines.erase(line); break; }
		}
		if (base == nullptr) { throw "Could not merge lines: there is no base."; }
		if (lines.size() == 0) { printf("WARNING: A line in circuit doesn't drive anything \n");
		}
		if (lines.size() == 1) { //Same non-fanout line, so delete.
			_lineType* toDelete = *lines.begin();
			if(toDelete->outputs().size() == 0){//Sanity check, this should not happen
				throw "Problem: multiple lines have no output.";
			}
			base->addOutput(*toDelete->outputs().begin());
			toDelete->outputs(std::unordered_set<Connecting*>()); //This shouldn't be necessary, but was added in order to clear COP values consistently.
			toDelete->inputs(std::unordered_set<Connecting*>());
			delete toDelete; //This will automatically delete its connections.
			continue;
		}
		//All other lines are fanouts.
		for (auto otherLineIterator = lines.begin(); otherLineIterator != lines.end(); ++otherLineIterator) {
			base->addOutput(*otherLineIterator);
		}
	}
}

template <class _lineType, class _nodeType>
void Parser<_lineType, _nodeType>::Clean() {
	pis_.clear();
	pos_.clear();
	nodes_.clear();
	lines_.clear();
}

#endif
