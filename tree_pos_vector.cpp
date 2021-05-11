#pragma once
#include "tree_pos_vector.h"
#include "tree.h"

using namespace datalib;

//I need to know the grade of the tree and the 
//num_nodes for instatiate the tree
template<class T>
tree_pos_vector<T>::tree_pos_vector(): tree<T>()
{
    //initialization parameter
    max_degree = 1;
    this->num_nodes = _num_nodes;

    //initialization vector
    vec_node.resize(_num_nodes);
}  

template <class T>
void tree_pos_vector<T>::addNode(const node<T> *_x,const node<T> *_parent)
{
    /*
     * Pre-conditions: 
     *
    */

    node<T>* x_ptr;

    //per vedere se esiste la sua esistenza 
    typename std::vector<node<T>*>::iterator x_itr;
    typename std::vector<node<T>*>::iterator parent_itr;




    
    

}
