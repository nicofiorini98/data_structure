#ifndef NODE_CPP
#define NODE_CPP
#pragma once
#include "Node.h"
#include <algorithm>

using namespace datalib;

template<class T>
Node<T>::Node(T _value){

    //todo vedere se pos mi serve ancora
    //initialization
    value = _value;
    pos=-1;
    num_children=0;
    parent=nullptr;
    node_list={};
    mark=unexplored;

}

template<class T>
Node<T>::Node(T value, Node<T>* parent){

            this->value = value;
            pos = -1;
            num_children = 0;
            parent = parent;
            node_list = {};
            mark = unexplored;
} 

template<class T>
Node<T>::Node(const Node<T>& x){
    value = x.value;
    node_list = x.node_list;
    parent = x.parent;
    pos = x.pos;
    num_children = x.num_children;
    mark = unexplored;
}


template<class T>
Node<T>::~Node(){

}


template<class T>
bool Node<T>::operator==(const Node<T>& x) const{
    if(x.value==value)
        return true;
    else
        return false;
}

template<class T>
Node<T>& Node<T>::operator=(const Node<T>& x){
    value = x.value;
    node_list = x.node_list;
    pos = x.pos;
    parent = x.parent;
    return *this;
}

template<class T>
bool Node<T>::operator<(const Node<T>& x) const{

    if(x.value<value)
        return true;
    else 
        return false;
}

template<class T>
bool Node<T>::operator<=(const Node<T>& x) const{

    if(x.value<=value)
        return true;
    else
        return false; 
}

template<class T>
bool Node<T>::operator>(const Node<T>& x) const{

    if(x.value>value)
        return true;
    else
        return false;
}

template<class T>
bool Node<T>::operator>=(const Node<T>& x) const{

    if(x.value>=value)
        return true;
    else 
        return false;
}

template<class T>
bool Node<T>::operator!=(const Node<T>& x) const{
    if(x.value==value)
        return false;
    else
        return true;
}

// TODO ridare un'occhiata al std::find qui dentro

// &&    con questo posso passarci soltanto rvalue reference, io qui ci passo una lista creata sul momento
// ecco perchè devo passarci questo
//altrimenti posso pure mettere const std::list<node<T>*> & _children, però così poi non 
// posso modificare la lista, ma a me non importa non è la lista che devo modificare 

// O(n log(n))
template<class T>
void Node<T>::addChildren(const std::list<Node<T>*>& _children){

    typename std::list<Node<T>*>::iterator itr;

    for(auto& child: _children)
    {
        if(child==nullptr)
            continue;

        itr = std::find(node_list.begin(),node_list.end(),child);

			//if the child isn't on the list, then add it 
        if(itr==node_list.end()){
            node_list.push_back(child); //complessità costante
        }
    }
}

#endif