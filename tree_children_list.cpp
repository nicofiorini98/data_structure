#include "tree_children_list.h"

using namespace datalib;    

tree_children_list::tree_children_list(int _degree){
    degree=_degree;

}


void tree_children_list::addNode(const node* x,const node *_parent){

    /* pre-conditions: x must be different from the null pointer
    * if father is a null pointer, _node is a roots of the tree 
    */
    
    node *n;
    std::map<int,node*>::iterator itr;

    //if the node x doesn't exist in the map, then add it
    itr=nodes_map.find(x->value);
    if(itr != nodes_map.end()){
        n = new node(*x);
        nodes_map.insert({x->value,n});
    }

    //if the node _parent doesn't exist in the map, then add it 

    //devo creare un nodo anche per il parent, non posso usare quello che viene passato per parametro
    if(_parent=nullptr)
    {
        n->parent = ;
    }




    
    
    

}