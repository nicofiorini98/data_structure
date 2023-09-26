#include <exception>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "./City.h"
#include "./Coordinates.h"
#include "GraphIncList.h"
#include "Node.h"
#include "TreePosVector.h"
#include "TreePtrList.h"
#include "DHeap.h"
// #include "GraphAdjList.h"
// #include "GraphEdgeList.h"

#define TREE_PTR_LIST 0
#define POS_VECTOR 0
#define GRAPH_EDGE_LIST 0
#define GRAPH_INC_LIST 0
#define DHEAP 1
#define HEAP_SORT 1

#define CITY_TREE_PTR_LIST 0
#define CITY_TREE_POS_VECTOR 0
#define PROVA 0
#define GRAPH_ADJ_LIST 0

using namespace datalib;

City* roma    = new City(1, "roma");
City* milano  = new City(2, "milano");
City* napoli  = new City(3, "napoli");
City* bolzano = new City(4, "bolzano");
City* gerusalemme = new City(5, "gerusalemme");

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

    try{

    std::cout<<"\n+++++++++++++ Test TreePosVector: ++++++++++\n";

    std::ifstream input("/home/nico/project/data_structure/input_test/tree.txt");
    //std::ifstream ist2{"C:\\Users\\1dnic\\Desktop\\my_project\\data_structure\\insert_tree.txt"};
    //std::ofstream os{"../output.txt"};

	// input.open("../tree.txt",std::ios_base::in);

    if(!input.is_open()){
        std::cout << "Failed to open file." << std::endl;
        return -1;
    }else{
        std::cout << "file opened correctly." << std::endl;
    }

    auto tree = new TreePosVector<std::string>(2,3);
    // auto tree = TreePtrList<std::string>();

    //inizializzazione di tree tramite file

    input>>*tree;


    std::cout<<"Test TreePosVector::getDegree() : "<<tree->getDegree("a")<<" \n";

	std::string parent = tree->getParent("l");

    std::list<std::string> children = tree->getChildren("b");

	std::cout<<"Test TreePosVector::getChildren(\"b\")";

    for(auto& c: children){
        std::cout<<"\n--> "<<c;
    }
    std::cout<<std::endl;

    // tree->showTree();

    std::cout<<"getNumChildrenTest: "<<tree->getNumChildren("b")<<"\n";

    std::cout<<"the parent of l is: "<<tree->getParent("l")<<"\n";

    tree->showTree();


    delete tree;

    std::cout<<"parent: "<<parent<<"\n";

    std::cout<<"\n----------------------------------------------\n";
		

    }catch(std::exception &error){
        std::cout<<"Errore --> "<<error.what();
    }
    

#endif

/* ------------------- Testinge DHeap ------------------- */
#if DHEAP
	try{

        std::cout<<"\n++++++++++++++ Testing DHeap +++++++++++++++\n";


        // {37,22,31,13,15,25,14,7,3,12,9}

        DHeap<int> dheap(2,15,{3,37,22,31,13,15,25,14,7,12,1}); // 11 elementi

        // std::cout<<
        dheap.deleteValue(3);
        dheap.deleteValue(37);
        // dheap.insert(37);

        dheap.showTree();

        //devo arrivare a vedere questo
        // {37,22,31,13,15,25,14,nullptr,nullptr,7,3,nullptr,nullptr,12,9} // questo è 2-heap fixato

        std::cout<<"\n----- \nIl max dell'heap è: "<< dheap.getMaxValue()<<"\n";

        dheap.popMaxValue();

        std::cout<<"\n----- \nIl max dell'heap è: "<< dheap.getMaxValue()<<"\n";

        // std::cout<<"isLeaf(): "<<dheap.isLeaf(9)<<"\n"; // restituisce 

    }catch(std::exception &error){
        std::cout<<"DHeap error caught: "<<error.what()<<"\n";
    }

#endif
    
#if HEAP_SORT
    
    try{
        
        // TODO risolvere per valori uguali, l'heap deve poter avere due valori uguali
        std::cout<<"\n++++++++++++++ Testing HeapSort +++++++++++++++\n";
        std::vector<int> unordered_int = {1,2,3,4,5,6,7,8,9,10,11};
        
        DHeap<int> dheap(2,unordered_int.size(),unordered_int);
        
        std::vector<int> ordered_int;
        
        //algoritmo heap sort
        while(!dheap.isEmpty()){
            ordered_int.push_back(dheap.popMaxValue());
        }
        
        std::cout<<"Vettore ordinato in senso decrescente: \n";
        for(auto& value: ordered_int){
            std::cout<<value<<" ";
        }

        std::cout<<"\n-------------- end HeapSort ---------------\n";
    }catch(std::exception &error){
        std::cout<<"Heap sort error: "<<error.what()<<"\n";
    }

#endif


#if TREE_PTR_LIST

    try
    {
        std::cout<<"\n++++++++++ Prova TreePtrList : ++++++++++\n";
   /*
    * std::string a{"a"},l{"l"},b{"b"}j;
    * std::string e{"e"},r{"r"},o{"o"};
    */

    std::ifstream input("/home/nico/project/data_structure/input_test/tree.txt");

    //std::ifstream ist2{"C:\\Users\\1dnic\\Desktop\\my_project\\data_structure\\insert_tree.txt"};
    //std::ofstream os{"../output.txt"};

	// input.open("../tree.txt",std::ios_base::in);
    if(!input.is_open()){
        std::cout << "Failed to open file." << std::endl;
        return -1;
    }else{
        std::cout << "file opened correctly." << std::endl;
    }

    auto tree = TreePtrList<std::string>();

    //inizializzazione di tree tramite file

    input>>tree;

    std::cout<<"Test TreePtrList::getDegree() : "<<tree.getDegree("a")<<" \n";

    std::string parent = tree.getParent("l");
    std::cout<<"Test TreePtrList::getParent() : "<<parent<<" \n";
    std::cout<<"Test TreePtrList::getParent() : "<<tree.getParent("l")<<" \n";

	//verifica aggiunta nodo -- da migliorare, in questo modo non va bene.
    std::string boh = "boh";
    std::string s = "a";
    tree.addNode(boh,s);
    tree.addChildren("a",{"nodo1","nodo2"});
    

    std::list<std::string> children;
    children = tree.getChildren("a");

    std::cout<<"------ \n Test TreePtrList::getChildren(): ";
    for(auto c: children){
        std::cout<<c<<" ";
    }
    std::cout<<std::endl;

	std::cout<<"------\n Prova depthSearch: \n";
    tree.depthSearch("a");

	std::cout<<"Prova breadthSearch: \n";
    tree.breadthSearch("a");

    std::cout<<"\n----------------------------------------------\n";

    }
    catch (const std::exception& e) 
    {
        std::cerr << "Exception caught: " << e.what() << std::endl;     
    }
    
#endif

#if GRAPH_EDGE_LIST

    //std::string a{"a"},b{"b"},c{"c"};
    //std::string d{"d"},e{"e"},f{"f"},g{"g"};

    GraphIncList<std::string> graph;

    std::fstream input;
    input.open( "/home/nico/project/data_structure/input_test/oriented_graph.txt",std::ios::in);

    if(input.is_open()){
        input>>graph;
        graph.showStructure();

    }
    else
        std::cout<<"file non aperto\n";

    //_graph.showStructure();
    std::list<Edge<std::string>> edges;
    graph.getOutgoingEdges("a",edges);

    for(auto &e: edges){
        std::cout<<e;
    }

#endif

#if GRAPH_INC_LIST

    std::cout<<"\n ------------- Prova GraphIncList ---------------\n";

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


    //grafo per visita in ampiezza
	GraphIncList<std::string> graph;

    std::fstream input;
    input.open( "/home/nico/project/data_structure/input_test/oriented_graph.txt",std::ios::in);

    if(input.is_open()){
        input>>graph;
    }
    else
        std::cout<<"file non aperto\n";


    graph.addEdge("a","c"); // OK 
    graph.addNode("l");     // this is not necessary, only for testing
    graph.addEdge("l","a"); // OK

    std::cout<<"virtual method: "<<graph.getNumNode()<<"\n";

    std::cout<<"numero archi: "<<graph.numEdge()<<"\n";//OK
    std::cout<<"max degree: "<<graph.maxDegree()<<"\n";
    std::cout<<"degree of c: "<<graph.degree("c")<<"\n";


    graph.showStructure();      // OK
    graph.deleteEdge("l","a");  // OK
    graph.showStructure();      // OK

    // TreePtrList<std::string> tree;
    // graph.depthSearch("b", tree);
    // _graph.breadthSearch("a",breadthTree);

    TreePtrList<std::string> tree;
    graph.breadthSearch("a",tree);

	// std::cout<<"\n show breadthTree\n";
    tree.showStructure();

    // std::list<Edge<std::string>> lista;
    //_graph.getIncomingEdges(g,lista);
    // _graph.getOutgoingEdges(g,lista);

    // for(auto& e: lista){
    //     //std::cout<<e;
    // }

#endif
    return 0;
}
