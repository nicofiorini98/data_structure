#ifndef GRAPH_H
#define GRAPH_H

#include "BasicGraph.h"
#include "Edge.h"
#include "Node.h"
#include "TreePtrList.h"
#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <stack>

namespace slothLib {

/**
 * \class Graph
 * \brief Graph is an abstract class that inherits from BasicGraph and contains 
 * all the methods from Graph implementations.
 * \author Nico Fiorini
 * \date 02/03/2021
 */

template <class T> class Graph: public BasicGraph<T> {
  private:
  protected:
    int numEdges;

  public:
    
    /// Costructor
    Graph(): BasicGraph<T>(){
        numEdges = 0;
    }
    
    /// virtual Destructor
    virtual ~Graph() {}

    /// return the number of the Edge in the graph
    int numEdge() { return numEdges;}
    
    /// return the degree of nodeValue
    virtual int degree(const T &nodeValue) = 0;

    /// return all the Edge in the graph into a list
    virtual std::list<Edge<T>>& getAllEdges(std::list<Edge<T>> &edges) const = 0;

    /// return the incident edges of value
    virtual std::list<Edge<T>>& getIncidentEdges(const T &value,
                                  std::list<Edge<T>> &edges) = 0;

    /// return the outgoing edges of value
    virtual std::list<Edge<T>>& getOutgoingEdges(const T &value,
                                  std::list<Edge<T>> &edges) = 0;

    /// return the incoming edges of value
    virtual std::list<Edge<T>>& getIncomingEdges(const T &value,
                                  std::list<Edge<T>> &edges) = 0;

    /// add the node Value in the structure
    virtual void addNode(const T &value) = 0; // add a Node

    /// add the edge in the structure and create the nodes if doesn't exists
    virtual void addEdge(const Edge<T>& edge) = 0;

    /// add the edge in the structure and create the nodes if doesn't exists
    virtual void addEdge(const T& srcValue,
                         const T& destValue,
                         double weight = 0)=0; // add an Edge

    /// delete the node Value in the structure
    virtual void deleteNode(const T &value) = 0; // remove a Node in the graph

    /// delete the edge in the structure
    virtual void
    deleteEdge(const T &srcValue,
               const T &destValue) = 0; // remove a Edge in the graph


    /// return a list with the order based in breadthSearch
    virtual TreePtrList<T>& breadthSearch(const T &startValue, TreePtrList<T> &tree)=0;

    /// return a list with the order based in depthSearch
    virtual TreePtrList<T>& depthSearch(const T &startValue, TreePtrList<T> &tree)=0;

    /// return the value in the object based to the value passed
	virtual T getValue(const T& nodeValue) const override = 0;

    /// change the node in the object structure from oldValue to newValue
	virtual void setValue(const T& oldValue,const T& newValue) override = 0;
    
    friend std::istream &operator>>(std::istream &is, Graph<T> &graph) {
        // pre-conditions
        // the input work with csv format, example:
        // value, parent
        // value2, value

        // std::cout<<"chiamata funzione\n";
        std::string line, srcString, destString;

        // read line-by-line
        while (std::getline(is, line)) {

            auto *src = new T;
            auto *dest = new T;
            //
            // converte la riga in uno stream
            std::stringstream str(line);
            //leggo lo stream fino al carattere delimitatore
            std::getline(str, srcString,
                         graph.delimiter);
            
            // converte il primo campo in uno stream
            std::stringstream str1(srcString); 
            str1 >> *src;   
            
            // continuo a leggere per trovare il secondo campo
            std::getline(str, destString,graph.delimiter); 

            if (destString.empty()) {
                continue;
            }

            std::stringstream str2(destString);
            str2 >> *dest;
            graph.addEdge(*src, *dest);

            delete src;
            delete dest;
        }
        return is;
    }

    friend std::ostream &operator<<(std::ostream &os, Graph<T> &graph) {

        std::list<Edge<T>> edges;
        for(auto &e: graph.getAllEdges(edges)){
            os<<e<<"\n";            
        }
        return os;
    }

    std::ostream &outputDotFile(std::ostream &dotFile)const override{
        std::list<Edge<T>> edges;

        dotFile << "digraph G {\n";
        for (auto &e : this->getAllEdges(edges)) {

                dotFile << (e.src)->value << " -> ";
                dotFile << (e.dest)->value << " [label=\"" << e.getWeight() << "\"]";
                dotFile << "\n";
        }

        dotFile << "}";
        return dotFile;
    }
};
} // namespace datalib

#endif
