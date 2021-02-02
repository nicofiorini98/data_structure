#pragma once 

#include <iostream>
#include "Graph.h"
#include <vector>

using namespace std;

//stores adjacency list items


class AdjacencyList{
private: 
public: 

    vector<vector<Node>> adjList; 
    //constructor
    AdjacencyList(vector<Edge> const &_edges,int N){
        // resize the vector to N elements of type vector<int>
        adjList.resize(N);
 
        for(auto &edge:_edges){
            //insert at the end
            //std::cout<<"boh che succede\n";
//            std::cout<<edge.src.key<<"\n";
            adjList[edge.src.key].push_back(edge.dest);  //TODO RIVEDERE 
            //praticamente sto a di che al nodo con quella chiave inserisco il nodo dest

            // Uncomment below line for undirected graph
            // adjList[edge.dest].push_back(edge.src);
        }
    }
};


 // print adjacency list representation of graph
void printGraph(AdjacencyList const& graph, int N)
{
    int i=0;
    for (auto &node: graph.adjList )
    {
        // print current vertex number
        cout << i << " --> ";
        // print all neighboring vertices of vertex i
        for(auto &neighboor: node){
            std::cout<<neighboor.key;
        }
        i++;
        
        cout << endl;
    }
}
