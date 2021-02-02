#pragma once
#include <iostream>
#include <list>

//to define with template
struct Node{
    int value;
    int key;
};

//TODO here I should define the template
//class for the Edge of the graph, this edge is oriented
struct Edge{
    Node src;    //source of the edge
    Node dest;   //destination of the edge
    int weight; //weight of the edge
};




