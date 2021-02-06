#pragma once
#include <iostream>
#include <list>

//to define with template
class Node{
private:
    int value;
    int pos;
public:
    Node(int _value){
        value=_value;
        pos=-1;
    }
    Node(const Node& x){
        value=x.value;
        pos=x.pos;
    }

    friend class AdjList;
};

//TODO here I should define the template
//class for the Edge of the graph, this edge is oriented
struct Edge{
    Node *src;    //source of the edge
    Node *dest;   //destination of the edge
    int weight; //weight of the edge
    std::string color;

};




