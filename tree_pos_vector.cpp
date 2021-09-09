#pragma once
#include <math.h>
#include "tree_pos_vector.h"
#include "tree.h"

using namespace datalib;

//I need to know the grade of the tree and the 
//num_nodes for instatiate the tree
template<class T>
tree_pos_vector<T>::tree_pos_vector(int _degree,int _height): tree<T>()
{
    //initialization parameter
    degree = _degree;
    root=nullptr;
    height=_height;

    //computation of max_num_nodes allowed from the data_structure
    max_num_nodes=0;
    for(int i=0;i<=height;i++){
        max_num_nodes += pow(degree,i);
    }

    //initialization vector (nullptr)
    vec_node.resize(this->max_num_nodes);

    // std::cout<<"size of the vector: "<<vec_node.size()<<"\n";

}  

template <class T>
void tree_pos_vector<T>::addNode2(node<T>* _x,node<T> *_parent){

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
    
    //check if x already exists
    //std::cout<<"prima di trova: "<<std::endl<< (*vec_node.begin())->value;
    // if((*vec_node.begin())==nullptr)
    //     std::cout<<"vettore nodo nullo\n";

    x_itr = datalib::trova(vec_node.begin(), vec_node.end(),_x);

    if(x_itr != vec_node.end()){
        std::string error = "x already exists\n";
        throw error;
    }

    //MEGLIO NON FARLO QUI, ANCORA NON SO SE DEVO LANCIARE UN ERRORE PER IL PARENT O NO
    //vedere dove farlo, perchè senza questo da segmentation fault
    // if(!root)
    //     root = x_ptr;

    // TODO qui devo decide dove vado ad inserire il nodo, e lo devo inserire 
    // in base alla posizione del padre

    if(_parent){

        parent_itr = datalib::trova(vec_node.begin(),vec_node.end(),_parent);
        std::cout<<"puntatore al parent "<<(*parent_itr)<<"\n";

        //pre-condition 2: parent can't be different from the null_ptr
        if(parent_itr==vec_node.end())
        {
            std::string a =   "addNode(): the father entered doesn't exists, at call number: " + std::to_string(call);
            throw a;
        }

        try{
            addChildrens(*parent_itr,{_x});
        }
        catch(std::string &error){
            throw error; 
        }
        

    }
    else //padre nullo, aggiornare radice
    {
        if(root){
            std::string error("esiste già una radice\n");
            throw error;
        }
        else{

            std::cout<<"aggiunta radice\n";
            node<T>* x_ptr = new node<T>(*_x);
            root=x_ptr;
            vec_node[1]=x_ptr;
            x_ptr->pos=1;
        }           
    }
}

template<class T>
void tree_pos_vector<T>::addChildrens(node<T>* _x,const std::list<node<T>*> &_childrens){
    
    /* Preconditions
     * 1. the node _x must exists
     * 2. the nodes to be added must have enough space 
     */




    //preconditions 1 
    if(!_x){
        std::string error("error: _x can't be null pointer\n");
        throw error;
    }

    int pos = _x->pos;

    //preconditions 2 
    if((_x->num_children + _childrens.size()) > degree){
        std::string error("error: max child node reached\n");
        throw error;
    }


    for(auto &n: _childrens){

        node<T> *child2add= new node<T>(*n);

        //add childrens in vec_node in the proper positions
        int pos_childrens=(pos*degree)+_x->num_children;

        vec_node[pos_childrens]= child2add;
        child2add->pos=pos_childrens;

        _x->num_children++;
    }
}


template <class T>
void tree_pos_vector<T>::showTree(){

    std::cout<<"\n\n Stampa di Tree_pos_vector: \n";

    for(auto &n: vec_node){
        if(n){
            std::cout<<n->value<<", puntatore: "<<n<<"\n";
        }
        else if(n==nullptr)
            std::cout<<"nullptr\n";
    }
    
    std::cout<<std::endl;


}