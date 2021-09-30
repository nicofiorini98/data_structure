#pragma once
#include "tree_ptr_list.h"
#include <stack>

using namespace datalib;    

template<class T>
tree_ptr_list<T>::tree_ptr_list(int _degree): tree<T>()
{
    //initalization parameter
    degree=_degree;
    root=nullptr;
}

template<class T>
tree_ptr_list<T>::~tree_ptr_list(){

    int j=0;
    //TODO 
    //questo mi genera un segmentation fault, quindi vado ad accedere ad un'area 
    for(typename std::map<T,node<T>*>::iterator i=nodes_map.begin();  i!=nodes_map.end();i++)
    {
        // TODO controllare questo pezzo
        std::cout<<"distruttore: "<< j <<"\n";
        delete i->second;
        // nodes_map.erase(i); //this bring to segmentation fault 
        j++;
    }
}

template<class T>
void tree_ptr_list<T>::addNode(const T* _x,const T *_parent)
{
    node<T>* x_ptr;

    //x_itr and parent_itr are dependent names
    typename std::map<T,node<T>*>::iterator x_itr;
    typename std::map<T,node<T>*>::iterator parent_itr;

    //pre-conditions: 
    //1. the node x to add must be different from nullptr
    //2. the node parent must exists if different from nullptr
    //3. the parent nullptr means that x is the root 
    //4. x will be the root if parent is nullptr and even the root is nullptr
    if(_x==nullptr)
    {
        throw "You cannot add a null node";
        //std::cerr<<"non puoi aggiungere un nodo nullo\n";
        // return;
    }

    //check if x already exists
    x_itr = nodes_map.find(*_x);
    if(x_itr == nodes_map.end())
    {
        x_ptr = new node<T>(*_x); 
        nodes_map.insert({x_ptr->value,x_ptr});
    }

    if(!root)
        root=x_ptr;

    if(_parent) //TODO  //questo è come se fosse if(_parent) da testare il cambiamento 
    {
        parent_itr = nodes_map.find(*_parent);
        if(parent_itr == nodes_map.end()){
            std::string error("the father entered doesn't exist");
            throw error;
        }

        x_ptr->parent = (parent_itr->second);

        //update children of the parent
        (x_ptr->parent)->addChildren({x_ptr});
    }
    else
    {
        if(x_ptr==root)
            x_ptr->parent=nullptr;
        else
            x_ptr->parent=root;
    }
}

//return the number of sons for the node x 
template<class T>
int tree_ptr_list<T>::getDegree(const T &_x)
{
    return nodes_map.find(_x)->second->node_list.size();
}

//return the pointer to the node of a 
//todo vedere, non mi conviene restituire un puntatore

template<class T>
T tree_ptr_list<T>::getParent(const T &_x)
{
    //to see if is convenient to return a reference, the client 
    //what he can do with a reference of node?
    // return *((nodes_map.find(_x)->second->parent)->value);

	//TODO da rifare


}

template<class T>
std::list<T>& tree_ptr_list<T>::getChildren(const T &_x){

    // typename std::map<T,node<T>*>::iterator itr=nodes_map.find(_x);

    // if(itr!=nodes_map.end())
    // {
    //     return (nodes_map.find(_x)->second->node_list);
    // }

	//TODO da rivedere

}


template<class T>
void tree_ptr_list<T>::visitDFS(const T* _root)
{
    //initialize for stack
    typename std::stack<node<T>> s;
    typename std::map<T,node<T>*>::iterator itr;

    //pre-conditions: if the node isn't in the tree, return error
    itr = nodes_map.find(_root->value);
    if(itr==nodes_map.end())
    {
        throw " the node entered for start the visit doesn't exists\n";
        // std::cerr<<"errore, non c'è il nodo per poter fare la visita\n";
        // return;
    }

    s.push(*(*itr).second);
    while(!s.empty())    
    {
        node<T> *u = &s.top();
        s.pop();             //pop don't return the value

        //todo vedere se è corretto, non mi fido
        if(u)
        {
            //visit u
            std::cout<<u->value<<"\n";
            typename std::list<node<T>*> childrens=getChildren(*u);
            typename std::list<node<T>*>::iterator itr;

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


template<class T>
void tree_ptr_list<T>::showTree()
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


template<class T>
void tree_ptr_list<T>::showTreePtr()
{
    std::cout<<std::endl;
    for(auto& n: nodes_map)
    {
        if(n.second->parent!=nullptr){
            std::cout<<((n.second)->parent)<<"<---";
        }
        else 
            std::cout<<"null"<<"<---";
    
        std::cout<<n.second<<" --->  ";
        //print the sons if the list isn't empty
        if(!n.second->node_list.empty())
        {
            for(auto& child: n.second->node_list)
                std::cout<<child<<" ";
        }
        else 
            std::cout<<"null";

        std::cout<<std::endl;
    }
}

//private function
template <class T>
std::list<node<T>*>& tree_ptr_list<T>::getNodeList(node<T>* _x){

            typename std::map<T,node<T>*>::iterator x_itr;
            x_itr = nodes_map.find(_x->value);
            if(x_itr != nodes_map.end()){
                return (x_itr->second)->node_list;
            }
            else throw "boh";

};


template<class T>
void tree_ptr_list<T>::showTree2()
{
    std::cout<<std::endl;

}