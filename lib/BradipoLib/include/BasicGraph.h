#ifndef BASIC_GRAPH_H
#define BASIC_GRAPH_H
#pragma once

#include "Edge.h"
#include "Node.h"
#include <iostream>

namespace datalib {

/**
 * \class Graph
 * \brief This is abstract Class, is a base class for Tree and graph.
 * \author Nico Fiorini
 * \date 02/03/2021
 */

template <class T> class BasicGraph {
  protected:
	  int numNodes;
    char delimiter = ',';

  public:
    BasicGraph() {
		  numNodes = 0;	
    }

    /// virtual destructor
    virtual ~BasicGraph() {}

    /// return the number of the Node in the graph
    int getNumNode() { return numNodes; }
    
    /// set Delimiter Input File
    virtual void setDelimiterFile(const char delimiter){this->delimiter = delimiter;}
	
    /// return the value in the object based to the value passed
	  virtual T getValue(const T& nodeValue) const = 0;
	
    /// change the node in the object structure from oldValue to newValue
	  virtual void setValue(const T& oldValue,const T& newValue) = 0;

    ///Output with dot 
    virtual std::ostream &outputDotFile(std::ostream &dotFile) const = 0;
    
  };
} // namespace datalib

#endif
