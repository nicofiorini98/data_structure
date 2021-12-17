#ifndef GRAPH_INC_LIST_H
#define GRAPH_INC_LIST_H


#include "graph.h"
#include "edge.h"
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
    class graph_inc_list: public graph<T>{
    private: 

        std::map<T,node<T>*> inc_list;        

        std::vector<edge<T>> edge_list;        

        // bool edge_existence(const T &_src,const T &_dest) const;
        bool edge_existence(const edge<T> _e) const;
        bool node_existence(const T* _n) const;

        typename std::map<T,node<T>*>::iterator getNode(const T* _n) const;
        typename std::vector<edge<T>>::iterator getEdge(const T* _n) const;
        // std::vector<edge<T>> edge_list; 
        // std::map<T,node<T>*> adj_lists;   

    public:
        ///Default costructor for the GraphAdjList
        graph_inc_list();

        ///Costructor with a vector of Edge
        // graph_adj_list(const std::vector<Edge> &_edges);
        ///virtual Destructor
        virtual ~graph_inc_list(){} 

        ///add a Node x in the graph
        void addNode(const T &_x);

        int degree(const T &_x){}

        ///add an Edge (x,y) in the graph
        void addEdge(const T *_src,const T *_dest);
        void addEdge(const edge<T>& _edge){}
        void deleteNode(const T &_x){}                        //remove a Node in the graphj
        void deleteEdge(const T &_src,const T &_dest){}       //remove a Edge in the graph
        // void deleteEdge(const Edge &_edge);               //remove a Edge in the graph
		// int grade(const T &_x){}

        std::vector<edge<T>> getIncidentEdge(const T &_x){}          //return the incident edge of the Node x
        void getAdjNode(const T &_x){}

        void showStructure() const;
        void showNode() const;
        //void showGraphPos() const;
        void showGraphValue() const{};
    };

}

#include "graph_inc_list.cpp"

#endif