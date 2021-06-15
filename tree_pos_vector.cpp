#pragma once
#include "tree_pos_vector.h"
// #include <algorithm>
#include "tree.h"

using namespace datalib;

//I need to know the grade of the tree and the 
//num_nodes for instatiate the tree
template<class T>
tree_pos_vector<T>::tree_pos_vector(int _max_degree,int _num_nodes): tree<T>()
{
    //initialization parameter
    degree = _max_degree;
    root=nullptr;
    this->num_nodes = _num_nodes;

    //initialization vector (nullptr)
    vec_node.resize(this->num_nodes);

}  

template <class T>
void tree_pos_vector<T>::addNode(const node<T> *_x,const node<T> *_parent)
{

    //per vedere se i nodi sono già inseriti
    typename std::vector<node<T>*>::iterator x_itr;
    typename std::vector<node<T>*>::iterator parent_itr;

    //devo inserire padre e figlio nel vettore, 
    //nel frattempo devo mantenere il vettore abbastanza grande 
    //devo aggiornare il numero dei nodi

    //pre-conditions: 
    //1. the node x to add must be different from nullptr
    //2. the node parent must exists if different from nullptr
    //3. the parent nullptr means that x is the root if the root exists
    //   otherwise x become the root (only the first node inserted can be the root)

    //pre-condition 1
    if(_x==nullptr)
        throw "you can't add nullptr as a node\n";

    node<T>* x_ptr;

    //check if x already exists
    x_itr = std::find(vec_node.begin(), vec_node.end(),_x);
    if(x_itr == vec_node.end())
    {
        //allocation of the node
        x_ptr = new node<T>(*_x);

        // vec_node.insert({x_ptr->value,x_ptr}); //devo capire dove vado ad inserire il nodo padre
    }
    else{
        //se il nodo esiste, cosa devo farci, cambiare posizione????
    }

    if(!root)
        root = x_ptr;


    // TODO qui devo decide dove vado ad inserire il nodo, e lo devo inserire 
    // in base alla posizione del padre

    if(_parent){
        parent_itr = std::find(vec_node.begin(),vec_node.end(),_parent);

        //pre-condition 2.
        if(parent_itr==vec_node.end())
            throw "the father entered doesn't exists";
        
        //qui devo prendere la posizione del nodo del padre

    }
    else //padre nullo, aggiornare radice
    {
        //vedere se mi conviene usare 0 oppure 1
        vec_node[1]=x_ptr;
        // vec_node.at(1)=x_ptr;  //this type of insert generate out_of_range if needed
        // vec_node.insert(vec_node.begin(),x_ptr);
    }


    if(x_ptr==root)
        vec_node[1]=root;
    else{

    }
 
}



template<class T>
void tree_pos_vector<T>::addChildrens(const node<T>* _x, const std::list<node<T>> _childrens){
    
}
