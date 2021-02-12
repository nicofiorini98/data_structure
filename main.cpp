#include <iostream> 
#include "AdjacencyList.h"
#include "AdjList.h"
#include "GraphAdjList.h"
#include "TreeVectorFather.h"

 
int main(){

#if 1 
    Node a(0);    
    Node l(1);    
    Node b(2);    
    Node e(3);    
    Node r(4);    
    Node o(5);    
    
    TreeVectorFather tree;


    tree.addNode(&a);
    tree.addNode(&l);
    tree.addNode(&b);
    
    tree.addNode(&e,&l);
    tree.addNode(&r,&l);
    tree.addNode(&o,&b);


    tree.showTree();
        


#endif

#if 0

    Node a(0);
    Node b(1);
    Node c(2);
    Node d(3);
    Node e(4);
    
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
    Node f(5);
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
