#pragma once

#include <iostream> 
#include <list>
#include "utility.h"

class Graph {
private: 

protected:
    int num_node;
    int num_edge;

public:

    Graph(){
        num_node=0;
        num_edge=0;
    }
    virtual ~Graph(){}

    //virtual ~Graph();
    int numNode(){return num_node;}                           //return the number of the Node in the arch
    int numEdge(){return num_edge;}                          //return the number of the Edge 

    virtual int grade(const Node &x)=0;                     //return the grade of the Node x
    virtual void getIncidentEdge(const Node &x)=0;          //return the incident edge of the Node x
    virtual void getAdjNode(const Node &x)=0; 

    //void getExtremes(Edge* e);              //return the Node of the Edge //is only for edge list
    //Node* getOpposite(Node x,Edge e);      //return the Node from the opposite side of the Edge  //is only for edge_list
    bool isAdjacent(const Node &x,const Node &y);       //return true if the edge(x,y) exist, else return false

    //each data structure has own method for add Node and Edge
    virtual void addNode(const Node &x)=0;                //add a Node 
    virtual void addEdge(const Node &x,const Node &)=0;        //add an Edge
    //void deleteNode(Node *x);               //remove a Node in the graph
    //void deleteEdge(Edge* e);               //remove a Edge in the graph
};

