/**
 * @file Level.h
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2018-12-23
 *
 * @copyright Copyright (c) 2018
 *
 */

#ifndef Level_h
#define Level_h

#include <unordered_map>
#include <unordered_set>
#include <limits>

#include "Connection.h"

/*
 * This class models objects which are levelelized.
 *
 * This class is for structures where the arangement of Connecting objects
 * implies a "level" relative to a given object is craeted. This is most likely
 * applied to Verticies relative directed-graph objects.
 */
class Levelized : public virtual Connecting {
public:
	
	/*
	 * Create an object which are connected to other Levelized objects.
	 *
	 * @param (optional) _inputs A vector of input Levelized objects.
	 * @param (optioanl) _outputs A vector of output Levelized objects.
	 * @param (optional) _name Name of the connection (defaults to empty strying).
	 */
	Levelized(std::unordered_set<Levelized*> _inputs = std::unordered_set<Levelized*>(),
			  std::unordered_set<Levelized*> _outputs = std::unordered_set<Levelized*>(),
			  std::string _name = ""
	);

	/*
	 * Calculate and return the input level.
	 *
	 * If the level is not defined, it will be caclulated through a recursive
	 * depth-first search.
	 *
	 * If the level cannot be calculated because no "root" is defined,
	 * an error will be thrown.
	 *
	 * @return The input level of the object.
	 */
	int inputLevel();

	/*
	 * Calculate and return the input level.
	 *
	 * If the level is not defined, an exception will be thrown.
	 * @return The input level of the object.
	 */
	int inputLevelConst() const;

	/*
	 * Clear (set to unknown) this object's input level and all levels which depend on this level.
	 *
	 * This function uses a depth-first search algorithm to clear levels.
	 */
	void inputLevelClear();

	/*
	 * Set this object's input level to "zero".
	 */
	void inputLevelZero();

	/*
	 * Calculate and return the output level.
	 *
	 * If the level is not defined, it will be caclulated through a recursive
	 * depth-first search.
	 *
	 * If the level cannot be calculated because no "root" is defined,
	 * an error will be thrown.
	 *
	 * @return The output level of the object.
	 */
	int outputLevel();

	/*
	 * Calculate and return the output level of this object.
	 *
	 * If the level is not defined, an exception will be thrown.
	 *
	 * @return The output level of the object.
	 */
	int outputLevelConst() const;

	/*
	 * Clear (set to unknown) this object's output level and all levels which depend on this level.
	 *
	 * This function uses a depth-first search algorithm to clear levels.
	 *
	 */
	void outputLevelClear();

	/*
	 * Set this object's output level to "zero".
	 *
	 */
	void outputLevelZero();



	/*
	 * This constant is assigned as the level for objects with no defined
	 * level.
	 */
	const int UNKNOWN_LEVEL = -1;



private:
	

	/*
	 * The object's input level.
	 */
	int inputLevel_;

	/*
	 * The object's output level.
	 */
	int outputLevel_;

	/*
	 * Based on a vector of given level values, return the Level of this object.
	 * 
	 * @param _levels Level values to calculated based on.
	 * @return The calculated level value.
	 */
	virtual int levelCalculation(std::vector<int> _levels);

protected:

	/*
	 * Delete a given input connection
	 *
	 * The given input connection will be removed. If it does not exist, an
	 * exception will be thrown.
	 *
	 * @param The input connection to remove.
	 */
	virtual void removeInputConnection(Connection* _rmv, bool _deleteConnection = true);

	/*
   * Delete a given output connection
   *
   * The given output connection will be removed. If it does not exist, an
   * exception will be thrown.
   *
   * @param The output connection to remove.
   */
	virtual void removeOutputConnection(Connection* _rmv, bool _deleteConnection = true);

	/*
   * Add a given input connection
   *
   * @param Input connection to add
   */
	virtual void addInputConnection(Connection* _add);

	/*
	 * Add a given output connection
	 *
	 * @param Output connection to add
	 */
	virtual void addOutputConnection(Connection* _add);
};
#endif