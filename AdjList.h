#include "Graph.h"
#include <iostream>
#include <list>
#include <vector>
#include <utility>
#include <string>




class AdjList: public Graph
{
private:
    
    std::vector<std::list<Node>> adj_lists;
    void generate_key(int start=0);
    int grade(int pos);

public:
    
    //constructor
    AdjList(std::vector<Edge> const &_edges);
    
    void addNode(const Node &x);                //add a Node 
    void addEdge(const Node &x,const Node &y);        //add an Edge
    int grade(const Node &x){}

    void getIncidentEdge(const Node &x);          //return the incident edge of the Node x
    
    void getAdjNode(const Node &x); 

    //GETTER 
    //return an iterator that point in an adjList of a Node x
    std::vector<std::list<Node>>::iterator getList(const Node &x) ;


    void showGraph() const;

};






