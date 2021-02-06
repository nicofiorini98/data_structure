#include "AdjList.h"

AdjList::AdjList(std::vector<Edge> const &_edges): Graph()
{

    for(auto &edge: _edges){
        //if the adjList don't have the src node then add the adjList in the adjLists
        std::vector<std::list<Node>>::iterator it_src = getList(*edge.src);
        std::vector<std::list<Node>>::iterator it_dest = getList(*edge.dest);

        //add node lists if it doesn't exist in adjList else add only an edge in the list of the node 
        if(it_src == adj_lists.end()){
            adj_lists.push_back({*edge.src,*edge.dest}); //TODO
            num_node++;
            num_edge++;
        }
        else{
            (*it_src).push_back({*edge.dest}); 
            num_edge++;
        }
         
        //add the destination edge if isn't in the adjList
        if(it_dest==adj_lists.end()){
            adj_lists.push_back({*edge.dest});
            num_node++;
        }
    }
    generate_key();
    //std::cout<<"il grado del nodo "<<(*adj_lists[1].begin()).value<<" è :" <<grade((*adj_lists[1].begin()).pos)<<"\n";

}


//return the number of neighboor of the node in the position pos 
int AdjList::grade(int pos)
{
    return adj_lists[pos].size()-1;
}

std::vector<std::list<Node>>::iterator AdjList::getList(const Node &x)
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
        (*adj_lists[i].begin()).pos=i;
}

 // print adjacency list representation of graph
void AdjList::showGraph() const{

    for (auto &node: adj_lists){
        // print current vertex number
        std::cout << (*node.begin()).pos << " --> ";
        // print all neighboring vertices of vertex i
        for(std::list<Node>::const_iterator it = ++(node.cbegin()); it!=node.cend(); it++)
            std::cout<<(*it).pos<<" ";
        
        std::cout << std::endl;
    }
}

//return the incident edge of the Node x
void AdjList::getIncidentEdge(const Node &x){
     //TODO    


}          

void AdjList::getAdjNode(const Node &x){
    

}

//add a Node O(n)
//TODO Do I have to guarantee the uniqueness?
void AdjList::addNode(const Node &x)
{
    std::vector<std::list<Node>>::iterator itr=getList(x);
    if(itr==adj_lists.end()){
        adj_lists.push_back({x});
        (*adj_lists[num_node].begin()).pos=num_node;
        num_node++;
    }
}

//add an Edge O(n)
void AdjList::addEdge(const Node &x,const Node &y)
{
    std::vector<std::list<Node>>::iterator itr=getList(x);
    if(itr==adj_lists.end())
    {
        //TODO add pos in the node added
        adj_lists.push_back({x,y});
        num_node++;
        num_edge++;
    }
    else {
        (*itr).push_back(y);
        num_edge++;
    }

}
