#include "tree_general.h"
#include <stack>

using namespace datalib;    

tree_general::tree_general(int _degree){
    degree=_degree;
}


void tree_general::addNode(const node* x,const node *_parent,const std::list<node*> _children){

    /* pre-conditions: x must be different from the null pointer
    * if father is a null pointer, _node is a roots of the tree 
    */
    
    node* n;
    node* p=nullptr; 

    std::map<int,node*>::iterator itr;
    std::map<int,node*>::iterator itr_parent;

    //try to find x in the map
    itr=nodes_map.find(x->value);
    

    //manage the parent if specified(!=nullptr)
    if(_parent != nullptr) {
        //try to find _parent in the map
        itr_parent=nodes_map.find(_parent->value);

        //create parent if doesn't exist and add in the map
        if(itr_parent == nodes_map.end()){
            p = new node(*_parent);                                                     //new to delete
            nodes_map.insert({p->value,p});
        }
        else
            //update the pointer p
            p=itr_parent->second;
    }


    //if x doesn't exist, create it and add in map
    if(itr == nodes_map.end())
    {
        n = new node(x->value,p);                                                       //new to delete
        nodes_map.insert({x->value,n});

        //add a son in parent
        if(p!=nullptr)
            p->node_list.push_back(n);
    }

    //add-update parent to the node 
    n->parent=p; 

//     //add children in the node 
//     for(auto &child: _children)
//     {
//         //if x doesn't exist, create it and add in map
//         itr = nodes_map.find(child->value);
//         if(itr==nodes_map.end())
//         {
//             n = new node(*child);
//             nodes_map.insert({n->value,child});
//         }
//     } 
}


//return the number of sons for the node x 
int tree_general::getDegree(const node &x)
{
   return nodes_map.find(x.value)->second->node_list.size();
}

//return the pointer to the node of a 
//todo vedere, non mi conviene restituire un puntatore
node tree_general::getParent(const node &x)
{
    //to see if is convenient to return a reference, the client 
    //what he can do with a reference of node?
   return *(nodes_map.find(x.value)->second->parent);
}

std::list<node*> tree_general::getChildren(const node&x){

    //

    std::map<int,node*>::iterator itr=nodes_map.find(x.value);

    if(itr!=nodes_map.end())
    {
        return (nodes_map.find(x.value)->second->node_list);
    }
}


void tree_general::visitDFS(const node &_root)
{
    //initialize for stack
    std::stack<node*> s;
    std::map<int,node*>::iterator itr;

    itr = nodes_map.find(_root.value);
    if(itr==nodes_map.end())
    {
        std::cerr<<"errore, non c'è il nodo per poter fare la visita\n";
        return;
    }

    s.push((*itr).second);
    while()    

}



void tree_general::showTree(){


    std::cout<<std::endl;
    for(auto& n: nodes_map)
    {
        if(n.second->parent!=nullptr){
            std::cout<<((n.second)->parent)->value<<"<---";
        }
        else 
            std::cout<<"//"<<"<---";
    
        std::cout<<n.first<<" --->  ";
        for(auto& child: n.second->node_list){
            std::cout<<child->value<<" ";
        }
        std::cout<<std::endl;
    }
}
