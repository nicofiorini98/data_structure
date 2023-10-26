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
#include "Testing.h"
#include "Dijkstra.h"


using namespace slothLib;

// output stream to print std::pair
template <typename T1, typename T2>
std::ostream &operator<<(std::ostream &os, const std::pair<T1, T2> &p) {
    os << p.first ;
    return os;
}

int main(){

    // testTreePtrList();
    // testTreePosVector();
    // testCopyCostructor();
    // testGraphCopyCostructor();
    // testGraphEdgeList();
    // testGraphIncList();
    // testDHeapMin();
    // Dijkstra();


    return 0;
}
