#ifndef BASIC_GRAPH_H
#define BASIC_GRAPH_H
#pragma once

#include "Edge.h"
#include "Node.h"
#include <iostream>

namespace  slothLib {

/**
 * \class BasicGraph
 * \brief This is an abstract class, it is the base class for all trees and graphs.
 * \author Nico Fiorini
 * \date 10/10/2023
 */

template <class T> class BasicGraph {
  protected:
    /**@brief number of nodes in the graph*/
	  int numNodes;
    /**@brief delimiter character for the input*/
    char delimiter = ',';

  public:
    
    /// Costructor
    BasicGraph() {
		  numNodes = 0;	
    }

    /// virtual destructor
    virtual ~BasicGraph() {}

    /**
     * @brief Return the number of nodes contained in the Graph.
     */
    int getNumNode() { return numNodes; }
    
    /**
     * @brief Set delimiter for input file.
     * @param delimiter delimiter character for input file.
     */
    virtual void setDelimiterFile(const char delimiter){this->delimiter = delimiter;}
	
    /// return the value in the object based to the value passed
    /**
     * @brief Return the value passed by parameter contained in the Graph
     * @param nodeValue is the parameter to search and return from the Graph.
     * @note Uniqueness is based on comparison operators.
    */
	  virtual T getValue(const T& nodeValue) const = 0;
	
    /**
     * @brief Change the value of the node OldValue with the newValue.
     * @param oldValue the value to search and change.
     * @param newValue the new value to change with the old value.
    */
	  virtual void setValue(const T& oldValue,const T& newValue) = 0;

    /**
     * @brief Write in the stream in dot language to visualize with Graphviz software.
     * @param dotFile The stream to write in dot language.
    */
    virtual std::ostream &outputDotFile(std::ostream &dotFile) const = 0;
    
  };
}

#endif
