/**
 * @file Connection.h
 * @author Joshua Immanuel (jzi0005@tigermail.auburn.edu)
 * @author Spencer Millican (millican@auburn.edu)
 * @version 0.1
 * @date 2018-12-21
 *
 * @copyright Copyright (c) 2018
 *
 */

#ifndef Connection_h
#define Connection_h

#include <unordered_set>
#include <string>

class Connecting;
class Connection;

/**
 * This class models any object which connects to other objects through
 * Connections.
 *
 * The Connecting class is not intended to be used as a stand-alone class. This
 * class is indendtended to be inherited by objects which desire for connections
 * to be made to other Connecting objects. Therefore, this class is best
 * referred to as a "feature" of other classes.
 *
 * Connections must be directional, i.e., an object can have input and output
 * Connections, but not Connections of an unspecified direction.
 *
 * A Connecting class can have any number of input/output Cconnections.
 * Connections can be added and removed.
 *
 */
class Connecting {
 public:
  /*
   * Create a Connecting class with no Connections.
   *
   * By default, when a new connecting object is created, it will connect to
   * nothing.
   *
   * The name will be an empty string.
   */
  Connecting();

  /*
   * Create a Connecting object with Connections to the given Connecting objects.
   *
   * With this constructor, the Connections are implied, and therefore the 
   * Connections will be created "on-the-fly".
   *
   * @param inputs A vector of input Connecting objects.
   * @param outputs A vector of output Connecting objects.
   * @param (optional) _name Name of the connection (defaults to empty strying).
   */
  Connecting(std::unordered_set<Connecting*> _inputs,
             std::unordered_set<Connecting*> _outputs,
			 std::string _name = ""
  );

  /*
   * Upon destruction, destroy all connections.
   *
   * When a Connecting object is destroyed, all Connections will be destroyed.
   * This will in turn remove all Connections to input/ouput objects.
   */
  ~Connecting();

  /**
   * Get all the input Connecting objects.
   *
   * @return A vector of all objects which connect to this object through an 
   *         input Connection.
   */
  virtual std::unordered_set<Connecting*> inputs() const;

  /*
   * Set the inputs of this object to the given objects.
   *
   * @param  _inputs A set of objects to be input Connections.
   * @return A set of all objects which connect to this object through an 
   *         input Connection.
   */
  virtual std::unordered_set<Connecting*> inputs(std::unordered_set<Connecting*> _inputs) ;

  /**
   * Get all the output Connecting objects.
   *
   * @return A vector of all objects which connect to this object through an
   *         output connection.
   */
  virtual std::unordered_set<Connecting*> outputs() const;

  /*
   * Set the outputs of this object to the given objects.
   *
   * @param  _inputs A set of objects to be output Connections.
   * @return A set of all objects which connect to this object through an
   *         output Connection.
   */
  virtual std::unordered_set<Connecting*> outputs(std::unordered_set<Connecting*> _outputs);

  /*
   * Delete the input Connection which connects the given input object.
   *
   * If the Connection cannot be found, an exception will be thrown.
   *
   * @param The input Connecting object to be disconnected.
   */
  void removeInput(Connecting* _rmv);

  /*
   * Delete the output COnnection which connects the given input object.
   *
   * If the Connection cannot be found, an exception will be thrown.
   *
   * @param The output Connecting object to be disconnected.
   */
  void removeOutput(Connecting* _rmv);

  /*
   * Add a given input Connecting object using a new Connection.
   *
   * @param Input Connecting object to connect to.
   */
  virtual void addInput(Connecting* _add);

  /*
 * Add a given output Connecting object using a new Connection.
 *
 * @param Output Connecting object to connect to.
 */
  virtual void addOutput(Connecting* _add);

  /*
   * Return the name of this levelized object.
   *
   * @return This object's name.
   */
  std::string name() const;


private:

  /**
   * This vector contains all the input connections.
   */
  std::unordered_set<Connection*> inputs_;

  /**
   * This vector contains all the output connections.
   */
  std::unordered_set<Connection*> outputs_;

  /*
   * The name of this connection.
   */
  std::string name_;

  /**
   * The Connection class is a friend. It is the only class which can add/remove
   * itself using private functions.
   */
  friend Connection;

  /*
 * Delete a given input connection
 *
 * The given input connection will be removed. If it does not exist, an
 * exception will be thrown.
 *
 * @param The input connection to remove.
 */
  void removeInput(Connection* _rmv);

  /*
 * Delete a given output connection
 *
 * The given output connection will be removed. If it does not exist, an
 * exception will be thrown.
 *
 * @param The output connection to remove.
 */
  void removeOutput(Connection* _rmv);

  /*
 * Add a given input connection
 *
 * @param Input connection to add
 */
  void addInput(Connection* _add);

  /*
   * Add a given output connection
   *
   * @param Output connection to add
   */
  void addOutput(Connection* _add);
};

/**
 * This class models a connection between two objects, i.e., an input object and
 * an output object.
 *
 * This class models a connection between two arbitrary memory elements. One
 * memory element must be an "input" and the other must be an "output", i.e.,
 * this connection is directional.
 *
 * Every connection must have an input and an output, i.e., an "end" connection
 * is not a valid object.
 *
 * The objects to be connected must have the "Connecting" feature, i.e., they
 * must inherit from the "Connecting" class.
 *
 * Once a connection is created, it cannot be changed, i.e., it's input and
 * output cannot be changed.
 *
 * When a Connection is created, the input/output will automatically have 
 * knowledge that it is driving this object.
 *
 * When a connection is deleted, the Connecting input/output wil be called to
 * remove this connection.
 *
 */
class Connection {
 public:
  /*
   * Throw an exception. It is not valid to create a non-connecting Connection.
   *
   * It is not valid to create a non-connecting connection. An exception will be
   * thrown.
   */
  Connection();

  /**
   * Create a new Connection Object with a given input and output.
   *
   * A newConnection will be created for the two given objects.
   *
   * Both objects to be connected must inherit from the Connecting feature.
   *
   * Non-objects (nullptrs) will not be accepted.
   *
   * @param input - A pointer to the input of the Connection.
   * @param output - A pointer to the output of the Connection.
   */
  Connection(Connecting * _input, Connecting * _output);

  /**
   * Destroys the Connecting and removes this Connection from the input/output.
   *
   * When a Connection is destroyed, the input/output Connecting objects will
   * be called upon to remove this connection.
   */
  ~Connection();

  /**
   * Get the input of the Connection.
   *
   * This function returns a pointer the input of this Connection
   *
   * @return The input Connecting object to this Connection.
   */
  Connecting* input() const;

  /**
   * Get the output of the Connection.
   *
   * This function returns a pointer the output of this Connection
   *
   * @return The output Connecting object to this Connection.
   */
  Connecting* output() const;

 private:
  /**
   * A pointer to the input Connecting object.
   *
   * This is a pointer to the input connecting object. This may not be a
   * nullptr.
   *
   */
  Connecting* input_;

  /**
   * A pointer to the input Connecting object.
   *
   * This is a pointer to the output  connecting object. This may not be a
   * nullptr.
   *
   */
  Connecting* output_;
};

#endif