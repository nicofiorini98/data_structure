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

        //qui devo prendere la posizione del nodo del padre
        // std::list<node<T>*> lista;
        // lista.push_back(_x);
        addChildrens(*parent_itr,{_x});

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
void tree_pos_vector<T>::addChildrens(const node<T>* _x, const std::list<node<T>*> &_childrens){
    
    /* Preconditions
     * 1. the node _x must exists
     * 2. the nodes to be added must have enough space 
     */

    //intanto lo faccio solo per un nodo, poi penso a modoficare bene gli attributi 
    
    //preconditions 1 
    if(!_x){
        std::string error("error: _x can't be null pointer\n");
        throw error;
    }

    

    int pos = _x->pos;
    std::cout<<"posizione del parent: "<<pos<<"\n";

    node<T>* first_childrens = *(_childrens.begin());

    node<T> *childrens = new node<T>(first_childrens->value);

    int pos_childrens = (pos*degree);           //da modificare nel caso si hanno più figli
    vec_node[pos_childrens] = childrens;

    childrens->pos=pos_childrens;

    std::cout<<"posizione del figlio: "<<pos_childrens<<"\n";
    

    

    // int num2add= _childrens.size();
    // if((_x->num_children + num2add) >= degree)
    //     throw "error: max child node reached\n";

    //add childrens in the vector structure
    // int i=0;
    // for(auto &n: _childrens){

    //     node<T> *a = new node<T>(n->value);
    //     int pos_a= (pos*degree)+i;
    //     vec_node[pos_a] = a; 

    //     a->pos=pos_a;
    //     i++;
    // }

}


template <class T>
void tree_pos_vector<T>::showTree(){

    std::cout<<"\n\n Stampa di Tree_pos_vector: \n";


    for(auto &n: vec_node){
        if(n){
            std::cout<<n->value<<", puntatore: "<<n;
        }
        // else if(n==nullptr)
        //     std::cout<<"nullptr\n";
    }
    
    std::cout<<std::endl;


}