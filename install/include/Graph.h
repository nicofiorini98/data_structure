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
 * @class Graph
 * @brief A graph data structure template.
 *
 * This class provides a basic implementation of a graph data structure. It supports
 * adding and removing nodes and edges, as well as performing basic graph operations
 * such as breadth-first search and depth-first search.
 *
 * \author Nico Fiorini
 * @tparam T The type of the nodes in the graph.
 */

template <class T> class Graph: public BasicGraph<T> {
  private:
  protected:
    int numEdges;

  public:
    
    /**
     * @brief Constructor for the Graph.
     *
     * Initializes the number of edges to 0.
     */
    Graph(): BasicGraph<T>(){
        numEdges = 0;
    }
    
    /**
     * @brief Virtual destructor for the Graph.
     */
    virtual ~Graph() {}

    /**
     * @brief Get the number of edges in the graph.
     * @return The number of edges in the graph.
     */
    int numEdge() { return numEdges;}
    
    /**
     * @brief Get the degree of a node with a specific value.
     * 
     * @param nodeValue The value of the node.
     * @return The degree of the node.
     */
    virtual int degree(const T &nodeValue) = 0;

    /**
     * @brief Get all the edges in the graph into a list.
     * 
     * @param edges The list to store the edges.
     * @return A list containing all the edges in the graph.
     */
    virtual std::list<Edge<T>>& getAllEdges(std::list<Edge<T>> &edges) const = 0;

    /**
     * @brief Get the incident edges of a node with a specific value.
     * 
     * @param value The value of the node.
     * @param edges The list to store the incident edges.
     * @return A list containing the incident edges of the node.
     */
    virtual std::list<Edge<T>>& getIncidentEdges(const T &value,
                                  std::list<Edge<T>> &edges) = 0;

    /**
     * @brief Get the outgoing edges of a node with a specific value.
     * 
     * @param value The value of the node.
     * @param edges The list to store the outgoing edges.
     * @return A list containing the outgoing edges of the node.
     */
    virtual std::list<Edge<T>>& getOutgoingEdges(const T &value,
                                  std::list<Edge<T>> &edges) = 0;

    /**
     * @brief Get the incoming edges of a node with a specific value.
     * 
     * @param value The value of the node.
     * @param edges The list to store the incoming edges.
     * @return A list containing the incoming edges of the node.
     */
    virtual std::list<Edge<T>>& getIncomingEdges(const T &value,
                                  std::list<Edge<T>> &edges) = 0;

    /**
     * @brief Add a node with a specific value to the graph structure.
     * 
     * @param value The value of the node to be added.
     */
    virtual void addNode(const T &value) = 0;

    /**
     * @brief Add an edge to the graph structure and create the nodes if they do not exist.
     * 
     * @param edge The edge to be added.
     */
    virtual void addEdge(const Edge<T>& edge) = 0;

    /**
     * @brief Add an edge to the graph structure and create the nodes if they do not exist.
     * 
     * @param srcValue The value of the source node.
     * @param destValue The value of the destination node.
     * @param weight The weight of the edge (default is 0).
     */
    virtual void addEdge(const T& srcValue,
                         const T& destValue,
                         double weight = 0)=0; 

    /**
     * @brief Delete a node with a specific value from the graph structure.
     * 
     * @param value The value of the node to be deleted.
     */
    virtual void deleteNode(const T &value) = 0;

    /**
     * @brief Delete an edge from the graph structure.
     * 
     * @param srcValue The value of the source node.
     * @param destValue The value of the destination node.
     */
    virtual void deleteEdge(const T &srcValue,const T &destValue) = 0;

    /**
     * @brief Perform breadth-first search starting from a node with a specific value.
     * 
     * @param startValue The value of the starting node.
     * @param tree The tree to store the search results.
     * @return A list with the order based on breadth-first search.
     */
    virtual TreePtrList<T>& breadthSearch(const T &startValue, TreePtrList<T> &tree)=0;

    /**
     * @brief Perform depth-first search starting from a node with a specific value.
     * 
     * @param startValue The value of the starting node.
     * @param tree The tree to store the search results.
     * @return A list with the order based on depth-first search.
     */
    virtual TreePtrList<T>& depthSearch(const T &startValue, TreePtrList<T> &tree)=0;

	virtual T getValue(const T& nodeValue) const override = 0;

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
