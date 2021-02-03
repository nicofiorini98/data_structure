#include <iostream> 
#include "AdjacencyList.h"

int main(){

    Node a,b,c,d;
    std::vector<Edge> edges;
    a.value=0;
    b.value=1;
    c.value=2;
    d.value=3;

    Edge ab;
    ab.src=a;
    ab.dest=b;

    Edge bc;
    bc.src=b;
    bc.dest=c;

    Edge ac;
    ac.src=a;
    ac.dest=c;

    Edge cd;
    cd.src=c;
    cd.dest=d;

    Edge da;
    da.src=d;
    da.dest=a;

    Edge dc;
    dc.src=d;
    dc.dest=c;

    edges.push_back(ab);
    edges.push_back(ac);
    edges.push_back(bc);
    edges.push_back(cd);
    edges.push_back(da);
    edges.push_back(dc);
 
    //AdjacencyList(edges);
    AdjacencyList boh(edges,edges.size());

    printGraph(boh,edges.size());

    
    return 0;

}
