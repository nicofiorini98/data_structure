#include "AdjList.h"

AdjList::AdjList(std::vector<Edge> const &_edges): Graph()
{
    for(auto &edge: _edges)
        addEdge(*edge.src,*edge.dest);
    //generate_key();
}

AdjList::~AdjList(){

    for(auto& node: adj_lists){
        delete *node.begin();
    }
}



//return the number of neighboor of the node in the position pos 
int AdjList::grade(int pos)
{
    return adj_lists[pos].size()-1;
}

std::vector<std::list<Node*>>::iterator AdjList::getList(const Node &x)
{
    std::vector<std::list<Node*>>::iterator itr;

    for(itr=adj_lists.begin();itr!=adj_lists.end();itr++)
        if((*(*itr).begin())->value==x.value)
            return itr;

    return itr;

}

void AdjList::generate_key(int start)
{
    for(int i=start;i<adj_lists.size();i++)
        (*adj_lists[i].begin())->pos=i;
}

 // print adjacency list representation of graph
void AdjList::showGraph() const{

    for (auto &node: adj_lists){
        // print current vertex number
        std::cout << (*node.begin())<< " --> ";
        // print all neighboring vertices of vertex i
        for(std::list<Node*>::const_iterator it = ++(node.cbegin()); it!=node.cend(); it++)
            std::cout<<(*it)<<" ";
        
        std::cout << std::endl;
    }
}

void AdjList::showGraphValue() const{

    for (auto &node: adj_lists){
        // print current vertex number
        std::cout << (*node.begin())->value<< " --> ";
        // print all neighboring vertices of vertex i
        for(std::list<Node*>::const_iterator it = ++(node.cbegin()); it!=node.cend(); it++)
            std::cout<<(*it)->value<<" ";
        
        std::cout << std::endl;
    }
}
//return the incident edge of the Node x
void AdjList::getIncidentEdge(const Node &x){
     //TODO    


}          

void AdjList::getAdjNode(const Node &x){
    //TODO 
    

}

//add a Node O(n)
void AdjList::addNode(const Node &x)
{
    std::vector<std::list<Node*>>::iterator itr=getList(x);

    if(itr==adj_lists.end()){
        Node *src=new Node(x);
        adj_lists.push_back({src});
        std::list<Node*> a;
        (*adj_lists[num_node].begin())->pos=num_node;
        num_node++;
    }
}

//add an Edge O(n)
void AdjList::addEdge(const Node &x,const Node &y)
{
    //if the adjList don't have the src node then add the adjList in the adjLists
    std::vector<std::list<Node*>>::iterator itr_src = getList(x);
    std::vector<std::list<Node*>>::iterator itr_dest = getList(y);

    Node *src;
    Node *dest;
    
    //create node src if doesn't exist else get the pointer of the node in the list
    if(itr_src == adj_lists.end())
        src=new Node(x.value);
    else
        src = *itr_src->begin();

    //create node dest if doesn't exist else get the pointer of the node in the list
    if(itr_dest == adj_lists.end())
        dest = new Node(y.value);
    else 
        dest= *itr_dest->begin();


    //add node lists if it doesn't exist in adjList else add only an edge in the list of the node 
    if(itr_src == adj_lists.end() && itr_dest==adj_lists.end())
    {
        adj_lists.push_back({src,dest}); 
        adj_lists.push_back({dest});
        num_node+=2;
        num_edge++;
        //std::cout <<" aggiunto arco" <<src->value<<" ," << dest->value<<"\n";
    }
    else if(itr_src == adj_lists.end()){
        adj_lists.push_back({src,dest}); 
        num_node++;
        num_edge++;
    }
    else if(itr_dest==adj_lists.end()){
        (*itr_src).push_back({dest});
        adj_lists.push_back({dest});
        num_edge++;
        num_node++;
    }
    else
    {
        (*itr_src).push_back({dest}); 
        num_edge++;
    }

    generate_key(); //O(n) TODO evitare questo
}

void AdjList::showGraphPos() const{

    for (auto &node: adj_lists){
        // print current vertex number
        std::cout << (*node.begin())->pos<< " --> ";
        // print all neighboring vertices of vertex i
        for(std::list<Node*>::const_iterator it = ++(node.cbegin()); it!=node.cend(); it++)
            std::cout<<(*it)->pos<<" ";
        
        std::cout << std::endl;
    }

}




