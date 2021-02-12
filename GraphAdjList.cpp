#include "GraphAdjList.h"
#include <list>

GraphAdjList::GraphAdjList(const std::vector<Edge> &_edges)
{
    for(auto &edge: _edges)
        addEdge(*edge.src,*edge.dest);
}

//add an Edge O(n)
void GraphAdjList::addEdge(const Node &x,const Node &y)
{
    //TODO si può migliorare utilizzando addNode? 
    //if the adjList don't have the src node then add the adjList in the adjLists
    std::map<int,std::list<Node*>>::iterator itr_src = adj_lists.find(x.value);
    std::map<int,std::list<Node*>>::iterator itr_dest = adj_lists.find(y.value);

    Node *src;
    Node *dest;
    
    //create node src if doesn't exist else get the pointer of the node in the list
    if(itr_src == adj_lists.end())
        src=new Node(x.value);
    else
        src = *(itr_src->second).begin(); 

    //create node dest if doesn't exist else get the pointer of the node in the list
    if(itr_dest == adj_lists.end())
        dest = new Node(y.value);
    else 
        dest= *(itr_dest->second).begin(); 


    //add the node in the edge if doesn't exist in adjList 
    if(itr_src == adj_lists.end() && itr_dest==adj_lists.end())
    {
        adj_lists.insert(std::pair<int,std::list<Node*>>(src->value,{src,dest}));
        adj_lists.insert(std::pair<int,std::list<Node*>>(dest->value,{dest}));
        num_node+=2;
        num_edge++;
    }
    //else if  add only an edge in the list of the node 
    else if(itr_src == adj_lists.end()){
        //adj_lists.push_back({src,dest}); 
        adj_lists.insert(std::pair<int,std::list<Node*>>(src->value,{src,dest}));
        num_node++;
        num_edge++;
    }
    else if(itr_dest==adj_lists.end()){
        (itr_src->second).push_back({dest});
        adj_lists.insert(std::pair<int,std::list<Node*>>(dest->value,{dest}));
        num_edge++;
        num_node++;
    }
    else
    {
        (itr_src->second).push_back({dest}); 
        num_edge++;
    }
    
}

void GraphAdjList::addEdge(const Edge &_edge){
    addEdge(*_edge.src,*_edge.dest);
}


void GraphAdjList::addNode(const Node &x){

    Node *src=new Node(x);

    std::map<int,std::list<Node*>>::iterator itr= adj_lists.find(x.value);
    if(itr==adj_lists.end()){
        adj_lists.insert(std::pair<int,std::list<Node*>>(x.value,{src}));
        num_node++;
    }
}

void GraphAdjList::deleteNode(const Node &x){

    std::map<int,std::list<Node*>>::iterator itr_x= adj_lists.find(x.value);
    std::map<int,std::list<Node*>>::iterator itr; 

    //TODO segmentation fault qui nel remove nella lista
    for(itr=adj_lists.begin(); itr!= adj_lists.end();itr++)
    {
        //delete the eventual in the other adjacenty list if exists
        if(itr!=itr_x)
        {
            itr->second.remove(*itr_x->second.begin());
            /*
            //delete node in the adjList if exists
            for(auto& node: itr->second){       //per ogni nodo nella lista di adiacenza 
                //std::cout<<itr->second<<
                std::cout<<"che problema ci sta: "<<node->value<<"\n";
                if(x.value == node->value)
                {
                    std::cout<<"boh1\n";
                    itr->second.remove(node);
                    std::cout<<"boh2\n";
                }
            }
            */
        }

    }
    
    //get a pointer to the node to delete 
    Node* to_delete = *(itr_x->second).begin();
    
    adj_lists.erase(itr_x);

    delete to_delete;
        //this generate memory leakthis generate memory leak
        //TODO destroy the node 

}


void GraphAdjList::deleteEdge(const Node &x,const Node &y)
{

    std::map<int,std::list<Node*>>::iterator itr_y= adj_lists.find(x.value);

    for(auto& node: adj_lists)
        if(node.first==x.value)
            node.second.remove(*itr_y->second.begin());

}


void GraphAdjList::deleteEdge(const Edge &_edge){
    deleteEdge(*_edge.src,*_edge.dest);

}

void GraphAdjList::showGraph() const{

    for (auto &node: adj_lists){
        // print current vertex number
        std::cout << (*(node.second).begin())<< " --> ";
        // print all neighboring vertices of vertex i
        for(std::list<Node*>::const_iterator it = ++((node.second).cbegin()); it!=(node.second).cend(); it++)
            std::cout<<(*it)<<" ";
        
        std::cout << std::endl;
    }
}

void GraphAdjList::showGraphValue() const{

    for (auto &node: adj_lists){
        // print current vertex number
        std::cout << (*(node.second).begin())->value<< " --> ";
        // print all neighboring vertices of vertex i
        for(std::list<Node*>::const_iterator it = ++((node.second).cbegin()); it!=(node.second).cend(); it++)
            std::cout<<(*it)->value<<" ";
        
        std::cout << std::endl;
    }
}



