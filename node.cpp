#pragma once
#include "node.h"
#include <algorithm>

using namespace datalib;

template<class T>
node<T>::node(T _value){

    //initialization
    value=_value;
    pos=-1;
    num_children=0;
    parent=nullptr;
    node_list={};

}

template<class T>
node<T>::node(T _value,node<T>* _parent){

            value=_value;
            pos=-1;
            num_children=0;
            parent=_parent;
            node_list={};

} 

template<class T>
node<T>::node(const node<T>& x){

    value = x.value;
    node_list = x.node_list;
    parent = x.parent;
    pos = x.pos;
    num_children=x.num_children;

}


template<class T>
node<T>::~node()
{
    
}


template<class T>
bool node<T>::operator==(const node<T>& x) const{
    if(x.value==value)
        return true;
    else
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

    if(x.value<value)
        return true;
    else 
        return false;
}

template<class T>
bool node<T>::operator<=(const node<T>& x) const{

    if(x.value<=value)
        return true;
    else
        return false; 
}

template<class T>
bool node<T>::operator>(const node<T>& x) const{

    if(x.value>value)
        return true;
    else
        return false;
}

template<class T>
bool node<T>::operator>=(const node<T>& x) const{

    if(x.value>=value)
        return true;
    else 
        return false;
}

template<class T>
bool node<T>::operator!=(const node<T>& x) const{
    if(x.value==value)
        return false;
    else
        return true;
}

// TODO ridare un'occhiata al std::find qui dentro

// &&    con questo posso passarci soltanto rvalue reference, io qui ci passo una lista creata sul momento
// ecco perchè devo passarci questo
//altrimenti pososo pure mettere const std::list<node<T>*> & _children, però così poi non 
// posso modificare la lista, ma a me non importa non è la lista che devo modificare 

// O(n log(n))
template<class T>
void node<T>::addChildren(const std::list<node<T>*>& _children){ 

    typename std::list<node<T>*>::iterator itr;

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
