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

        bool edgeExistence(const T *srcValue,const T *destValue) const;
        bool edgeExistence(const T &srcValue,const T &destValue) const;

        bool nodeExistence(const T &value) const;
        bool nodeExistence(const Node<T> &value) const;

    public:
        ///Default costructor for the GraphAdjList
        GraphEdgeList();

        GraphEdgeList(const GraphEdgeList<T>& otherGraph) {
            std::list<Edge<T>> edges;
            this->numEdges = otherGraph.numEdges;
            for(auto& e: otherGraph.getAllEdges(edges)){
                this->addEdge(e.getSourceValue(),e.getDestinationValue(),e.getWeight());
            }
        }

        ///Costructor with a vector of Edge
        ///virtual Destructor
        virtual ~GraphEdgeList();

        ///add a Node x in the graph
        void addNode(const T &value) override;
        
        ///
        T getValue(const T& value) const override;

        void setValue(const T& oldValue, const T& newValue)  override;

        int degree(const T &value)   override;

        ///add an Edge (x,y) in the graph
        void addEdge(const T& srcValue, const T& destValue, double weight = 0)override; // add an Edge
        
        void addEdge(const Edge<T>& edge)override{};

        /// delete the node in the structure
        void deleteNode(const T &value)override;

        // remove the edge
        void deleteEdge(const T &srcValue,const T &destValue)override{}

        bool isAdjacent(const T &srcValue,const T &destValue) override;       //return true if the edge(x,y) exist, else return false

        std::list<Edge<T>>& getAllEdges(std::list<Edge<T>> &edges) const override;
        
        //TODO controllare
        std::vector<Edge<T>> getIncidentEdge(const T &value);          //return the incident edge of the Node x

        std::list<Edge<T>>& getIncidentEdges(const T& node,std::list<Edge<T>>& edges) override;

        std::list<Edge<T>>& getOutgoingEdges(const T& node,std::list<Edge<T>>& edges) override;

        std::list<Edge<T>>& getIncomingEdges(const T& node,std::list<Edge<T>>& edges) override;


        //method for search on graph
        void markNode(const T& value,marking mark)override{}

        
    };
    
}


#include "../sources/GraphEdgeList.cpp"
#endif