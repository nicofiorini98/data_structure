#include "tree_general.h"
#include <stack>

using namespace datalib;    
int callAdd =0; 


tree_general::tree_general(int _degree): tree()
{
    //initalization parameter
    degree=_degree;
    root=nullptr;

}


void tree_general::addNode(const node* _x,const node *_parent,const std::list<node*> _children){

    /*
    * pre-conditions: x and _parent cannot both be nullptr
    * x is a roots of the tree if the parent is not specified and the root doesn't exists
    * x is a children of the roots if the parent is not specified and the root already exists
    */
    callAdd++;
    //std::cout<<"chiamata addNode numero: "<<callAdd<<"\n";

    node* x;
    node* parent_ptr=nullptr;

    node* s=nullptr;

    std::map<int,node*>::iterator itr;
    std::map<int,node*>::iterator itr_parent;

    if(x==nullptr)
    {
        std::cerr<<"errore, non puoi aggiungere un nodo che sia nullo\n";
    }

    //manage the parent if specified(!=nullptr)
    if(_parent != nullptr)
    {
        //try to find _parent in the map
        itr_parent = nodes_map.find(_parent->value);

        //create parent if doesn't exist and add in the map
        if(itr_parent == nodes_map.end())
        {
            parent_ptr = new node(_parent->value); 
            nodes_map.insert({parent_ptr->value,parent_ptr});                                             
        }
        else{
            //update the pointer p
            parent_ptr=itr_parent->second;
        }
    }

    //try to find x in the map
    itr=nodes_map.find(_x->value);

    //if x doesn't exist, create it and add in map
    if(itr == nodes_map.end())
    {
        x = new node(_x->value);                                                       //new to delete
        nodes_map.insert({x->value,x});

        //add a son in parent
        if(parent_ptr)
            parent_ptr->node_list.push_back(x);
        
        //add parent 
        x->parent=parent_ptr;
    }
    else 
    {
        (itr->second)->parent=parent_ptr;

        //update sons of the parent
        if(parent_ptr)
            parent_ptr->node_list.push_back(itr->second);
    }


    
/*  //add children in the node 
    for(auto &child: _children)
    {
        //pre-conditions: we can add child only if doesn't exists in the tree               //troppo restrittiva come condizione?
        itr = nodes_map.find(child->value);
        if(itr==nodes_map.end())
        {
            s = new node(*child);
            s->parent = n;
            nodes_map.insert({s->value,s});
            n->node_list.push_back();
        }
    } */
    //std::cout<<"fine chiamata\n";
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


void tree_general::visitDFS(const node* _root)
{
    //initialize for stack
    std::stack<node> s;
    std::map<int,node*>::iterator itr;

    //pre-conditions: if the node isn't in the tree, return error
    itr = nodes_map.find(_root->value);
    if(itr==nodes_map.end())
    {
        std::cerr<<"errore, non c'è il nodo per poter fare la visita\n";
        return;
    }

    s.push(*(*itr).second);
    while(!s.empty())    
    {
        node *u = &s.top();
        s.pop();             //pop don't return the value

        //todo vedere se è corretto, non mi fido
        if(u)
        {
            //visit u
            std::cout<<u->value<<"\n";
            std::list<node*> childrens=getChildren(*u);
            std::list<node*>::iterator itr;

            if(childrens.empty())
                u=nullptr;
            else
               /*  for(itr=childrens.end()--;itr != childrens.begin();itr--)
                    s.push(**itr);
               */
               for(auto i=(childrens.rbegin());i!=childrens.rend();i++)
                    s.push(**i);
            //prendere la lista dei figli di u 
            //ed inserirli nello stack
        }
    }
}



void tree_general::showTree()
{
    std::cout<<std::endl;
    for(auto& n: nodes_map)
    {
        if(n.second->parent!=nullptr){
            std::cout<<((n.second)->parent)->value<<"<---";
        }
        else 
            std::cout<<"null"<<"<---";
    
        std::cout<<n.first<<" --->  ";
        //print the sons if the list isn't empty
        if(!n.second->node_list.empty())
        {

            for(auto& child: n.second->node_list){
                std::cout<<child->value<<" ";
            }

        }
        else 
            std::cout<<"null";

        std::cout<<std::endl;
    }
}


void tree_general::showTree2()
{
    std::cout<<std::endl;

}