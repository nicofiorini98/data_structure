#include <iostream> 
#include <fstream>
#include <sstream>
#include <vector>
#include "city.h"
#include "Node.h"
#include "Edge.h"
#include "GraphAdjList.h"
#include "GraphEdgeList.h"
#include "GraphIncList.h"
#include "TreePtrList.h"
#include "TreePosVector.h"
//#include <chrono>

//using namespace std;
// //using namespace std::chrono 
// high_resolution_clock::time_point t1= high_resolution_clock::now();

// high_resolution_clock::time_point t2= high_resolution_clock::now();

// duration<double> time_span=duration_cast<duration<double>>(t2-t1);

// std::cout<<"it took the time"<<time_span.count()<<"seconds.";

#define TREE_PTR_LIST 0
#define POS_VECTOR 0
#define GRAPH_ADJ_LIST 0
#define GRAPH_EDGE_LIST 1
#define GRAPH_INC_LIST 0
#define PROVA 0 


using namespace datalib;
city roma(1, "roma");
city milano(2, "milano");
city napoli(3, "napoli");

int main(){

/* std::cout << 1234.56789 << "\t\t(defaultfloat)\n"
 // \t\t to line up columns
<< std::fixed << 1234.56789 << "\t(fixed)\n"
< < std::scientific << 1234.56789 << "\t(scientific)\n";
*/


    // datalib::node<int> a0{0},l1{1},b2{2};
    // datalib::node<int> e3{3},r4{4},o5{5},n{6};

    //int a0{0},l1{1},b2{2};
    //int e3{3},r4{4},o5{5},n{6};

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
    GraphIncList<int> _graph_inc_list;

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

    std::string a{"a"},l{"l"},b{"b"};
    std::string e{"e"},r{"r"},o{"o"},n{"n"};

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

    auto *t = new TreePtrList<std::string>(2);


    auto *tfile = new TreePtrList<std::string>(5);
    ist2>>*tfile;

    try{
        t->addNode(&a);
        t->addNode(&l,&a);
        t->addNode(&b,&a);
        t->addNode(&e,&l);
        t->addNode(&r,&l);
        t->addNode(&o,&b);
    }
    catch(std::string error){
        std::cout<<error<<"\n";
    }

    t->updateParent(r,b);
    t->showStructure();



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

    GraphAdjList<int> *_graph = new GraphAdjList<int>();

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

    //std::string a{"a"},b{"b"},c{"c"};
    //std::string d{"d"},e{"e"},f{"f"},g{"g"};

    GraphIncList<std::string> _graph;

    std::fstream input;
    input.open( "../oriented_graph.txt",std::ios::in);

    if(input.is_open()){
        input>>_graph;
    }
    else
        std::cout<<"file non aperto\n";

    //_graph.showStructure();
    std::list<Edge<std::string>> _list;
    _graph.getOutgoingEdges("a",_list);

    for(auto &e: _list){
        std::cout<<e;
    }

#endif

#if GRAPH_INC_LIST

    std::string a{"a"},b{"b"},c{"c"};
    std::string d{"d"},e{"e"},f{"f"},g{"g"};

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

    //grafo.addEdge(&a,&b);
    //grafo.addEdge(&b,&c);
    /*GraphIncList<city> graph_city;

	graph_city.addEdge(&milano,&napoli);
	graph_city.addEdge(&milano,&roma);
	graph_city.addEdge(&napoli,&roma);

    graph_city.showStructure();*/

    //grafo per visita in ampiezza
	GraphIncList<std::string> _graph;

    std::fstream input;
    input.open( "../oriented_graph.txt",std::ios::in);

    if(input.is_open()){
        input>>_graph;
    }
    else
        std::cout<<"file non aperto\n";

    //_graph.showStructure();

	/*try{

         _graph.addEdge(&a,&d);
         _graph.addEdge(&d,&a);
         _graph.addEdge(&a,&b);
         _graph.addEdge(&b,&a);
         _graph.addEdge(&a,&c);
         _graph.addEdge(&c,&a);
         _graph.addEdge(&b,&c);
         _graph.addEdge(&c,&b);
         _graph.addEdge(&c,&d);
         _graph.addEdge(&d,&c);
         _graph.addEdge(&c,&e);
         _graph.addEdge(&e,&c);
         _graph.addEdge(&e,&f);
         _graph.addEdge(&f,&e);
         _graph.addEdge(&f,&g);
         _graph.addEdge(&g,&f);
         _graph.addEdge(&e,&g);
         _graph.addEdge(&g,&e);

         // std::cout<<"il grado del nodo è: "<<_graph.degree("n")<<"\n";
     }catch(std::string &_error){
         std::cout<<_error<<"\n";
     }*/
    _graph.showStructure();

    std::list<Edge<std::string>> lista;
    //_graph.getIncomingEdges(g,lista);
    _graph.getOutgoingEdges(g,lista);

    for(auto& e: lista){
        //std::cout<<e;
    }

#endif
    return 0;
}
