#ifndef GRAPH_ADJ_LIST_H
#define GRAPH_ADJ_LIST_H
#include "Graph.h"
#include <map>
#include <vector>

namespace datalib{
	/**
	 * \class GraphAdjList
	 * \brief This class is a data structure for a graph,
	 * is implemented with Adjacency List tecnique .
	 * 
	 * Inherits from Graph class 
	 * \author Nico Fiorini
	*/

    template<class T>
    class GraphAdjList: public Graph<T> {
    private: 

        std::map<T,Node<T>*> adjList;
        Node<T>* private_addNode(const T &value); // todo vedere se è essenziale

    public:
        ///Default costructor for the GraphAdjList
        GraphAdjList(){}

        ///Costructor with a vector of Edge
        // GraphAdjList(const std::vector<Edge> &_edges);
        ///virtual Destructor
        virtual ~GraphAdjList(){}

        ///add a Node x in the graph
        void addNode(const T &value);

        int degree(const T &value){}
        ///add an Edge (x,y) in the graph
        void addEdge(const T &srcValue,const T &destValue);
        // void addEdge(const edge& _edge);
        void deleteNode(const T &value);                        //remove a Node in the graph
        void deleteEdge(const T &srcValue,const T &destValue);       //remove a Edge in the graph
        // void deleteEdge(const Edge &_edge);               //remove a Edge in the graph
		// int grade(const T &_x){}

        void getIncidentEdge(const T &value){}          //return the incident edge of the Node x
        void getAdjNode(const T &value){}

        void showStructure() const;
        void showNode() const;
        //void showGraphPos() const;
        void showGraphValue() const;
    };
}

#include "../sources/GraphAdjList.cpp"
#endif
