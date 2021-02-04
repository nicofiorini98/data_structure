#include "AdjacencyList.h"

//shortcut for iterator 
using  list_list_itr=  std::list<std::list<Node>>::iterator ;
using list_it = std::list<Node>::iterator;

//Costructor with Edge
AdjacencyList::AdjacencyList(std::vector<Edge> const &_edges)
{

    for(auto &edge: _edges){
        //if the adjList don't have the src node then add the adjList in the adjLists
        list_list_itr it_src = getList(edge.src);
        list_list_itr it_dest = getList(edge.dest);

        //add node lists if it doesn't exist in adjList else add only an edge in the list of the node 
        if(it_src == adjLists.end())
            adjLists.push_back({edge.src,edge.dest});
        else
            (*it_src).push_back({edge.dest});
         
        //add the destination edge if isn't in the adjList
        if(it_dest==adjLists.end())
            adjLists.push_back({edge.dest});
    }
}

//get adjList of a node
list_list_itr AdjacencyList::getList(Node x){

     list_list_itr it;
     for(it=adjLists.begin();it!=adjLists.end();it++)
        if((*(*it).begin()).value==x.value)
            return it;

    return it;
}

bool AdjacencyList::hasNode(const Node &x){

         //return true if the node will found in the first 
         for(auto& adjList: adjLists)
         {
             if((*(adjList.begin())).value==x.value)
                 return true;
             return false;
         }
         return false;
    }


void AdjacencyList::addNode(Node x){
        
    //add node lists if it doesn't exist else add an edge in the list of the node 
    //std::list<Node> adjList;
    //adjList.push_back(x);
    
    adjLists.push_back({x});

}                

void AdjacencyList::addEdge(Node x,Node y){

    list_list_itr it = getList(x);

    //add node lists if it doesn't exist else add an edge in the list of the node 
    if(it == adjLists.end()){
        adjLists.push_back({x,y});
    }
    else
        (*it).push_back({y});
}

int AdjacencyList::grade(Node x){
    std::list<std::list<Node>>::iterator it = this->getList(x);
    return (*it).size()-1;
}


 // print adjacency list representation of graph
void AdjacencyList::showGraph() const{

    for (auto &node: this->adjLists ){
        // print current vertex number
        std::cout << (*node.begin()).value << " --> ";
        // print all neighboring vertices of vertex i
        for(std::list<Node>::const_iterator it = ++(node.cbegin()); it!=node.cend(); it++)
            std::cout<<(*it).value<<" ";
        
        std::cout << std::endl;
    }
}

