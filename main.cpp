#include <iostream> 
#include <fstream>
#include <sstream>
#include <vector>
#include "node.h"
#include "edge.h"
#include "graph_adj_list.h"
#include "graph_edge_list.h"
#include "graph_inc_list.h"
#include "tree_ptr_list.h"
#include "tree_pos_vector.h"
//#include <chrono>

//using namespace std;
// //using namespace std::chrono 
// high_resolution_clock::time_point t1= high_resolution_clock::now();

// high_resolution_clock::time_point t2= high_resolution_clock::now();

// duration<double> time_span=duration_cast<duration<double>>(t2-t1);

// std::cout<<"it took the time"<<time_span.count()<<"seconds.";

#define VECTOR_FATHER 0
#define TREE_PTR_LIST 0
#define POS_VECTOR 0
#define GRAPH_ADJ_LIST 0
#define GRAPH_EDGE_LIST 0
#define GRAPH_INC_LIST 1
#define PROVA 0 

using namespace datalib;


int main(){

/* std::cout << 1234.56789 << "\t\t(defaultfloat)\n"
 // \t\t to line up columns
<< std::fixed << 1234.56789 << "\t(fixed)\n"
< < std::scientific << 1234.56789 << "\t(scientific)\n";
*/

    // datalib::node<std::string> a0{"a"},l1{"l"},b2{"b"};
    // datalib::node<std::string> e3{"e"},r4{"r"},o5{"o"},n{"n"};

    // datalib::node<int> a0{0},l1{1},b2{2};
    // datalib::node<int> e3{3},r4{4},o5{5},n{6};

    //int a0{0},l1{1},b2{2};
    //int e3{3},r4{4},o5{5},n{6};

    std::string a{"a"},l{"l"},b{"b"};
    std::string e{"e"},r{"r"},o{"o"};



    std::cout<<"\n";

#if POS_VECTOR 


    std::cout<<"Prova vettore posizione: \n";
    datalib::tree_pos_vector<std::string> t(2,3);

    try{
        t.addNode(&a);
        t.addNode(&l,&a);
        t.addNode(&b,&a);
        t.addChild(&l,&a);
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
    vec_node.push_back(&boh;
    graph_inc_list<int> _graph_inc_list;

    _graph_inc_list.addNode(a0);

    _graph_inc_list.shl1);

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

#if TREE_PTR_LIST

    // datalib::node<int> a0{0},l1{1},b2{2};
    // datalib::node<int> e3{3},r4{4},o5{5};

    //std::ifstream is{"../node.txt"};

    std::ifstream ist2{"C:\\Users\\1dnic\\Desktop\\my_project\\data_structure\\insert_tree.txt"};
    //std::ofstream os{"../output.txt"};

	//ist2.open( "C:\Users\1dnic\Desktop\my_project\data_structure\insert_tree.txt",std::ios::in);
    /*while(ist2.eof())
    {
        std::string a;
        std::cout<< a;
    }*/

    //std::list<node*> children;

    auto *t = new tree_ptr_list<std::string>(2);


    auto *tfile = new tree_ptr_list<std::string>(5);
    ist2>>*tfile;

    t->addNode(&a);
	t->addNode(&l,&a);
	t->addNode(&b,&a);
	t->addNode(&e,&l);
	t->addNode(&r,&l);
    t->addNode(&o,&b);
    /*}


 //   if(ist2.is_open())
	//{
		//ist2 >> *t;
		//t->addNode(&a);
		//t->addNode(&l,&a);
		//t->addNode(&b,&a);
		// t->addNode(&e,&a);
		// t->addNode(&r,&a);
		// t->addNode(&o,&b);   
    /*}
    else
        std::cout << "file non aperto\n";
    */

    tfile->showStructure();
    // t->showTreePtr();


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

#if GRAPH_ADJ_LIST

    graph_adj_list<int> *_graph = new graph_adj_list<int>();

    _graph->addNode(a0); // It's redundant
    _graph->addEdge(l1,b2);
    _graph->addEdge(b2,a0);
    _graph->addEdge(a0,l1);
    _graph->addEdge(a0,e3);
    _graph->addEdge(b2,e3);

    std::cout<<"\n\n";
    _graph->showStructure();
    //graph->deleteEdge(a,c);

    //graph.addNode(h);
    //graph->showGraph();
    std::cout<<std::endl;

    //delete graph;
    //std::cout<<"grafo distrutto\n";

#endif


#if GRAPH_EDGE_LIST

    graph_edge_list<int>* _graph = new graph_edge_list<int>();
    
    // _graph->addNode(a0);
    // _graph->addNode(l1);
    try{
        _graph->addEdge(&a0,&l1);
        _graph->addEdge(&l1,&a0);
        _graph->addEdge(&b2,&a0);
        _graph->addEdge(&l1,&b2);
        _graph->addEdge(&a0,&b2);

    }catch(std::string _error){
        std::cout<<_error<<"\n";
    }

    std::vector<edge<int>> incident_edge;

    incident_edge = _graph->getIncidentEdge(a0);

    std::cout<<(*_graph);

    std::cout<<"grado di 2: "<<_graph->degree(a0);
    std::cout<<"\n";

    for(auto &e: incident_edge){
        std::cout<<e;
    }
    


#endif

#if GRAPH_INC_LIST

    
    /* 
    n=4 m=5

    a -> 0 -> 4       0:(a,b)
    b -> 2            1:(c,a)
    c -> 1 -> 3       2:(b,c)
    d                 

    0:(a,b)
    1:(c,a)
    2:(b,c)
    3:(c,d)
    4:(a,d)
    */



	graph_inc_list<std::string> _graph;
	try{
        _graph.addEdge(&a, &l);
        _graph.addEdge(&a, &b);
        _graph.addEdge(&b, &a);
        _graph.addEdge(&l, &e);
        _graph.addEdge(&e, &a);
    }catch(std::string &_error){
        std::cout<<_error<<"\n";
    }

    _graph.showStructure(); //is only for debug

#endif
    return 0;
}
