#include "Graph.h"
#include <iostream>
#include <list>
#include <vector>
#include <utility>
#include <string>



class AdjList{
private:
    std::vector<std::list<Node>> adj_lists;
    void generate_key(int start=0);
    int grade(int pos);
public:
    
    //constructor
    AdjList(std::vector<Edge> const &_edges);

    void addNode(Node x);                //add a Node 
    void addEdge(Node x,Node y);        //add an Edge
    int grade(Node x);
    
    //GETTER 
    //return an iterator that point in an adjList of a Node x
    std::vector<std::list<Node>>::iterator getList(Node x) ;

//    bool hasNode(const Node &x);

    void showGraph() const;

};






