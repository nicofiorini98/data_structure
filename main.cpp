#include <iostream> 
#include "AdjacencyList.h"

#define lista_adiacenza 1
 
int main(){

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

    boh.showGraph();
    
#endif 

    return 0;

}
