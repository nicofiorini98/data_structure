#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <list>
#include <stack>
#include <queue>
#include "TreePtrList.h"
#include "Node.h"
#include "Edge.h"


namespace datalib{

    /**
     * \class Graph
     * \brief This class is abstract, is a base class for various implementations.
     * \author Nico Fiorini
     * \date 02/03/2021
     */

	template<class T>
    class Graph {
    private: 

    protected:
        int numNodes;
        int numEdges;
        char delimiter = ',';

    public:

        Graph(){
            numNodes=0;
            numEdges=0;
        }
        virtual ~Graph(){}

        ///return the number of the Node in the graph
        int numNode(){return numNodes;}             
        ///return the number of the Edge in the graph
        int numEdge(){return numEdges;}             
        ///return the grade of the node x 

        virtual int maxDegree()=0;                                   //restituisce il grado massimo del grafo
        virtual int degree(const T &value)=0;                            //restituisce il grado del nodo
        ///return the incident edge of the Node x
        virtual void getIncidentEdges(const T& value, std::list<Edge<T>>& edges)=0;
        virtual void getOutgoingEdges(const T& value, std::list<Edge<T>>& edges)=0;
        virtual void getIncomingEdges(const T& value, std::list<Edge<T>>& edges)=0;
        ///return the adjacent nodes of the Node x
        //void getExtremes(Edge* e);                         //return the Node of the Edge //is only for edge list
        //node* getOpposite(Node x,Edge e);                  //return the Node from the opposite side of the Edge  //is only for edge_list
        virtual bool isAdjacent(const T &srcValue,const T &destValue)=0;       //return true if the edge(x,y) exist, else return false

        //each data structure has own method for add Node and Edge
        virtual void addNode(const T &value)=0;                        //add a Node
        virtual void addEdge(const T *srcValue,const T *destValue)=0;       //add an Edge
        // virtual void addEdge(const Edge &_edge)=0;               //add an Edge
        virtual void deleteNode(const T &value)=0;                     //remove a Node in the graph
        virtual void deleteEdge(const T &srcValue,const T &destValue)=0;    //remove a Edge in the graph
        // virtual void deleteEdge(const Edge<T> &_edge)=0;         //remove a Edge in the graph

        //metodi per fare visite
        virtual void breadthSearch(const T& startValue, TreePtrList<T>& tree){};
        virtual void depthSearch(const T& startValue, TreePtrList<T>& tree){};
        virtual void markNode(const T& value,marking mark)=0;
        //virtual std::vector<T>& getAdjacentNode(const T& node); //return a vector with the adjacent of node

        friend std::istream &operator>>(std::istream &is, Graph<T> &graph){
            //pre-conditions
            //the input work with csv format --> node2add, parent
            //example with string:

            //std::cout<<"chiamata funzione\n";
            std::string line,srcString,destString;

            //read line-by-line

            while (std::getline(is, line)) {

                auto *src = new T;
                auto *dest= new T;

                std::stringstream str(line);                                 //converte la riga in uno stream
                std::getline(str, srcString, graph.delimiter);              //leggo lo stream della riga fino al carattere delimitatore
                std::stringstream str1(srcString);                          // converte il primo campo in uno stream
                str1 >> *src;                                                //viene utilizzata la funzione >> per l'input del primo campo

                std::getline(str, destString, graph.delimiter);             //continuo a leggere per trovare il secondo campo

                //todo vedere se conviene utilizzare un carattere delimitatore
                if (destString.empty()){
                    //graph.addEdge(src, nullptr);
                    continue;
                }
                std::stringstream str2(destString);
                str2 >> *dest;
                graph.addEdge(src,dest);
            }
            return is;
        }

        friend std::ostream& operator<<(std::ostream& os, Graph<T>& graph) {

            //todo finire questa funzione
            //std::list<Edge<T>> lista =

            return os;
        }

    };
}

#endif
