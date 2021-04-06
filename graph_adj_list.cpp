// #include "graph_adj_list.h"
// #include <list>

// using namespace datalib;

// graph_adj_list::graph_adj_list(const std::vector<Edge> &_edges)
// {
//     for(auto &edge: _edges)
//         addEdge(*edge.src,*edge.dest);
// }


// //add an Edge O(n)
// void datalib::graph_adj_list::addEdge(const node &x,const node &y)
// {
//     //if the adjList don't have the src node then add the adjList in the adjLists
//     std::map<int,std::list<node*>>::iterator itr_src = adj_lists.find(x.value);
//     std::map<int,std::list<node*>>::iterator itr_dest = adj_lists.find(y.value);

//     node *src;
//     node *dest;
    
//     //create node src if doesn't exist else get the pointer of the node in the list
//     if(itr_src == adj_lists.end())
//         src=new node(x.value);
//     else
//         src = *(itr_src->second).begin(); 

//     //create node dest if doesn't exist else get the pointer of the node in the list
//     if(itr_dest == adj_lists.end())
//         dest = new node(y.value);
//     else 
//         dest= *(itr_dest->second).begin(); 


//     //add the node in the edge if doesn't exist in adjList 
//     if(itr_src == adj_lists.end() && itr_dest==adj_lists.end())
//     {
//         adj_lists.insert(std::pair<int,std::list<node*>>(src->value,{src,dest}));
//         adj_lists.insert(std::pair<int,std::list<node*>>(dest->value,{dest}));
//         num_node+=2;
//         num_edge++;
//     }
//     //else if  add only an edge in the list of the node 
//     else if(itr_src == adj_lists.end()){
//         //adj_lists.push_back({src,dest}); 
//         adj_lists.insert(std::pair<int,std::list<node*>>(src->value,{src,dest}));
//         num_node++;
//         num_edge++;
//     }
//     else if(itr_dest==adj_lists.end()){
//         (itr_src->second).push_back({dest});
//         adj_lists.insert(std::pair<int,std::list<node*>>(dest->value,{dest}));
//         num_edge++;
//         num_node++;
//     }
//     else
//     {
//         (itr_src->second).push_back({dest}); 
//         num_edge++;
//     }
    
// }

// void datalib::graph_adj_list::addEdge(const Edge &_edge){
//     addEdge(*_edge.src,*_edge.dest);
// }


// void datalib::graph_adj_list::addNode(const node &x){

//     //create node with copy costructor
//     node *src=new node(x);

//     std::map<int,std::list<node*>>::iterator itr= adj_lists.find(x.value);

//     if(itr==adj_lists.end()){
//         adj_lists.insert(std::pair<int,std::list<node*>>(x.value,{src}));
//         num_node++;
//     }
// }

// void datalib::graph_adj_list::deleteNode(const node &x){

//     std::map<int,std::list<node*>>::iterator itr_x= adj_lists.find(x.value);
//     std::map<int,std::list<node*>>::iterator itr; 

//     //TODO segmentation fault qui nel remove nella lista
//     for(itr=adj_lists.begin(); itr!= adj_lists.end();itr++)
//     {
//         //delete the eventual in the other adjacenty list if exists
//         if(itr!=itr_x)
//         {
//             itr->second.remove(*itr_x->second.begin());
//             /*
//             //delete node in the adjList if exists
//             for(auto& node: itr->second){       //per ogni nodo nella lista di adiacenza 
//                 //std::cout<<itr->second<<
//                 std::cout<<"che problema ci sta: "<<node->value<<"\n";
//                 if(x.value == node->value)
//                 {
//                     std::cout<<"boh1\n";
//                     itr->second.remove(node);
//                     std::cout<<"boh2\n";
//                 }
//             }
//             */
//         }

//     }
    
//     //get a pointer to the node to delete 
//     node* to_delete = *(itr_x->second).begin();
    
//     adj_lists.erase(itr_x);

//     delete to_delete;
//         //this generate memory leakthis generate memory leak
//         //TODO destroy the node 

// }


// void datalib::graph_adj_list::deleteEdge(const node &x,const node &y)
// {

//     std::map<int,std::list<node*>>::iterator itr_y= adj_lists.find(x.value);

//     for(auto& node: adj_lists)
//         if(node.first==x.value)
//             node.second.remove(*itr_y->second.begin());

// }


// void datalib::graph_adj_list::deleteEdge(const Edge &_edge){
//     deleteEdge(*_edge.src,*_edge.dest);

// }

// void datalib::graph_adj_list::showGraph() const{

//     for (auto &n: adj_lists){
//         // print current vertex number
//         std::cout << (*(n.second).begin())<< " --> ";
//         // print all neighboring vertices of vertex i
//         for(std::list<node*>::const_iterator it = ++((n.second).cbegin()); it!=(n.second).cend(); it++)
//             std::cout<<(*it)<<" ";
        
//         std::cout << std::endl;
//     }
// }

// void datalib::graph_adj_list::showGraphValue() const{

//     for (auto &n: adj_lists){
//         // print current vertex number
//         std::cout << (*(n.second).begin())->value<< " --> ";
//         // print all neighboring vertices of vertex i
//         for(std::list<node*>::const_iterator it = ++((n.second).cbegin()); it!=(n.second).cend(); it++)
//             std::cout<<(*it)->value<<" ";
        
//         std::cout << std::endl;
//     }
// }



