#pragma once
#include <iostream>
#include <list>

//TODO to define with template
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
    //overload operator
    bool operator==(const Node& x) const{
     std::cout<<"operatore ==\n";
        if(x.value==value){
            return true;
        }

        return false;
    }

    bool operator!=(const Node& x) const{
        if(x.value==value)
            return false;
        return true;
    }


    friend class AdjList;
    friend class GraphAdjList;
    friend class TreeVectorFather;
};

//TODO here I should define the template
//class for the Edge of the graph, this edge is oriented
struct Edge{
    Node *src;    //source of the edge
    Node *dest;   //destination of the edge
    int weight; //weight of the edge
    std::string color;
};

