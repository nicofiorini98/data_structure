#ifndef GRAPH_ADJ_LIST_CPP
#define GRAPH_ADJ_LIST_CPP
#pragma once
#include "GraphAdjList.h"
#include <list>

using namespace datalib;

// template<class T>
// GraphAdjList<T>::GraphAdjList(const std::vector<Edge> &_edges)
// {
//     for(auto &edge: _edges)
//         addEdge(*edge.src,*edge.dest);
// }


//add an Edge O(n log(n))
template<class T>
void GraphAdjList<T>::addEdge(const T &srcValue, const T &destValue)
{
    //Pre-conditions

    //if the adjList don't have the src node<T> then add the adjList in the adjLists
    typename std::map<T,Node<T>*>::iterator src_itr  = adjList.find(srcValue);  //O(log (n))
    typename std::map<T,Node<T>*>::iterator dest_itr = adjList.find(destValue); //O(log (n))

    Node<T> *src_ptr;
    Node<T> *dest_ptr;

    //create src node and dest node if isn't on the graph
    //else get the pointer from the itr 
    if(src_itr==adjList.end())
        src_ptr = private_addNode(srcValue);  //O(n)
    else 
        src_ptr = (*src_itr).second;

    if(dest_itr == adjList.end())
        dest_ptr = private_addNode(destValue); //O(n)
    else
        dest_ptr = (*dest_itr).second;

    src_ptr->addChildren({dest_ptr}); //O(n log(n))
}

// template<class T>
// void GraphAdjList<T>::addEdge(const Edge &_edge){
//     addEdge(*_edge.src,*_edge.dest);
// }

// O(n)
//this addNode return a pointer of node 
template<class T> 
Node<T>* GraphAdjList<T>::private_addNode(const T &value){

    //if node doesn't exist in the map, create it
    Node<T> *src = new Node<T>(value);
    adjList.insert(std::pair<T,Node<T>*>(src->value, src));
    ++this->num_node;
    return src;
}

// O(n)
template<class T>
void GraphAdjList<T>::addNode(const T &value){

    //if node doesn't exist in the map, create it
    Node<T> *src = new Node<T>(value);
    adjList.insert(std::pair<T,Node<T>*>(src->value, src));
    ++this->num_node;
}

template<class T>
void GraphAdjList<T>::deleteNode(const T &value){

    // std::map<int,std::list<node<T>*>>::iterator itr_x= adjList.find(x.value);
    // std::map<int,std::list<node<T>*>>::iterator itr; 

}

template<class T>
void GraphAdjList<T>::deleteEdge(const T &srcValue, const T &destValue)
{

}

// template<class T>
// void GraphAdjList<T>::deleteEdge(const Edge &_edge){
//     deleteEdge(*_edge.src,*_edge.dest);

// }

template<class T>
void GraphAdjList<T>::showStructure() const{
    
    for (auto &n: adjList){
        // print current vertex number
        std::cout << (*(n.second))<< " --> ";
        // print all neighboring vertices of vertex i

        for(auto &child: (n.second)->node_list){
            std::cout<<" "<<*child;
        }
        std::cout << std::endl;
    }
}

template<class T>
void GraphAdjList<T>::showNode() const{

    for(auto &n: adjList){
        std::cout<<*(n.second)<<"\n";
    }

    
}

template<class T>
void GraphAdjList<T>::showGraphValue() const{

    // for (auto &n: adjList){
    //     // print current vertex number
    //     std::cout << (*(n.second).begin())->value<< " --> ";
    //     // print all neighboring vertices of vertex i
    //     for(std::list<node<T>*>::const_iterator it = ++((n.second).cbegin()); it!=(n.second).cend(); it++)
    //         std::cout<<(*it)->value<<" ";
        
    //     std::cout << std::endl;
    // }
}



#endif