#include "tree_pos_vector.h"

using namespace datalib;
//I need to know the grade of the tree and the 
//num_nodes for instatiate the tree
tree_pos_vector::tree_pos_vector(int _max_degree,int _num_nodes)
{
    //initialization parameter
    max_degree = _max_degree;
    num_nodes = _num_nodes;

    //initialization vector
    vec_node.resize(num_nodes);
} 

//TODO build an example for doing this 
void tree_pos_vector::addNode(const node *_node,const node *_parent)
{
    
}

