#pragma once

#include <iostream>
#include "Graph.h"
#include <vector>
#include <list>
#include <iterator>


//stores adjacency list items


class AdjacencyList{
private:
    std::list<std::list<Node>> adjLists;
public:
    
    //constructor
    AdjacencyList(std::vector<Edge> const &_edges);
    
    //return an iterator that point in an adjList of a Node x
    std::list<std::list<Node>>::iterator getList(Node x);

    bool hasNode(const Node &x);

    void showGraph();

};



