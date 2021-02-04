#pragma once

#include <iostream> 
#include <list>
#include "utility.h"

class Graph {
private: 

protected:
    int num_node;

public:

    //virtual ~Graph();
    int numNode();                           //return the number of the Node in the arch
    int numEdge();                          //return the number of the Edge 

    virtual int grade(Node x)=0;                     //return the grade of the Node x

    void getIncidentEdge(Node* x);          //return the incident edge of the Node x
    void getExtremes(Edge* e);              //return the Node of the Edge
    Node* getOpposite(Node x,Edge e);      //return the Node from the opposite side of the Edge //TODO return a pointer?
    bool isAdjacent(Node x,Node y);       //return true if the edge(x,y) exist, else return false

    //each data structure has own method for add Node and Edge
    virtual void addNode(Node x)=0;                //add a Node 
    virtual void addEdge(Node x,Node y)=0;        //add an Edge
    //void deleteNode(Node *x);               //remove a Node in the graph
    //void deleteEdge(Edge* e);               //remove a Edge in the graph
};

