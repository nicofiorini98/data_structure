/*#pragma once 

#include <iostream>
#include <list>
#include "utility.h"
#include "Graph.h"
#include <vector>


class EdgeList: public Graph{
private:
    std::vector<Node*> nodes;
    std::list<Edge> edges;

public:
    EdgeList();
    EdgeList(std::list<Edge> _edges);
    ~EdgeList();


};

EdgeList::EdgeList(){
    nodes.push_back(new Node(3));    
    nodes.push_back(new Node(4));    
    edges.push_back(Edge(nodes[0],nodes[1]));

}

EdgeList::EdgeList(std::list<Edge>_edges){
}

void EdgeList::addEdge(Node* x,Node* y){

}
*/

