#include <exception>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "./City.h"
#include "GraphIncList.h"
#include "Node.h"
#include "TreePosVector.h"
#include "TreePtrList.h"
#include "DHeap.h"
#include "GraphEdgeList.h"
#include "BasicGraph.h"

#define TREE_PTR_LIST 0
#define POS_VECTOR 0
#define GRAPH_EDGE_LIST 0
#define GRAPH_INC_LIST 0
#define DHEAP_MAX 0
#define DHEAP_MIN 0
#define HEAP_SORT 0
#define COPY_COSTRUCTOR 1

//Required GraphViz installed on the system
template <class T>
void printPngImage(Graph<T>* graph,const std::string& nameFileDot, const std::string& nameFilePng){

    std::string path = "/home/nico/project/data_structure/output_test/";
    std::string nameDotFile = path + nameFileDot;

    std::ofstream dotFile(nameDotFile,std::ios::out);

    graph->outputDotFile(dotFile);

    dotFile<<std::endl;
    
    std::string pngName = path + nameFilePng;
    std::string command = "dot -Tpng " + std::string(nameDotFile) + " -o " + std::string(pngName);
    
    int result = system(command.c_str());

    if (result == 0) {
        std::cout << "Graph generation successful. Output image saved as " << nameFilePng<< std::endl;
    } else {
        std::cerr << "Graph generation failed. Check if GraphViz is installed and the DOT file exists." << std::endl;
    }
    
    dotFile.close();

}

void graphImage(const std::string& nameFileDot, const std::string& nameFilePng){

    // std::string pathInput = "/home/nico/project/data_structure/input_test/";
    std::string pathOutput = "/home/nico/project/data_structure/output_test/";
    std::string nameDotFile = pathOutput+ nameFileDot;
    std::string pngName = pathOutput + nameFilePng;

    std::string command = "dot -Tpng " + std::string(nameDotFile) + " -o " + std::string(pngName);
    
    int result = system(command.c_str());

    if (result == 0) {
        std::cout << "Graph generation successful. Output image saved as " << nameFilePng<< std::endl;
    } else {
        std::cerr << "Graph generation failed. Check if GraphViz is installed and the DOT file exists." << std::endl;
    }
    

}


/* ++++++++++++++++++ test TreePtrList +++++++++++++++++++ */

#if 1
inline int testTreePtrList(){
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

    std::list<std::string> values;
    std::cout<<"ordine depthSearch: \n";
    for(auto& value: tree.depthSearch("a",values)){
        std::cout<<value<<"-->";
    }
    std::cout<<std::endl;

    std::cout<<"ordine breadth: \n";
    for(auto& value: tree.breadthSearch("a",values)){
        std::cout<<value<<"-->";
    } 
    std::cout<<std::endl;
    
    std::cout<<"Test TreePtrList::getDegree() : "<<tree.getDegree()<<" \n";

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

    ;

	// std::cout<<"Prova breadthSearch: \n";
    // tree.breadthSearch("a",values);
    
    std::cout<<"\n----------------------------------------------\n";
    
    std::cout<<tree.getValue("a")<<"\n";
    tree.setValue("a","j");
    
    std::list<Edge<std::string>> edges;

    }
    catch (const std::exception& e) 
    {
        std::cerr << "Exception caught: " << e.what() << std::endl;     
    }
	return 0;
}
#endif

/* ++++++++++++++++++ test TreePosVector +++++++++++++++++++ */
inline int testTreePosVector(){
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

    std::cout<<"Test TreePosVector::getDegree() : "<<tree->getDegree()<<" \n";

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

    // tree->showTree();
    std::cout<<std::endl<<"operator<< with old value: "<<*tree<<"\n";
    
    std::cout<<"get the value :" <<tree->getValue("a")<<std::endl;
    tree->setValue("a","j");
    
    std::cout<<"operator << with new value j"<<*tree;


    delete tree;

    std::cout<<"parent: "<<parent<<"\n";

    std::cout<<"\n----------------------------------------------\n";
		

    }catch(std::exception &error){
        std::cout<<"Errore --> "<<error.what();
    }	

	return 0;
}

/* ++++++++++++++++++ test GraphEdgeList +++++++++++++++++++ */
#if 1
inline int testGraphEdgeList(){

	std::cout<<"\n ------------- Prova GraphEdgeList ---------------\n";
    GraphEdgeList<std::string> graph;

    std::fstream input;
    input.open("/home/nico/project/data_structure/input_test/oriented_graph.txt",std::ios::in);

    if(input.is_open())
        input>>graph;
    else{
        std::cout<<"file non aperto\n";
        return -1;
    }
    
    std::cout<<graph.getValue("a")<<"\n";
    graph.setValue("a","j");

    printPngImage(&graph,"edge.dot","edge.png");
    
	return 0;
}
#endif

/* ++++++++++++++++++ test GraphIncList +++++++++++++++++++ */
inline int testGraphIncList(){
	std::cout<<"\n ------------- Test GraphIncList ---------------\n";

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
    // tree.showStructure();

    // std::list<Edge<std::string>> lista;
    //_graph.getIncomingEdges(g,lista);
    // _graph.getOutgoingEdges(g,lista);

    // for(auto& e: lista){
    //     //std::cout<<e;
    // }	
	return 0;
}

/* ++++++++++++++++++ test DHeapMax +++++++++++++++++++ */
#if 1
inline int testDHeapMax(){
	try{

        std::cout<<"\n++++++++++++++ Testing DHeap MAX +++++++++++++++\n";
        std::cout<<"\n nothing in the function test, check it\n";


    }catch(std::exception &error){
        std::cout<<"DHeap error caught: "<<error.what()<<"\n";
    }
	return 0;
}
#endif

/* ++++++++++++++++++ test DHeapMin +++++++++++++++++++ */
#if 1
inline int testDHeapMin(){
	try{

        std::cout<<"\n++++++++++++++ Testing DHeap MIN +++++++++++++++++\n";

        DHeap<int,std::string> dheap(2,15,true);
        
        std::ifstream input("/home/nico/project/data_structure/input_test/heap_int_string.txt");
        
        if(!input.is_open()){
            std::cout << "Failed to open file." << std::endl;
            return -1;
        }else{
            std::cout << "file opened correctly." << std::endl;
            input>>dheap;
        }
    

        dheap.deleteByKey(37);
        dheap.deleteByKey(11);
        dheap.deleteByKey(3);
        
        dheap.changeKey(300,"c");
        dheap.changeValue(300,"d");
        

        // dheap.deleteByValue("undici");

        // {37,22,31,13,15,25,14,7,3,12,9}

        // DHeap<int> dheap(2,15,true,{3,37,22,31,13,15,25,14,7,12,1}); // 11 elementi

        // dheap.deleteValue(3);
        // dheap.deleteValue(37);
        // dheap.setValue(3,40);

        dheap.showTree();
        dheap.showStructure();

        //devo arrivare a vedere questo
        // {37,22,31,13,15,25,14,nullptr,nullptr,7,3,nullptr,nullptr,12,9} // questo è 2-heap fixato

        // std::cout<<"\n----- \nIl min dell'heap è: "<< dheap.getFirstValue()<<"\n";

        // dheap.popValue();

        // std::cout<<"\n----- \nIl min dell'heap è: "<< dheap.getFirstValue()<<"\n";

    }catch(std::exception &error){
        std::cout<<"DHeap error caught: "<<error.what()<<"\n";
    }

	return 0;
}
#endif

inline int testHeapSort(){
	try{
        
        DHeap<int,std::string> dheap(2,15,false);
        
        std::ifstream input("/home/nico/project/data_structure/input_test/heap_int_string.txt");
        
        if(!input.is_open()){
            std::cout << "Failed to open file." << std::endl;
            return -1;
        }else{
            std::cout << "file opened correctly." << std::endl;
            input>>dheap;
        }
        
        dheap.showTree();
        
        std::vector<std::pair<int,std::string>> ordered_int;
        
        //algoritmo heap sort
        while(!dheap.isEmpty()){
            std::pair<int,std::string> boh = dheap.popValue();
            // std::cout<<"popValue: "<<boh<<std::endl;
            ordered_int.push_back(boh);
        }
        
        std::cout<<"Vettore ordinato in senso decrescente: \n";
        for(auto& value: ordered_int){
            std::cout<<value.first<<" ";
        }

        std::cout<<"\n-------------- end HeapSort ---------------\n";
    }catch(std::exception &error){
        std::cout<<"Heap sort error: "<<error.what()<<"\n";
    }
	return 0;
}

/* ++++++++++++++++++ test TreeCopyCostructor +++++++++++++++++++ */
inline int testCopyCostructor(){
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

    auto tree = TreePosVector<std::string>(2,10);

    //inizializzazione di tree tramite file
    input>>tree;

	std::cout<<"tree: \n"<<tree;
    TreePosVector<std::string> copyTree(tree);
	std::cout<<"copyTree: \n"<<copyTree;
	
	
    
    

    }
    catch (const std::exception& e) 
    {
        std::cerr << "Exception caught: " << e.what() << std::endl;     
    }

	return 0;
}

inline int testGraphCopyCostructor(){
	try
    {
        std::cout<<"\n++++++++++ Prova Graph copy costructor: ++++++++++\n";
    /*
    * std::string a{"a"},l{"l"},b{"b"}j;
    * std::string e{"e"},r{"r"},o{"o"};
    */

    std::ifstream input("/home/nico/project/data_structure/input_test/oriented_graph.txt");

    //std::ifstream ist2{"C:\\Users\\1dnic\\Desktop\\my_project\\data_structure\\insert_tree.txt"};
    //std::ofstream os{"../output.txt"};

	// input.open("../tree.txt",std::ios_base::in);
    if(!input.is_open()){
        std::cout << "Failed to open file." << std::endl;
        return -1;
    }else{
        std::cout << "file opened correctly." << std::endl;
    }

    auto graph = GraphEdgeList<std::string>();

    //inizializzazione di tree tramite file
    input>>graph;

	std::cout<<"tree: \n"<<graph;
    GraphEdgeList<std::string> copyGraph(graph);
	std::cout<<"copyTree: \n"<<copyGraph;
	
	
    
    

    }
    catch (const std::exception& e) 
    {
        std::cerr << "Exception caught: " << e.what() << std::endl;     
    }

	return 0;
}
