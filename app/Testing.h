#ifndef TESTING_H
#define TESTING_H
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "./City.h"
#include "BasicGraph.h"
#include "DHeap.h"
#include "GraphEdgeList.h"
#include "GraphIncList.h"
#include "Node.h"
#include "TreePosVector.h"
#include "TreePtrList.h"
#include "Utils.h"

/* ++++++++++++++++++ test TreePtrList +++++++++++++++++++ */

#if 1
inline int testTreePtrList() {
    try {
        std::cout << "\n++++++++++ Prova TreePtrList : ++++++++++\n";
        /*
         * std::string a{"a"},l{"l"},b{"b"}j;
         * std::string e{"e"},r{"r"},o{"o"};
         */

        std::ifstream input("../../input_test/tree.txt");

        // std::ifstream
        // ist2{"C:\\Users\\1dnic\\Desktop\\my_project\\data_structure\\insert_tree.txt"};
        // std::ofstream os{"../output.txt"};

        // input.open("../tree.txt",std::ios_base::in);
        if (!input.is_open()) {
            std::cout << "Failed to open file." << std::endl;
            return -1;
        } else {

            auto tree = TreePtrList<std::string>();

            // inizializzazione di tree tramite file

            input >> tree;

            printTreePng(&tree, "provaTree.dot", "provaTree.png");

            std::list<std::string> values;
            std::cout << "ordine depthSearch: \n";
            for (auto &value : tree.depthSearch(values)) {
                std::cout << value << "-->";
            }
            std::cout << std::endl;

            std::cout << "ordine breadth: \n";
            for (auto &value : tree.breadthSearch(values)) {
                std::cout << value << "-->";
            }
            std::cout << std::endl;

            std::cout << "Test TreePtrList::getDegree() : " << tree.getDegree()
                      << " \n";

            std::string parent = tree.getParent("l");
            std::cout << "Test TreePtrList::getParent() : " << parent << " \n";
            std::cout << "Test TreePtrList::getParent() : "
                      << tree.getParent("l") << " \n";

            // verifica aggiunta nodo -- da migliorare, in questo modo non va
            // bene.
            std::string boh = "boh";
            std::string s = "a";
            tree.addNode(boh, s);
            tree.addChildren("a", {"nodo1", "nodo2"});

            std::list<std::string> children;
            children = tree.getChildren("a");

            std::cout << "------ \n Test TreePtrList::getChildren(): ";
            for (auto c : children) {
                std::cout << c << " ";
            }

            std::cout << std::endl;

            ;

            // std::cout<<"Prova breadthSearch: \n";
            // tree.breadthSearch("a",values);

            std::cout << "\n----------------------------------------------\n";

            std::cout << tree.getValue("a") << "\n";
            tree.setValue("a", "j");

            std::list<Edge<std::string>> edges;
        }
    } catch (const std::exception &e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
    return 0;
}
#endif

/* ++++++++++++++++++ test TreePosVector +++++++++++++++++++ */
inline int testTreePosVector() {
    try {

        std::cout << "\n+++++++++++++ Test TreePosVector: ++++++++++\n";

        std::ifstream input("../../input_test/tree.txt");

        if (!input.is_open()) {
            std::cout << "Failed to open file." << std::endl;
            return -1;
        } else {

            auto tree = new TreePosVector<std::string>(2, 3);
            // auto tree = TreePtrList<std::string>();

            // inizializzazione di tree tramite file
            input >> *tree;

            std::list<std::string> values;
            std::cout << "ordine depthSearch: \n";
            for (auto &value : tree->depthSearch(values)) {
                std::cout << value << "-->";
            }
            std::cout << std::endl;

            std::cout << "ordine breadth: \n";
            for (auto &value : tree->breadthSearch(values)) {
                std::cout << value << "-->";
            }
#if 0
    std::cout<<std::endl;

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

#endif

            delete tree;

            std::cout << "\n----------------------------------------------\n";
        }

    } catch (std::exception &error) {
        std::cout << "Errore --> " << error.what();
    }

    return 0;
}

/* ++++++++++++++++++ test GraphEdgeList +++++++++++++++++++ */
#if 1
inline int testGraphEdgeList() {

    std::cout << "\n ------------- Prova GraphEdgeList ---------------\n";
    GraphEdgeList<std::string> graph;

    std::fstream input;
    input.open("../../input_test/oriented_graph.txt", std::ios::in);

    if (input.is_open())
        input >> graph;
    else {
        std::cout << "file non aperto\n";
        return -1;
    }

    TreePtrList<std::string> searchTree;
    searchTree = graph.depthSearch("b", searchTree);

    printGraphPng(&graph, "edge.dot", "edge.png");

    printTreePng(&searchTree, "searchTree.dot", "searchTree.png");

    return 0;
}
#endif

/* ++++++++++++++++++ test GraphIncList +++++++++++++++++++ */
inline int testGraphIncList() {
    std::cout << "\n ------------- Test GraphIncList ---------------\n";

    // grafo per visita in ampiezza
    GraphIncList<std::string> graph;

    std::fstream input;
    input.open("../../input_test/oriented_graph.txt", std::ios::in);

    if (input.is_open()) {
        input >> graph;
    } else
        std::cout << "file non aperto\n";

    graph.addEdge("a", "c"); // OK
    graph.addNode("l");      // this is not necessary, only for testing
    graph.addEdge("l", "a"); // OK

    std::cout << "numero archi: " << graph.numEdge() << "\n"; // OK
    std::cout << "degree of c: " << graph.degree("c") << "\n";

    // TreePtrList<std::string> tree;
    // graph.depthSearch("b", tree);
    // _graph.breadthSearch("a",breadthTree);

    TreePtrList<std::string> tree;
    graph.depthSearch("b", tree);

    printGraphPng(&graph, "oriented_graph.dot", "orientedGraph.png");
    printTreePng(&tree, "breadth_tree.dot", "breadth_tree.png");

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

/* ++++++++++++++++++ test GraphIncList Search +++++++++++++++++++ */
#if 1

#endif

/* ++++++++++++++++++ test DHeapMax +++++++++++++++++++ */
#if 1
inline int testDHeapMax() {
    try {

        std::cout << "\n++++++++++++++ Testing DHeap MAX +++++++++++++++\n";
        std::cout << "\n nothing in the function test, check it\n";

    } catch (std::exception &error) {
        std::cout << "DHeap error caught: " << error.what() << "\n";
    }
    return 0;
}
#endif

/* ++++++++++++++++++ test DHeapMin +++++++++++++++++++ */
#if 1
inline int testDHeapMin() {
    try {

        std::cout << "\n++++++++++++++ Testing DHeap MIN +++++++++++++++++\n";

        DHeap<int, std::string> dheap(2, 15, true);

        std::ifstream input("../../input_test/heap_int_string.txt");

        if (!input.is_open()) {
            std::cout << "Failed to open file." << std::endl;
            return -1;
        } else {
            input >> dheap;

            dheap.deleteByKey(37);
            dheap.deleteByKey(11);
            dheap.deleteByKey(3);

            dheap.changeKey(300, "c");
            dheap.changeValue(300, "d");

            std::cout << dheap;
        }
    } catch (std::exception &error) {
        std::cout << "DHeap error caught: " << error.what() << "\n";
    }

    return 0;
}
#endif

inline int testHeapSort() {
    try {

        DHeap<int, std::string> dheap(2, 15, false);

        std::ifstream input("../../input_test/heap_int_string.txt");

        if (!input.is_open()) {
            std::cout << "Failed to open file." << std::endl;
            return -1;
        } else {
            input >> dheap;

            std::vector<std::pair<int, std::string>> ordered_int;

            // algoritmo heap sort
            while (!dheap.isEmpty()) {
                std::pair<int, std::string> boh = dheap.popValue();
                // std::cout<<"popValue: "<<boh<<std::endl;
                ordered_int.push_back(boh);
            }

            std::cout << "Vettore ordinato in senso decrescente: \n";
            for (auto &value : ordered_int) {
                std::cout << value.first << " ";
            }
        }
        std::cout << "\n-------------- end HeapSort ---------------\n";
    } catch (std::exception &error) {
        std::cout << "Heap sort error: " << error.what() << "\n";
    }
    return 0;
}

/* ++++++++++++++++++ test TreeCopyCostructor +++++++++++++++++++ */
inline int testCopyCostructor() {
    try {
        std::cout << "\n++++++++++ Prova TreePtrList : ++++++++++\n";
        /*
         * std::string a{"a"},l{"l"},b{"b"}j;
         * std::string e{"e"},r{"r"},o{"o"};
         */

        std::ifstream input("../../input_test/tree.txt");

        // input.open("../tree.txt",std::ios_base::in);
        if (!input.is_open()) {
            std::cout << "Failed to open file." << std::endl;
            return -1;
        } else {

            auto tree = TreePosVector<std::string>(2, 10);

            // inizializzazione di tree tramite file
            input >> tree;

            std::cout << "tree: \n" << tree;
            TreePosVector<std::string> copyTree(tree);
            std::cout << "copyTree: \n" << copyTree;
        }
    } catch (const std::exception &e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}

inline int testGraphCopyCostructor() {
    try {
        std::cout << "\n++++++++++ Prova Graph copy costructor: ++++++++++\n";
        /*
         * std::string a{"a"},l{"l"},b{"b"}j;
         * std::string e{"e"},r{"r"},o{"o"};
         */

        std::ifstream input("../../input_test/oriented_graph.txt");

        // input.open("../tree.txt",std::ios_base::in);
        if (!input.is_open()) {
            std::cout << "Failed to open file." << std::endl;
            return -1;
        } else {

            auto graph = GraphEdgeList<std::string>();

            // inizializzazione di tree tramite file
            input >> graph;

            std::cout << "tree: \n" << graph;
            GraphEdgeList<std::string> copyGraph(graph);
            std::cout << "copyTree: \n" << copyGraph;
        }
    } catch (const std::exception &e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}

#endif