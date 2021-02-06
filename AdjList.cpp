#include "AdjList.h"

AdjList::AdjList(std::vector<Edge> const &_edges){

    for(auto &edge: _edges){
        //if the adjList don't have the src node then add the adjList in the adjLists
        std::vector<std::list<Node>>::iterator it_src = getList(*edge.src);
        std::vector<std::list<Node>>::iterator it_dest = getList(*edge.dest);

        //add node lists if it doesn't exist in adjList else add only an edge in the list of the node 
        if(it_src == adj_lists.end())
            adj_lists.push_back({*edge.src,*edge.dest}); //TODO
        else
            (*it_src).push_back({*edge.dest});
         
        //add the destination edge if isn't in the adjList
        if(it_dest==adj_lists.end())
            adj_lists.push_back({*edge.dest});
    }


    generate_key();

    std::cout<<"il grado del nodo "<<(*adj_lists[1].begin()).value<<" è :" <<grade((*adj_lists[1].begin()).pos)<<"\n";

}

int AdjList::grade(int pos)
{
    return adj_lists[pos].size()-1;
}


std::vector<std::list<Node>>::iterator AdjList::getList(Node x)
{
    std::vector<std::list<Node>>::iterator itr;

    for(itr=adj_lists.begin();itr!=adj_lists.end();itr++)
        if((*(*itr).begin()).value==x.value)
            return itr;

    return itr;

}

void AdjList::generate_key(int start)
{
    for(int i=start;i<adj_lists.size();i++)
    {
        (*adj_lists[i].begin()).pos=i;
    }
}

 // print adjacency list representation of graph
void AdjList::showGraph() const{

    for (auto &node: adj_lists){
        // print current vertex number
        std::cout << (*node.begin()).value << " --> ";
        // print all neighboring vertices of vertex i
        for(std::list<Node>::const_iterator it = ++(node.cbegin()); it!=node.cend(); it++)
            std::cout<<(*it).value<<" ";
        
        std::cout << std::endl;
    }
}
