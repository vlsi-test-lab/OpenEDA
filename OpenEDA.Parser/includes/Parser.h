/**
 * @file Parser.h
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2019-01-02
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef Parser_h
#define Parser_h

#include "SimulationStructures.hpp"
#include "TraceStructures.hpp"

#include <string>
#include <utility> //std::pair
#include <set>
#include <map>

#include "Circuit.h"
#include "Level.h"

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

#endif