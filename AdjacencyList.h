#pragma once

#include <iostream>
#include "Graph.h"
#include <vector>
#include <list>
#include <iterator>


//stores adjacency list items


class AdjacencyList{
private:
public:

    std::list<std::list<Node>> adjLists;
    
    //constructor
    AdjacencyList(std::vector<Edge> const &_edges,int N){

        for(auto &edge: _edges){
            //if the adjList don't have the src node then add the adjList in the adjLists
            std::list<std::list<Node>>::iterator it=getList(edge.src);

            //add node lists if it doesn't exist else add an edge in the list of the node 
            if(it==adjLists.end()){
                adjLists.push_back({edge.src,edge.dest});
            }
            else{
                (*it).push_back({edge.dest});
            } 
        }
    }

    //return an iterator that point in an adjList of a Node x
    std::list<std::list<Node>>::iterator getList(Node x){

        std::list<std::list<Node>>::iterator it;
        for(it=adjLists.begin();it!=adjLists.end();it++)
            if((*(*it).begin()).value==x.value)
                return it;

        return it;
    }

    bool hasNode(const Node &x){

         std::list<std::list<Node>>::iterator list_it;

         //return true if the node will found in the first 
         for(auto& adjList: adjLists)
         {
             if((*(adjList.begin())).value==x.value)
                 return true;
             return false;
         }
         return false;
    }

};


 // print adjacency list representation of graph
void printGraph(AdjacencyList const& graph, int N)
{
    for (auto &node: graph.adjLists )
    {
        // print current vertex number
        std::cout << (*node.begin()).value << " --> ";
        // print all neighboring vertices of vertex i
        for(std::list<Node>::const_iterator it=(node.begin())++;it!=node.end();it++){
            std::cout<<(*it).value<<" ";
        }
        /*for(auto &neighboor: node){
            std::cout<<neighboor.value;
        }
        */
        
        std::cout << std::endl;
    }
}

