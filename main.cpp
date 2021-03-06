#include <iostream> 
#include "graph_adj_list.h"
#include "tree_parent_vector.h"
#include "tree_children_list.h"

#include <chrono>

using namespace std::chrono;


// //using namespace std::chrono 
// high_resolution_clock::time_point t1= high_resolution_clock::now();

    
// high_resolution_clock::time_point t2= high_resolution_clock::now();

// duration<double> time_span=duration_cast<duration<double>>(t2-t1);


// std::cout<<"it took the time"<<time_span.count()<<"seconds.";



#define vector_father 0
#define adj_lists 0
#define children_list 1

using namespace datalib;

int main(){

#if children_list

    node a(0);
    node l(1);
    node b(2); 
    node e(3);
    node r(4); 
    node o(5);
    node d(3);

    tree_children_list t;
    t.addNode(&a);
    t.addNode(&l,&a);
    
    t.addNode(&b,&a);
    t.addNode(&e,&l);
    t.addNode(&r,&l);
    t.addNode(&o,&b);
    t.showTree();
    
#endif

#if tree_vector_father

    node a(0);
    node l(1);
    node b(2); 
    node e(3);
    node r(4); 
    node o(5);
    
    tree_parent_vector t;


    t.addNode(&a);
    t.addNode(&l);
    t.addNode(&b);
    
    t.addNode(&e,&l);
    t.addNode(&r,&l);
    t.addNode(&o,&b);

    t.showTree();
    t.showTree();

#endif

#if graph_adj_lists

    node a(0);
    node b(1);
    node c(2);
    node d(3);
    node e(4);
    
    std::vector<Edge> edges;

    edges.push_back({&c,&d});
    edges.push_back({&d,&a});
    edges.push_back({&a,&c});
    edges.push_back({&b,&c});
    edges.push_back({&a,&b});
    //edges.push_back({&a,nullptr}); //TODO gestire nullptr 


    GraphAdjList *graph=new GraphAdjList(edges);
    //graph->addNode(e);
    graph->addEdge(e,b);
    graph->addEdge({&a,&e});
    node f(5);
    graph->addNode(f);
    graph->addEdge(e,f);
    graph->addEdge(a,f);

    graph->deleteNode(f);

    //graph->deleteEdge(a,c);

    //graph.addNode(h);
    //graph->showGraph();
    std::cout<<std::endl;
    graph->showGraphValue();



    //delete graph;
    //std::cout<<"grafo distrutto\n";
#endif



    return 0;


}
