/*#pragma once

#include <iostream>
#include "Graph.h"
#include <vector>
#include <list>
#include <iterator>


//stores adjacency list items
using list_list_itr =  std::list<std::list<Node>>::iterator ;


class AdjacencyList: public Graph{
private:
    std::list<std::list<Node>> adjLists;
public:
    
    //constructor
    AdjacencyList(std::vector<Edge> const &_edges);

    void addNode(Node x);                //add a Node 
    void addEdge(Node x,Node y);        //add an Edge
    int grade(Node x);
    
    //GETTER 
    //return an iterator that point in an adjList of a Node x
    list_list_itr getList(Node x) ;

    bool hasNode(const Node &x);

    void showGraph() const;

};


*/
