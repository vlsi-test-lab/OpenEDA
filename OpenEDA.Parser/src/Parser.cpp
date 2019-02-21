/**
 * @file Parser.cpp
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-01-02
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "Parser.h"

#include <algorithm> //std::transform
#include <cctype> //std::tolower
#include <fstream> //File handeling. 
#include <string> //String, getline

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

Circuit * Parser::Parse(std::string _filePath) {
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

Levelized * Parser::newLine(std::string _name) {
	return new FaultyLine<bool>(_name);
}

Levelized * Parser::newNode(std::string _functionName, std::unordered_set<Levelized*> _inputs, std::unordered_set<Levelized*> _outputs) {
	Function<bool>* function;
	if (
		!_functionName.compare("copy") || 
		!_functionName.compare("pi") ||
		!_functionName.compare("po") ||
		!_functionName.compare("const")
		) {
		function = new CopyFunction<bool>(_functionName);
	} else {
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

void Parser::addLine(Levelized * _line) {
	std::string name = _line->name();
	if (lines_.count(name) == 0) {//Name is not in use yet.
		lines_[name] = std::set<Levelized*>({ _line });
	} else {
		lines_.at(name).emplace(_line);
	}
}

size_t Parser::ParseLine(std::string _textLine) {
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
		} else { //pi
			Levelized* newNode = this->newNode("pi", std::unordered_set<Levelized*>(), std::unordered_set<Levelized*>({ line }));
			pis_.emplace(newNode);
			nodes_.emplace(newNode);
			line->addInput(newNode);
		}
		return 1;
	} else { //WE HAVE A GENERIC NODE
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

void Parser::MergeLines() {
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

void Parser::Clean() {
	pis_.clear();
	pos_.clear();
	nodes_.clear();
	lines_.clear();
}
