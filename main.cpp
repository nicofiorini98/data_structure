#include <iostream> 
#include "AdjacencyList.h"

int main(){

    Node a,b,c,d;
    vector<Edge> edges;
    a.key=0;
    b.key=1;
    c.key=2;
    d.key=3;

    Edge ab;
    ab.src=a;
    ab.dest=b;

    Edge bc;
    bc.src=b;
    bc.dest=c;

    Edge ac;
    bc.src=a;
    bc.dest=c;

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
    edges.push_back(bc);
    edges.push_back(cd);
    edges.push_back(da);
    edges.push_back(dc);
 
    AdjacencyList boh(edges,6);
    

    printGraph(boh,6);

    
    return 0;

}
