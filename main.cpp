#include <iostream> 
#include "AdjacencyList.h"
#include "AdjList.h"


#define lista_adiacenza 0
 
int main(){
/*
#if lista_adiacenza

    Node a,b,c,d;
    std::vector<Edge> edges;
    a.value=0;
    b.value=1;
    c.value=2;
    d.value=3;

    edges.push_back({a,b});
    edges.push_back({b,c});
    edges.push_back({a,c});
    edges.push_back({c,d});
    edges.push_back({d,a});
    edges.push_back({d,c});

    AdjacencyList boh(edges);

    Node e;
    e.value=4;

    boh.addNode(e);
    boh.addEdge(e,a);
    boh.addEdge(e,b);

    boh.addEdge(a,e);
    boh.showGraph();

    std::cout<<"\n il grado del nodo a è: "<<boh.grade(a);
*/    


    Node *a = new Node(0);
    Node *b = new Node(1);
    Node *c = new Node(2);
    Node *d = new Node(3);
    //Node *d = new Node(3);

    std::vector<Edge> edges;

    edges.push_back({a,b});
    edges.push_back({a,c});
    edges.push_back({b,c});
    edges.push_back({c,d});
    edges.push_back({d,a});
    //edges.push_back({g}); //TODO to correct this 

    AdjList graph(edges);

    //Node h(8);
    //graph.addNode(h);
    graph.showGraph();
    std::cout<<std::endl;
    graph.showGraphValue();



    return 0;


}
