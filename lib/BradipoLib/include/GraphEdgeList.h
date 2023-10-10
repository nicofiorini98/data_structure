#ifndef GRAPH_EDGE_LIST_H 
#define GRAPH_EDGE_LIST_H


#include "Graph.h"
// #include <map>
#include <vector>

namespace datalib{

	/**
	 * \class GraphAdjList
	 * \brief This class is a data structure for a graph,
	 * is implemented with Adjacency List tecnique .
	 * 
	 * Inherits from Graph class 
	 * \author Nico Fiorini
	*/
    //this scructure is implemented with vector of edge

    template<class T>
    class GraphEdgeList: public Graph<T>{
    private:

        std::vector<Edge<T>> edgeList;

        //TODO vedere se servono tutti e due 
        bool edgeExistence(const T *srcValue,const T *destValue) const;
        bool edgeExistence(const T &srcValue,const T &destValue) const;

        bool nodeExistence(const T &value) const;
        bool nodeExistence(const Node<T> &value) const;

    public:
        ///Default costructor for the GraphAdjList
        GraphEdgeList();

        ///Costructor with a vector of Edge
        // GraphAdjList(const std::vector<Edge> &_edges);
        ///virtual Destructor
        virtual ~GraphEdgeList(){}

        ///add a Node x in the graph
        void addNode(const T &value) override;

        int degree(const T &value)   override;

        ///add an Edge (x,y) in the graph
        void addEdge(const T *srcValue,const T *destValue) override;
        
        void addEdge(const Edge<T>& edge){}; //todo aggiungere nell'interfaccia

        void deleteNode(const T &value)override;                        //remove a Node in the graph

        void deleteEdge(const T &srcValue,const T &destValue)override{} //remove a Edge in the graph

        int maxDegree() override {return 0;}

        bool isAdjacent(const T &srcValue,const T &destValue) override;       //return true if the edge(x,y) exist, else return false

        // void deleteEdge(const Edge &_edge);               //remove a Edge in the graph

		// int grade(const T &_x){}

        std::list<Edge<T>>& getAllEdges(std::list<Edge<T>> &edges) override;
        
        //TODO controllare
        std::vector<Edge<T>> getIncidentEdge(const T &value);          //return the incident edge of the Node x

        void getIncidentEdges(const T& node,std::list<Edge<T>>& edges) override;

        void getOutgoingEdges(const T& node,std::list<Edge<T>>& edges) override;

        void getIncomingEdges(const T& node,std::list<Edge<T>>& edges) override;

        void showStructure() const{}

        void showNode() const;
        //void showGraphPos() const;
        void showGraphValue() const{};

        //method for search on graph
        void markNode(const T& value,marking mark){}

        
    };
    
}


#include "../sources/GraphEdgeList.cpp"
#endif