#include "tree_children_list.h"

using namespace datalib;    

tree_children_list::tree_children_list(int _degree){
    degree=_degree;

}


void tree_children_list::addNode(const node* x,const node *_parent,const std::list<node*> _children){

    /* pre-conditions: x must be different from the null pointer
    * if father is a null pointer, _node is a roots of the tree 
    */
    
    node* n;
    node* p=nullptr; 

    std::map<int,node*>::iterator itr;
    std::map<int,node*>::iterator itr_parent;

    //try to find x in the map
    itr=nodes_map.find(x->value);

    

    //try to find _parent in the map
    if(_parent != nullptr) {
        itr_parent=nodes_map.find(_parent->value);
        std::cout<<"boh\n";

        if(itr_parent == nodes_map.end()){
            std::cout<<"padre del nodo creato e aggiunto\n";                
            p = new node(*_parent);
            nodes_map.insert({p->value,p});
        }
        else
        {
            p=itr_parent->second;
        }
    }
    else if(itr_parent == nodes_map.end()){
            std::cout<<"padre del nodo creato e aggiunto\n";                
            p = new node(*_parent);
            nodes_map.insert({p->value,p});
        
    }

    //if parent doesn't exist, create it and add in map

    //if x doesn't exist, create it and add in map
    if(itr == nodes_map.end())
    {
        n = new node(x->value,p);
        nodes_map.insert({x->value,n});

        //add a son in parent
        if(p!=nullptr)
            p->node_list.push_back(n);
    }

    //add-update parent to the node 
    n->parent=p; 

    /* //add children in the node 
    for(auto &child: _children)
    {
        //if x doesn't exist, create it and add in map
        itr = nodes_map.find(child->value);
        if(itr==nodes_map.end())
        {
            n = new node(*child);
            nodes_map.insert({n->value,child});
        }
    } */
}



void tree_children_list::showTree(){

    std::cout<<std::endl;
    for(auto& n: nodes_map)
    {
        if(n.second->parent!=nullptr){
            std::cout<<((n.second)->parent)->value<<"->";
        }
    
        std::cout<<n.first<<" ->  ";
        for(auto& child: n.second->node_list){
            std::cout<<child->value<<" ";
        }
        std::cout<<std::endl;
    }


}
