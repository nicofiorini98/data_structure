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

  public:
    BasicGraph() {
		  numNodes=0;	
    }

    virtual ~BasicGraph() {}

    /// return the number of the Node in the graph
    int getNumNode() { return numNodes; }
	
	  // virtual T getValue(T key){std::cout<<key<<"\n";}
	
	  virtual void setValue(const T oldValue,const T& newValue) = 0;
    
    virtual void markNode(const T &value, marking mark) = 0;

};
} // namespace datalib

#endif
