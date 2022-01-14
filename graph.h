#ifndef GRAPH_H
#define GRAPH_H

#include <iostream> 
#include <list>
#include <stack>
#include <queue>
#include "tree_ptr_list.h"
#include "node.h"
#include "edge.h"


namespace datalib{

    /**
     * \class Graph
     * \brief This class is abstract, is a base class for various implementations.
     * \author Nico Fiorini
     * \date 02/03/2021
     */

	template<class T>
    class graph {
    private: 

    protected:
        int num_node;
        int num_edge;

    public:

        graph(){
            num_node=0;
            num_edge=0;
        }
        virtual ~graph(){}

        ///return the number of the Node in the graph
        int numNode(){return num_node;}             
        ///return the number of the Edge in the graph
        int numEdge(){return num_edge;}             
        ///return the grade of the node x 

        virtual int max_degree()=0;                                   //restituisce il grado massimo del grafo
        virtual int degree(const T &_x)=0;                            //restituisce il grado del nodo
        ///return the incident edge of the Node x
        virtual std::vector<edge<T>> getIncidentEdge(const T &_x)=0;           
        ///return the adjacent nodes of the Node x
        virtual void getAdjNode(const T &_x)=0;
        //void getExtremes(Edge* e);                         //return the Node of the Edge //is only for edge list
        //node* getOpposite(Node x,Edge e);                  //return the Node from the opposite side of the Edge  //is only for edge_list
        virtual bool isAdjacent(const T &_src,const T &_dest)=0;       //return true if the edge(x,y) exist, else return false

        //each data structure has own method for add Node and Edge
        virtual void addNode(const T &_x)=0;                        //add a Node 
        virtual void addEdge(const T *_src,const T *_dest)=0;       //add an Edge
        // virtual void addEdge(const Edge &_edge)=0;               //add an Edge
        virtual void deleteNode(const T &_x)=0;                     //remove a Node in the graph
        virtual void deleteEdge(const T &_src,const T &_dest)=0;    //remove a Edge in the graph
        virtual void breadthFirstSearch(const T& _first_node,tree_ptr_list<T>& _tree)=0;
        //virtual tree_ptr_list<T> depth(const T& _first_node)=0;
        // virtual void deleteEdge(const Edge<T> &_edge)=0;         //remove a Edge in the graph
    };
}

#endif
