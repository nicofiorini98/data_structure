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

        std::map<T,Node<T>*> inc_list;
        std::list<Edge<T>*> edge_list;

        // bool edge_existence(const T &_src,const T &_dest) const;
        bool edge_existence(const Edge<T> &_e) const;
        bool edge_existence(const T* _src,const T* _dest) const;
        bool node_existence(const T* _x) const;

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
        void addNode(const T &_x) override;

        ///return the max degree of the graph
        int maxDegree() override;
        ///return the degree of the node _x
        int degree(const T& _x) override;

        ///add an Edge (x,y) in the graph
        void addEdge(const T *_src,const T *_dest) override;
        void addEdge(const Edge<T>& _edge);
        void deleteNode(const T& _x)override;                         //remove a Node in the graph
        void deleteEdge(const T &_src,const T &_dest) override;       //remove a Edge in the graph 
        void deleteEdge(const Edge<T>& _edge);                        //remove a Edge in the graph

        void getIncidentEdges(const T& node, std::list<Edge<T>>& _list) override;
        void getOutgoingEdges(const T& node, std::list<Edge<T>>& _list) override;
        void getIncomingEdges(const T& node, std::list<Edge<T>>& _list) override;

        bool isAdjacent(const T &_src,const T &_dest) override;       //return true if the edge(x,y) exist, else return false

        //method for search in Graph
        void breadthSearch(const T& _first_node, TreePtrList<T>& _tree) override;
        void depthSearch(const T& _first_node, TreePtrList<T>& _tree) override;
        void markNode(const T& node,marking mark){}

        void showStructure() const;
        void showNode() const;
        void showGraphValue() const{}

    };
}

#include "../sources/GraphIncList.cpp"

#endif