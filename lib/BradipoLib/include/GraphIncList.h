#ifndef GRAPH_INC_LIST_H
#define GRAPH_INC_LIST_H


#include "Graph.h"
#include "Edge.h"
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
    //this scructure is implemented with vector of edge

    template<class T>
    class GraphIncList: public Graph<T>{
    private: 

		//this is the data structure
        std::map<T,Node<T>*> incList;
        std::list<Edge<T>*> edgeList;

        // bool edge_existence(const T &_src,const T &_dest) const;
        bool edgeExistence(const Edge<T> &edge) const;

        bool edgeExistence(const T* srcValue,const T* destValue) const;

        bool nodeExistence(const T* nodeValue) const;

        //typename std::map<T,node<T>*>::iterator getNode(const T* _n) const;
        //typename std::vector<edge<T>>::iterator getEdge(const T* _n) const;
        // std::vector<edge<T>> edge_list; 
        // std::map<T,node<T>*> adj_lists;   

    public:
        ///Default costructor for the GraphAdjList
        GraphIncList();

        ///Costructor with a vector of Edge
        // GraphAdjList(const std::vector<Edge> &_edges);
        ///virtual Destructor
        virtual ~GraphIncList(){}

        ///add a Node x in the graph
        void addNode(const T &value) override;

        ///return the max degree of the graph
        int maxDegree() override;

        ///Return the degree of the node _x
        int degree(const T& nodeValue) override;

        ///Add an Edge (x,y) in the graph
        void addEdge(const T& srcValue,const T& destValue) override;

        ///Add an Edge (x,y) in the graph
        void addEdge(const Edge<T>& edge);

        ///Delete the node from the Graph
        void deleteNode(const T& value) override;      

        //Remove the Edge in the graph
        void deleteEdge(const T &srcValue,const T &destValue) override;       //remove a Edge in the graph 

        void deleteEdge(const Edge<T>& edge);                        //remove a Edge in the graph

        void getIncidentEdges(const T& value, std::list<Edge<T>>& edges) override;

        void getOutgoingEdges(const T& value, std::list<Edge<T>>& edges) override;

        void getIncomingEdges(const T& value, std::list<Edge<T>>& edges) override;

        bool isAdjacent(const T &srcValue,const T &destValue) override;       //return true if the edge(x,y) exist, else return false

        //method for search in Graph
        void breadthSearch(const T& startValue, TreePtrList<T>& tree) override{};

        void depthSearch(const T& startValue, TreePtrList<T>& tree) override {};

        void markNode(const T& value,marking mark) override {}

        void showStructure() const;

        void showNode() const;

        void showGraphValue() const{}

    };
}

#include "../sources/GraphIncList.cpp"

#endif