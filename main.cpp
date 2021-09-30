#include <iostream> 
#include <fstream>
#include <vector>
#include "node.h"
#include "edge.h"
#include "graph_adj_list.h"
#include "tree_parent_vector.h"
#include "tree_general.h"
#include "tree_pos_vector.h"
//#include <chrono>

//using namespace std;
// //using namespace std::chrono 
// high_resolution_clock::time_point t1= high_resolution_clock::now();

// high_resolution_clock::time_point t2= high_resolution_clock::now();

// duration<double> time_span=duration_cast<duration<double>>(t2-t1);

// std::cout<<"it took the time"<<time_span.count()<<"seconds.";

#define VECTOR_FATHER 0
#define ADJ_LISTS 0
#define TREE_GENERAL 1
#define POS_VECTOR 0
#define PROVA 0 

int main()
{
/* std::cout << 1234.56789 << "\t\t(defaultfloat)\n"
 // \t\t to line up columns
<< std::fixed << 1234.56789 << "\t(fixed)\n"
< < std::scientific << 1234.56789 << "\t(scientific)\n";
*/

    // datalib::node<std::string> a0{"a"},l1{"l"},b2{"b"};
    // datalib::node<std::string> e3{"e"},r4{"r"},o5{"o"},n{"n"};

    // datalib::node<int> a0{0},l1{1},b2{2};
    // datalib::node<int> e3{3},r4{4},o5{5},n{6};

    int a0{0},l1{1},b2{2};
    int e3{3},r4{4},o5{5},n{6};

    std::string a{"a"},l{"l"},b{"b"};
    std::string e{"e"},r{"r"},o{"o"};

#if POS_VECTOR 


    std::cout<<"Prova vettore posizione: \n";
    datalib::tree_pos_vector<std::string> t(2,3);

    try{
        t.addNode(&a);
        t.addChild(&a,&l);
        t.addNode(&b,&a);
        t.addNode(&e,&l);
        t.addNode(&r,&l);
        t.addNode(&o,&b);
    }catch(std::string &error){
        std::cout<<error;
    }

    std::cout<<t;

#endif

#if PROVA

    std::vector<node<int>*> vec_node;

    vec_node.push_back(&a0);
    vec_node.push_back(&b2);
    vec_node.push_back(&e3);
    vec_node.push_back(&l1);

    std::vector<node<int>*>::iterator trovato = prova_trova(vec_node.begin(),vec_node.end(),&l1);

    if(trovato != vec_node.end()){
        std::cout<<"vettore trovato: "<<*trovato<<"\n";
    }

    int i=0;
    for(auto &n: vec_node){
        std::cout<<"pointer: "<<n<<"\n";
        i++;
    }

#endif

#if TREE_GENERAL


    // datalib::node<int> a0{0},l1{1},b2{2};
    // datalib::node<int> e3{3},r4{4},o5{5};

    // std::ifstream ist{"../node.txt"};
    // std::ifstream ist2{"../insert_tree.txt"};
    std::ofstream os{"../output.txt"};

    //input node from a file
    //ist>>a0>>l1>>b2>>e3>>r4>>o5>>n;
    //std::cout<<a0<<l1;

    //n=a0;

    // ist.open( "../insert_tree.txt",std::ios::in);

    //std::list<node*> children;

    tree_general<std::string> *t = new tree_general<std::string>;
    // tree_general<std::string> tfile;
    // ist2>>tfile;

    t->addNode(&a);
    t->addNode(&l,&a);
    t->addNode(&b,&a);
    t->addNode(&e,&l);
    t->addNode(&r,&l);
    t->addNode(&o,&b); 

    os<<*t;

    /* Non viene distrutto in maniera appropriata */
    // tfile.showTree();
    // tfile.showTreePtr();

    // try{
    //     t.visitDFS(&a0);
    // }catch(const char* msg){
    //     std::cerr<<msg<<"\n";
    // }

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
