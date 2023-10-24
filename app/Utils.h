#include <exception>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "GraphIncList.h"
#include "BasicGraph.h"
// #include "Testing.h"

//Required GraphViz installed on the system
template <class T>
void printGraphPng(Graph<T>* graph,const std::string& nameFileDot, const std::string& nameFilePng){

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

template <class T>
void printTreePng(Tree<T>* tree,const std::string& nameFileDot, const std::string& nameFilePng){

    std::string path = "/home/nico/project/data_structure/output_test/";
    std::string nameDotFile = path + nameFileDot;

    std::ofstream dotFile(nameDotFile,std::ios::out);

    tree->outputDotFile(dotFile);

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

inline void graphImage(const std::string& nameFileDot, const std::string& nameFilePng){

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
