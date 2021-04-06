#include <iostream> 
#include "edge.h"
#include "node.h"
#include "graph_adj_list.h"
#include "tree_parent_vector.h"
#include "tree_general.h"
#include <fstream>
//#include <chrono>
#include <vector>

//using namespace std;


// //using namespace std::chrono 
// high_resolution_clock::time_point t1= high_resolution_clock::now();

    
// high_resolution_clock::time_point t2= high_resolution_clock::now();

// duration<double> time_span=duration_cast<duration<double>>(t2-t1);

// std::cout<<"it took the time"<<time_span.count()<<"seconds.";

#define VECTOR_FATHER 0
#define ADJ_LISTS 0
#define TREE_GENERAL 1

//using namespace datalib;

int main()
{



/* std::cout << 1234.56789 << "\t\t(defaultfloat)\n"
 // \t\t to line up columns
<< std::fixed << 1234.56789 << "\t(fixed)\n"
< < std::scientific << 1234.56789 << "\t(scientific)\n";
*/

#if TREE_GENERAL

    datalib::node<int> a0{0},l1{0},b2{0};
    datalib::node<int> e3{0},r4{0},o5{0},n{0};

    std::ifstream ist{"../node.txt"};
    //std::ifstream ist2{"../insert_tree.txt"};

    //input node from a file
    ist>>a0>>l1>>b2>>e3>>r4>>o5>>n;
    std::cout<<a0<<l1;

    //n=a0;

    //ist.open( "../insert_tree.txt",std::ios::in);

    //std::list<node*> children;

    //tree_general t;
    //tree_general tfile;


    //ist2>>tfile;

    //t.addNode(&a0,nullptr,{l1,b2}); //optional
    // t.addNode(&n,nullptr);
    // t.addNode(&l1,&a0);
    // //t.addNode(&b2,&a0,{o5}); //optional  // mi fa andare in segmentation fault
    // t.addNode(&b2,&a0);
    // t.addNode(&e3,&l1);
    // t.addNode(&r4,&l1);
    // t.addNode(&o5,&b2); 

    //t.showTree();

    //std::cout<<"\n"<<n;

    //tfile.showTreePtr();

    //t.visitDFS(&a0);
    //std::cout<<"grado nodo a: "<<t.getDegree(a0)<<"\n";

#endif

#if TREE_VECTOR_FATHER

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

#if GRAPH_ADJ_LISTS

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
