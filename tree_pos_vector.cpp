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
    static int call = 0;
    call++;

    //local iterator, typename because are nested dependent names
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
    if(_x==nullptr){
        std::string error("you can't add nullptr as a node\n");
        throw error;
    }
    

    node<T>* x_ptr;

    //check if x already exists
    //std::cout<<"prima di trova: "<<std::endl<< (*vec_node.begin())->value;
    // if((*vec_node.begin())==nullptr)
    //     std::cout<<"vettore nodo nullo\n";

    x_itr = datalib::trova(vec_node.begin(), vec_node.end(),_x);

    if(x_itr == vec_node.end()){
        x_ptr = new node<T>(*_x);
        std::cout<<"creo il nodo: "<<*x_ptr<<"\n"; 
    }
    else{
        std::string error = "x already exists\n";
        throw error;
    }

    if(!root)
        root = x_ptr;

    // TODO qui devo decide dove vado ad inserire il nodo, e lo devo inserire 
    // in base alla posizione del padre

    if(_parent){

        parent_itr = datalib::trova(vec_node.begin(),vec_node.end(),_parent);


        //pre-condition 2.
        if(parent_itr==vec_node.end())
        {
            std::string a =   "addNode(): the father entered doesn't exists, at call number: " + std::to_string(call);
            throw a;
        }
        
        //qui devo prendere la posizione del nodo del padre
        addChildrens(_parent,{x_ptr});

    }
    else //padre nullo, aggiornare radice
    {
        //la radice è in posizione 1 
        vec_node[1]=root; 
        root->pos=1;
    }
}

template<class T>
void tree_pos_vector<T>::addChildrens(const node<T>* _x, const std::list<node<T>*> &_childrens){
    
    /* Preconditions
     * 1. the nodes to be added must have enough space 
     * 2. the node _x must exists
     */

    //TODO to clean
    if(!_x){
        std::string error("error: _x can't be null pointer\n");
        throw error;
    }

    int pos = _x->pos;
    int num2add= _childrens.size();
    
    if((_x->num_children + num2add) >= degree)
        throw "error: max child node reached\n";

    //add childrens in the vector structure
    int i=0;
    for(auto &n: _childrens){

        node<T> *a = new node<T>(n->value);
        int pos_a= (pos*degree)+i;
        vec_node[pos_a] = a; 

        a->pos=pos_a;
        i++;
    }

}


template <class T>
void tree_pos_vector<T>::showTree(){

    for(auto &n: vec_node){
        if(n){
            std::cout<<n->value<<" ";
            std::cout<<"puntatore a0:"<<n<<"\n";
        }
        else if(n==nullptr)
            std::cout<<"nullptr\n";
    }
    
    std::cout<<std::endl;


}