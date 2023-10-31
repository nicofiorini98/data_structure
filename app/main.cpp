#include <iostream>

#include "Testing.h"
#include "Dijkstra.h"

#include "TreePtrList.h"


using namespace slothLib;


int main(){
    
    std::cout<<"Welcome to the library\n";
    std::cout<<"Here an example of TreePtrList output in CSV format\n";
    std::cout<<"+++++++++TreePtrList++++++++++++"<<"\n";
    
    TreePtrList<std::string> tree;

    std::ifstream input("../../input_test/tree.txt");
    // input.open("../tree.txt",std::ios_base::in);
    if (!input.is_open()) {
        std::cout << "Failed to open file." << std::endl;
        return -1;
    } else {
        input>>tree;
    }

    std::cout<<tree;

    input.close();

    std::cout<<"+++++++++ Prova input Output Grafo ++++++++"<<std::endl;
    GraphIncList<std::string> graph;

    input.open("../../input_test/oriented_graph.txt");
    // input.open("../tree.txt",std::ios_base::in);
    if (!input.is_open()) {
        std::cout << "Failed to open file." << std::endl;
        return -1;
    } else {
        input>>graph;
    }

    std::cout<<graph;

    input.close();
    
    // testGraphCopyCostructor();
    // testCopyCostructor();
    // testHeapSort();
    // Dijkstra();

    return 0;
}
