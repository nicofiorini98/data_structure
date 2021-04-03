#include "tree_parent_vector.h"

using namespace datalib;

void tree_parent_vector::addNode(const node *_node, const node *_parent, const std::list<node> _children) 
{
    node* n = new node(*_node);

    //if father is not defined,and even the root is not defined, then the _node is the root
    if(root==nullptr && _parent==nullptr)
    {
        root=n;
        vec_node.push_back(std::make_pair(root,0));
        num_nodes++;
        std::cout<<"aggiunto"<<n->value <<" come radice ";
        return;
    }
    
    //if the father is not specified and the root already exists, 
    //then make node the son of the root
    else if(_parent==nullptr)
        vec_node.push_back(std::make_pair(n,0));
    else
    {
        int parent_pos=getPos(*_parent); 
        if(parent_pos==-1) // TODO gestire la non esistenza del padre nel vettore
            return;
        vec_node.push_back(std::make_pair(n,parent_pos));
    }

    //todo update with the children

}


int tree_parent_vector::getPos(const node &x)
{
    for(int i=0;vec_node.size();i++)
        if(vec_node[i].first->value==x.value)
            return i;

    return -1;
}

void tree_parent_vector::showTree(){
    int i=0;
    std::cout<<std::endl;
#if 0
    for(auto& node: vec_node){
         std::cout<<"nodo in posizione: "<< i++ <<" e valore "<< node.first->value<<" con padre in pos: "<<node.second<<
             " e valore: "<< vec_node[node.second].first->value<<std::endl;
    }
#endif
    
    for(auto& n: vec_node){
        std::cout<<"( "<< n.first->value<<", "<<n.second<<" )\n";
    }


}

