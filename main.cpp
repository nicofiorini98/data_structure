#include <iostream> 
#include "AdjacencyList.h"
#include "AdjList.h"


#define lista_adiacenza 1
 
int main(){

#if lista_adiacenza

    Node a(0);
    Node b(1);
    Node c(2);
    Node d(3);
    Node e(4);
    //Node *d = new Node(3);

    std::vector<Edge> edges;

    edges.push_back({&c,&d});
    edges.push_back({&d,&a});
    edges.push_back({&a,&c});
    edges.push_back({&b,&c});
    edges.push_back({&a,&b});

    AdjList *graph=new AdjList(edges);
    graph->addNode(e);


    //graph.addNode(h);
    graph->showGraph();
    std::cout<<std::endl;
    graph->showGraphPos();
    std::cout<<std::endl;
    graph->showGraphValue();

    delete graph;

    std::cout<<"grafo distrutto\n";


#endif


    return 0;


}
