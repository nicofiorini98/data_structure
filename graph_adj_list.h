#pragma once
#include "graph.h"
#include <map>
#include <vector>

namespace datalib{


	/**
	 * \class GraphAdjList
	 * \brief This class is a data structure for a graph,
	 * is implemented with Adjacency List.
	 * 
	 * Inherits from Graph class 
	 * An AdjList is ideal for Breadth-first search
	 * and Depth-first search. 
	 * \author Nico Fiorini
	 */
    template<class T>
    class graph_adj_list: public graph
    {
    private: 
        std::map<T,node<T>*>> adj_lists;   
    public:
        ///Default costructor for the GraphAdjList
        graph_adj_list(): graph(){}

        ///Costructor with a vector of Edge
        // graph_adj_list(const std::vector<Edge> &_edges);
        ///virtual Destructor
        virtual ~graph_adj_list(){} 

        ///add a Node x in the graph
        void addNode(const node<T> &x);
        ///add an Edge (x,y) in the graph
        void addEdge(const node<T> &x,const node<T> &y);
        // void addEdge(const Edge& _edge);
        void deleteNode(const node<T> &x);                             //remove a Node in the graph
        void deleteEdge(const node<T> &x,const node<T> &y);               //remove a Edge in the graph
        // void deleteEdge(const Edge &_edge);               //remove a Edge in the graph
        int grade(const node<T> &x){}
		
        void getIncidentEdge(const node<T> &x){}          //return the incident edge of the Node x
        void getAdjNode(const node<T> &x){}

        void showGraph() const;
        //void showGraphPos() const;
        void showGraphValue() const;
    };

    #include "graph_adj_list.cpp";

}