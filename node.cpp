#pragma once
#include "node.h"
#include <algorithm>

using namespace datalib;



template<class T>
node<T>::node(T _value)
{
    value=_value;
    pos=-1;
    num_children=0;
    parent=nullptr;
    node_list={};
}

template<class T>
node<T>::node(T _value,node<T>* _parent)
{
            value=_value;
            pos=-1;
            num_children=0;
            parent=_parent;
            node_list={};
} 

template<class T>
node<T>::node(const node<T>& x)
{
    value = x.value;
    node_list = x.node_list;
    pos = x.pos;
    parent = x.parent;
}


template<class T>
node<T>::~node()
{
    
}


template<class T>
bool node<T>::operator==(const node<T>& x) const{
    if(x.value==value){
        return true;
    }
    return false;
}

template<class T>
void node<T>::operator=(const node<T>& x) 
{
    value = x.value;
    node_list = x.node_list;
    pos = x.pos;
    parent = x.parent;   
}

template<class T>
bool node<T>::operator<(const node<T>& x) const{

    if(x.value<value){
        return true;
    }
    return false;
}

template<class T>
bool node<T>::operator<=(const node<T>& x) const{

    if(x.value<=value){
        return true;
    }
    return false;
}

template<class T>
bool node<T>::operator>(const node<T>& x) const{

    if(x.value>value){
        return true;
    }
    return false;
}

template<class T>
bool node<T>::operator>=(const node<T>& x) const{

    if(x.value>=value){
        return true;
    }
    return false;
}

template<class T>
bool node<T>::operator!=(const node<T>& x) const{
    if(x.value==value)
        return false;
    return true;
}

// TODO ridare un'occhiata al std::find qui dentro
template<class T>
void node<T>::addChildren(std::list<node<T>*>&& _children){

    typename std::list<node<T>*>::iterator itr;

    for(auto& child: _children)
    {
        if(child==nullptr)
            continue;

        itr = std::find(node_list.begin(),node_list.end(),child);

        if(itr==node_list.end()){
            node_list.push_back(child); //complessità costante
        }
    }
}
