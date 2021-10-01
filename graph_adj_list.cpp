#pragma once
#include "graph_adj_list.h"
#include <list>

using namespace datalib;

// template<class T>
// graph_adj_list<T>::graph_adj_list(const std::vector<Edge> &_edges)
// {
//     for(auto &edge: _edges)
//         addEdge(*edge.src,*edge.dest);
// }


//add an Edge O(n)
template<class T>
void graph_adj_list<T>::addEdge(const node<T> &x,const node<T> &y)
{
    //if the adjList don't have the src node<T> then add the adjList in the adjLists
    std::map<int,std::list<node<T>*>>::iterator itr_src = adj_lists.find(x.value);
    std::map<int,std::list<node<T>*>>::iterator itr_dest = adj_lists.find(y.value);

    node<T> *src;
    node<T> *dest;
    
    //create node<T> src if doesn't exist else get the pointer of the node<T> in the list
    if(itr_src == adj_lists.end())
        src=new node<T>(x.value);
    else
        src = *(itr_src->second).begin(); 

    //create node<T> dest if doesn't exist else get the pointer of the node<T> in the list
    if(itr_dest == adj_lists.end())
        dest = new node<T>(y.value);
    else 
        dest= *(itr_dest->second).begin(); 


    //add the node<T> in the edge if doesn't exist in adjList 
    if(itr_src == adj_lists.end() && itr_dest==adj_lists.end())
    {
        adj_lists.insert(std::pair<int,std::list<node<T>*>>(src->value,{src,dest}));
        adj_lists.insert(std::pair<int,std::list<node<T>*>>(dest->value,{dest}));
        num_node<T>+=2;
        num_edge++;
    }
    //else if  add only an edge in the list of the node<T> 
    else if(itr_src == adj_lists.end()){
        //adj_lists.push_back({src,dest}); 
        adj_lists.insert(std::pair<int,std::list<node<T>*>>(src->value,{src,dest}));
        num_node<T>++;
        num_edge++;
    }
    else if(itr_dest==adj_lists.end()){
        (itr_src->second).push_back({dest});
        adj_lists.insert(std::pair<int,std::list<node<T>*>>(dest->value,{dest}));
        num_edge++;
        num_node<T>++;
    }
    else
    {
        (itr_src->second).push_back({dest}); 
        num_edge++;
    }
    
}

// template<class T>
// void graph_adj_list<T>::addEdge(const Edge &_edge){
//     addEdge(*_edge.src,*_edge.dest);
// }


template<class T>
void graph_adj_list<T>::addNode(const node<T> &x){

    //create node<T> with copy costructor
    node<T> *src=new node<T>(x);

    std::map<int,std::list<node<T>*>>::iterator itr= adj_lists.find(x.value);

    if(itr==adj_lists.end()){
        adj_lists.insert(std::pair<int,std::list<node<T>*>>(x.value,{src}));
        num_node<T>++;
    }
}

template<class T>
void graph_adj_list<T>::deleteNode(const node<T> &x){

    std::map<int,std::list<node<T>*>>::iterator itr_x= adj_lists.find(x.value);
    std::map<int,std::list<node<T>*>>::iterator itr; 

    //TODO segmentation fault qui nel remove nella lista
    for(itr=adj_lists.begin(); itr!= adj_lists.end();itr++)
    {
        //delete the eventual in the other adjacenty list if exists
        if(itr!=itr_x)
        {
            itr->second.remove(*itr_x->second.begin());
            /*
            //delete node<T> in the adjList if exists
            for(auto& node<T>: itr->second){       //per ogni nodo nella lista di adiacenza 
                //std::cout<<itr->second<<
                std::cout<<"che problema ci sta: "<<node<T>->value<<"\n";
                if(x.value == node<T>->value)
                {
                    std::cout<<"boh1\n";
                    itr->second.remove(node<T>);
                    std::cout<<"boh2\n";
                }
            }
            */
        }

    }
    
    //get a pointer to the node<T> to delete 
    node<T>* to_delete = *(itr_x->second).begin();
    
    adj_lists.erase(itr_x);

    delete to_delete;
        //this generate memory leakthis generate memory leak
        //TODO destroy the node<T> 

}


template<class T>
void graph_adj_list<T>::deleteEdge(const node<T> &x,const node<T> &y)
{

    std::map<int,std::list<node<T>*>>::iterator itr_y= adj_lists.find(x.value);

    for(auto& node<T>: adj_lists)
        if(node<T>.first==x.value)
            node<T>.second.remove(*itr_y->second.begin());

}



// template<class T>
// void graph_adj_list<T>::deleteEdge(const Edge &_edge){
//     deleteEdge(*_edge.src,*_edge.dest);

// }

template<class T>
void graph_adj_list<T>::showGraph() const{

    for (auto &n: adj_lists){
        // print current vertex number
        std::cout << (*(n.second).begin())<< " --> ";
        // print all neighboring vertices of vertex i
        for(std::list<node<T>*>::const_iterator it = ++((n.second).cbegin()); it!=(n.second).cend(); it++)
            std::cout<<(*it)<<" ";
        
        std::cout << std::endl;
    }
}

template<class T>
void graph_adj_list<T>::showGraphValue() const{

    for (auto &n: adj_lists){
        // print current vertex number
        std::cout << (*(n.second).begin())->value<< " --> ";
        // print all neighboring vertices of vertex i
        for(std::list<node<T>*>::const_iterator it = ++((n.second).cbegin()); it!=(n.second).cend(); it++)
            std::cout<<(*it)->value<<" ";
        
        std::cout << std::endl;
    }
}



