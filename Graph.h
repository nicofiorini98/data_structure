#pragma once

#include <iostream> 
#include <list>
#include "utility.h"

class Graph {
public:

    virtual ~Graph();

    virtual int numNode();                          //return the number of the Node in the arch
    virtual int numEdge();                          //return the number of the Edge 
    virtual int grade(Node* x);                     //return the grade of the Node x
    virtual void getIncidentEdge(Node* x);          //return the incident edge of the Node x
    virtual void getExtremes(Edge* e);              //return the Node of the Edge
    virtual Node* getOpposite(Node*x,Edge* e);      //return the Node from the opposite side of the Edge //TODO return a pointer?
    virtual bool isAdjacent(Node* x,Node* y);       //return true if the edge(x,y) exist, else return false
    virtual void addNode(Node* x)=0;                //add a Node 
    virtual void addEdge(Node* x,Node* y)=0;        //add an Edge
    virtual void deleteNode(Node *x);               //remove a Node in the graph
    virtual void deleteEdge(Edge* e);               //remove a Edge in the graph


};

