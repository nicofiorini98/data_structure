
#ifndef TREE_POS_VECTOR_CPP
#define TREE_POS_VECTOR_CPP
#include <math.h>
#include "TreePosVector.h"
#include "Tree.h"

using namespace datalib;

//I need to know the grade of the tree and the 
//num_nodes for instatiate the tree
template<class T>
TreePosVector<T>::TreePosVector(int _degree, int _height): Tree<T>(){
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
void TreePosVector<T>::addNode(const T* _x, const T* _parent){

    static int call = 0;
    call++;

    //local iterator, typename because are nested dependent names
    typename std::vector<Node<T>*>::iterator x_itr;
    typename std::vector<Node<T>*>::iterator parent_itr;

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

        //pre-condition 2: parent can't be different from the null_ptr
        if(parent_itr==vec_node.end())
        {
            //is only for debugging
            std::string a =   "addNode(): the father entered doesn't exists, at call number: " + std::to_string(call);
            throw a;
        }
        try{
            T a = *_x;
            addChild(_parent,{&a});
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
            Node<T>* x_ptr = new Node<T>(*_x);
            root=x_ptr;
            vec_node[1]=x_ptr;
            x_ptr->pos=1;
        }
    }
}


//add childrens to node x, x must exists
template<class T>
void TreePosVector<T>::addChildren(const T* _x, const std::list<T*> &_children){
    
    /* Preconditions
     * 1. the node _x must exists, and must be in the vec_node
     * 2. the nodes to be added must have enough space 
     * TODO 3. the child node to be added it must not exist
     */

    typename std::vector<Node<T>*>::iterator x_itr;
    x_itr= datalib::trova(vec_node.begin(),vec_node.end(),_x);
    
    //preconditions 1 
    if(x_itr == vec_node.end()){
        std::string error("error: _x can't be null pointer\n");
        throw error;
    }

    int pos = (*x_itr)->pos;

    //preconditions 2 
    if(((*x_itr)->num_children + _children.size()) > degree){
        std::string error("error: max child node reached\n");
        throw error;
    }

    for(auto &n: _children){
        Node<T> *child2add= new Node<T>(*n);

        //add childrens in vec_node in the proper positions
        int pos_childrens=(pos*degree)+ (*x_itr)->num_children;

        vec_node[pos_childrens]= child2add;
        child2add->pos=pos_childrens;

        ++(*x_itr)->num_children;
    }
}

template<class T>
void TreePosVector<T>::addChild(const T* _x, const T* _child){
    /* Preconditions
     * 1. the node _x must exists, and must be in the vec_node
     * 2. the nodes to be added must have enough space 
     * 3. the child node to be added it must not exist
     */

    typename std::vector<Node<T>*>::iterator x_itr;
    x_itr= datalib::trova(vec_node.begin(),vec_node.end(),_x);
    typename std::vector<Node<T>*>::iterator child_itr;
    child_itr= datalib::trova(vec_node.begin(),vec_node.end(),_child);
    
    //preconditions 1 
    if(x_itr == vec_node.end()){
        std::string error("error: _x can't be null pointer\n");
        throw error;
    }


    //precondition 2 
    if(((*x_itr)->num_children + 1) > degree){
        std::string error("error: max child node reached\n");
        throw error;
    }
    //pre-condition 3
    if(child_itr != vec_node.end()){
        std::string error("the child to add, already exists in tree\n");
        throw error;
    }

    int pos = (*x_itr)->pos;
    int pos_child=(pos*degree) + (*x_itr)->num_children;

    Node<T> *child2add= new Node<T>(*_child);

    vec_node[pos_child]= child2add;
    vec_node[pos_child]->pos=pos_child;

    ++(*x_itr)->num_children;
}

template <class T>
void TreePosVector<T>::showTree(){

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

// template <class T>
// int tree_pos_vector<T>::getNumChildren(node<T>* _x){
//     return _x->num_children;
// }

//convention of print tree
template <class T>
void TreePosVector<T>::showTree2(){
    //OUTPUT following the conventions of the library
    //{ padre figlio1 } { padre figlio2 } { padre2 figlio1}

    for(auto &node: vec_node){
        if(node){
            
        }
    }

}


#endif