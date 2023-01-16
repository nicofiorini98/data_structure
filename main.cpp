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
#define GRAPH_EDGE_LIST 0
#define GRAPH_INC_LIST 1
#define PROVA 0
#define CITY_TREE_POS_VECTOR 0
#define CITY_TREE_PTR_LIST 0


using namespace datalib;
city* roma    = new city(1, "roma");
city* milano  = new city(2, "milano");
city* napoli  = new city(3, "napoli");
city* bolzano = new city(4, "bolzano");
city* gerusalemme = new city(5, "gerusalemme");

int main(){

#if CITY_TREE_POS_VECTOR
    std::cout<<*roma;

    try{
		datalib::TreePosVector<city> tree(2, 3);
		tree.addNode(roma,nullptr);         //radice
        tree.addChildren(*roma,{*milano,*napoli});
		tree.addNode(milano,gerusalemme);
		tree.addNode(napoli,bolzano);
        tree.showTree2();

    }catch(std::string &error){
        std::cout<<error;
    }


#endif

#if CITY_TREE_PTR_LIST

    try{
		datalib::TreePtrList<city> tree;
		tree.addNode(roma,nullptr);         //radice
        tree.addChildren(*roma,{*milano,*napoli});
		tree.addNode(gerusalemme,milano);
		// tree.addNode(bolzano,napoli);
        tree.showStructure();

    }catch(std::string &error){
        std::cout<<error;
    }

#endif 



#if POS_VECTOR

    std::cout<<"Prova vettore posizione: \n";
    try{
		datalib::TreePosVector<std::string> tree(2, 3);
		tree.addNode(new std::string("a"),nullptr);  //radice
        tree.addChildren("a",{"l","b"});
		// tree.addNode(new std::string("l"),new std::string("a"));
		// tree.addNode(new std::string("b"),new std::string("a"));
		tree.addNode(new std::string("e"), new std::string("l"));
		tree.addNode(new std::string("r"), new std::string("l"));
		tree.addNode(new std::string("o"), new std::string("b"));

        tree.showTree2();

    }catch(std::string &error){
        std::cout<<error;
    }

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

   /*
    * std::string a{"a"},l{"l"},b{"b"};
    * std::string e{"e"},r{"r"},o{"o"};
    */

	std::string n{"n"},g{"g"};

    std::ifstream input;
    //std::ifstream ist2{"C:\\Users\\1dnic\\Desktop\\my_project\\data_structure\\insert_tree.txt"};
    //std::ofstream os{"../output.txt"};

	input.open( "../tree.txt",std::ios::in);
    auto tree = TreePtrList<std::string>();

    //inizializzazione di tree tramite file
    input>>tree;

    std::cout<<"grado nodo a : "<<tree.getDegree("a")<<"\n";
    std::list<std::string> _list;

    
    tree.depthSearch(new std::string("a"));

    tree.breadthSearch(new std::string("a"));

    //tree.addChildren("a",{g,n});
    //tree.getChildren("a",_list);

    /*for(auto& child: _list)
        std::cout<<child;*/
    //tree.showStructure();

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
    input.open( "../unoriented_graph_337.txt",std::ios::in);

    if(input.is_open()){
        input>>_graph;
    }
    else
        std::cout<<"file non aperto\n";

    TreePtrList<std::string> tree;
    _graph.depthSearch("b", tree);
    // _graph.breadthSearch("a",breadthTree);

    // breadthTree.breadthSearch(new std::string("a"));

	// std::cout<<"\n show breadthTree\n";
    tree.showTree();

    // std::list<Edge<std::string>> lista;
    //_graph.getIncomingEdges(g,lista);
    // _graph.getOutgoingEdges(g,lista);

    // for(auto& e: lista){
    //     //std::cout<<e;
    // }

#endif
    return 0;
}
