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
    
    tree.addRoot("radice");
    tree.addNode("figlio1","radice");
    tree.addNode("figlio2","radice");

    std::cout<<tree;

    return 0;
}
