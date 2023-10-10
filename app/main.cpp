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
#include "DistanceCity.h"
// #include "GraphAdjList.h"
// #include "GraphEdgeList.h"

#define TREE_PTR_LIST 0
#define POS_VECTOR 1
#define GRAPH_EDGE_LIST 0
#define GRAPH_INC_LIST 0
#define DHEAP_MAX 0
#define DHEAP_MIN 0
#define HEAP_SORT 0

#define CITY_TREE_PTR_LIST 0
#define CITY_TREE_POS_VECTOR 0
#define PROVA 0
#define GRAPH_ADJ_LIST 0
#define CITY 0
#define DIJKSTRA 0


using namespace datalib;

// output stream to print std::pair
template <typename T1, typename T2>
std::ostream &operator<<(std::ostream &os, const std::pair<T1, T2> &p) {
    // os << "(" << p.first << "," << p.second << ")";
    os << p.first ;
    return os;
}

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

    // tree->showTree();
    std::cout<<std::endl<<"operator<<: "<<*tree;


    delete tree;

    std::cout<<"parent: "<<parent<<"\n";

    std::cout<<"\n----------------------------------------------\n";
		

    }catch(std::exception &error){
        std::cout<<"Errore --> "<<error.what();
    }
    

#endif

/* ------------------- Testing DHeap ------------------- */
#if DHEAP_MAX
	try{

        std::cout<<"\n++++++++++++++ Testing DHeap MAX +++++++++++++++\n";


        // {37,22,31,13,15,25,14,7,3,12,9}

        DHeap<int> dheap(2,15,true,{3,8,1,1,37,22,31,13,15,25,14,7,12,38}); // 11 elementi

        // dheap.deleteValue(3);
        // dheap.deleteValue(37);

        dheap.showTree();

        //devo arrivare a vedere questo
        // {37,22,31,13,15,25,14,nullptr,nullptr,7,3,nullptr,nullptr,12,9} // questo è 2-heap fixato

        std::cout<<"\n----- \nIl max dell'heap è: "<< dheap.getFirstValue()<<"\n";

        dheap.popValue();

        std::cout<<"\n----- \nIl max dell'heap è: "<< dheap.getFirstValue()<<"\n";

        // std::cout<<"isLeaf(): "<<dheap.isLeaf(9)<<"\n"; // restituisce 

    }catch(std::exception &error){
        std::cout<<"DHeap error caught: "<<error.what()<<"\n";
    }

#endif

#if DHEAP_MIN
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

#endif

    
#if HEAP_SORT
    
    try{
        
        // TODO risolvere per valori uguali, l'heap deve poter avere due valori uguali
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
    
    std::list<Edge<std::string>> edges;

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
    
#if CITY
    City city;
    std::fstream input;
    input.open( "/home/nico/project/data_structure/input_test/city_graph.txt",std::ios::in);

    GraphIncList<City> cityGraph;
    if(input.is_open()){
        while(!input.eof()){
            Edge<City> edge;
            input>>edge;
            double weight = calculateDistance(edge.getSourceValue(),edge.getDestinationValue());
            edge.setWeight(weight);
            cityGraph.addEdge(edge);
        }
    }
    else
        std::cout<<"file non aperto\n";
    
    cityGraph.showStructure();

#endif

#if DIJKSTRA 

    /* 
    algorimo Dijkstra(grafo G,vertice s)->albero
    for(each)(vertice u in G) do Dsu <- +inf
     T = albero formato dal solo vertice s
     Dheap S
     Dss = 0
     S.insert(s,0)

     while( not S.isEmpty())do
       u = s.popValue()
       for each(arco(u,v)in G)do
            if(Dsv == inf)then
                s.insert(v,Dsu + w(u,v))
                Dsv = Dsu + w(u,w)
                rendi u padre di v in T
            else if(Dsu + w(u,v)<Dsv)then
                s.decreaseKey(v,Dsv-(Dsu-w(u,v)))
                rendi u nuovo padre di v in T
    
    return T
    */
    /* Come posso rappresentare le distanze tra i nodi?
     * posso usare std::pair<int,Node<T>>
     * Devo fare una struct per inserire nell'heap le distanze tra i nodi
     */
    

    std::fstream input;
    input.open( "/home/nico/project/data_structure/input_test/city_graph.txt",std::ios::in);

    GraphIncList<City> cityGraph;
    if(input.is_open()){
        // TODO aggiungere il peso in graphIncList
        // input all the edges in the graph
        while(!input.eof()){
            Edge<City> edge;
            input>>edge;
            double weight = calculateDistance(edge.getSourceValue(),edge.getDestinationValue());
            edge.setWeight(weight);
            cityGraph.addEdge(edge);
        }

        std::ofstream cytyGraphdotFile("/home/nico/project/data_structure/output_test/cityGraph.dot",std::ios::out);
        
        cityGraph.outputDotFile(cytyGraphdotFile);
        
        cytyGraphdotFile.close();

        DHeap<double,City> S(2,cityGraph.getNumNode(),true);

        //initialization spanning tree
        TreePtrList<City> tree;

        City startValue = cityGraph.getValue({"Roma"});
        startValue.setDistance(0);

        //aggiorno la start city with distance 0
        cityGraph.setValue({"Roma"},startValue);

        tree.addRoot(startValue);
        
        S.insert(std::pair<double,City>(0,startValue));
        //aggiornare distanza da Roma->Roma Dss=0

        while(!S.isEmpty()){
            City u = S.popValue().second;

            //get all outgoing edges from city u
            std::list<Edge<City>> edges;
            cityGraph.getOutgoingEdges(u,edges);

            #define dest e.getDestinationValue()
            #define src e.getSourceValue()

            for(auto& e: edges){
                double Dsv = dest.getDistance();
                double Dsu = src.getDistance();
                double weight = e.getWeight();

                if(Dsv >= 10000){
                    Dsv = Dsu + weight;
                    S.insert(std::pair<double,City>(Dsv,dest));
                    tree.addNode(dest, src);
                    
                    //update the distance of dest
                    City newDistance = dest; 
                    newDistance.setDistance(Dsv);
                    cityGraph.setValue(dest,newDistance); 

                }else if(Dsu + weight < Dsv){
                    Dsv = Dsu + weight;
                    S.changeKey(Dsv, dest);
                    
                    //update the distance of dest
                    City newDistance = dest; 
                    newDistance.setDistance(Dsv);
                    cityGraph.setValue(dest,newDistance); 
                    tree.updateParent(dest, src);
                }
            }

            
        }

        // cityGraph.showStructure();
        // S.showTree();
        // tree.showTree();
        std::cout<<"spanning tree edge list: "<<tree<<std::endl;

        std::ofstream dotFile("/home/nico/project/data_structure/output_test/minimum_spanning_tree.dot",std::ios::out);
        
        tree.outputDotFile(dotFile);
        
        dotFile.close();
        
    }
    else
        std::cout<<"file non aperto\n";

#endif
    return 0;
}
