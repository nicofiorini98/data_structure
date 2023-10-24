#ifndef GRAPH_INC_LIST_H
#define GRAPH_INC_LIST_H


#include "Graph.h"
#include "Edge.h"
#include <map>
#include <vector>

namespace slothLib{

	/**
	 * \class GraphIncList
	 * \brief This class is a data structure for a graph,
	 * is implemented with incidency List tecnique .
	 * 
	 * Inherits from Graph class 
	 * \author Nico Fiorini
	*/
    //this scructure is implemented with vector of edge

    template<class T>
    class GraphIncList: public Graph<T>{
    private: 

		//this is the data structure
        std::map<T,Node<T>*> incList;
        std::list<Edge<T>*> edgeList;

        // bool edge_existence(const T &_src,const T &_dest) const;
        bool edgeExistence(const Edge<T> &edge) const;

        bool edgeExistence(const T* srcValue,const T* destValue) const;

        bool nodeExistence(const T* nodeValue) const;


    public:
        ///Default costructor for the GraphAdjList
        GraphIncList();
        
        /// CopyCostructor
        GraphIncList(const GraphIncList<T>& otherGraph) {
            std::list<Edge<T>> edges;
            this->numEdges = otherGraph.numEdges;
            for(auto& e: otherGraph.getAllEdges(edges)){
                this->addEdge(e.getSourceValue(),e.getDestinationValue(),e.getWeight());
            }
        }
        
        ///Costructor with a vector of Edge
        ///virtual Destructor
        virtual ~GraphIncList();

        ///add a Node x in the graph
        void addNode(const T &value) override;

        ///Return the degree of the node _x
        int degree(const T& nodeValue) override;

        std::list<Edge<T>>& getAllEdges(std::list<Edge<T>> &edges) const override;

        /// return the value in the object based to the value passed
	    T getValue(const T& nodeValue) const override;
        
        /// change the node in the object structure from oldValue to newValue
        void setValue(const T& oldValue,const T& newValue) override;

        void addEdge(const T& srcValue,const T& destValue,double weight = 0) override;

        void addEdge(const Edge<T>& edge)override;

        ///Delete the node from the Graph
        void deleteNode(const T& value) override;      

        ///Remove the Edge in the graph
        void deleteEdge(const T &srcValue,const T &destValue) override;

        ///Remove the Edge in the graph
        void deleteEdge(const Edge<T>& edge);                    

        /// Get the incident edges of a graph
        std::list<Edge<T>>& getIncidentEdges(const T& value, std::list<Edge<T>>& edges) override;

        /// Get the outgoing edges of a graph
        std::list<Edge<T>>& getOutgoingEdges(const T& value, std::list<Edge<T>>& edges) override;

        /// Get the incoming edges of a graph
        std::list<Edge<T>>& getIncomingEdges(const T& value, std::list<Edge<T>>& edges) override;

        ///method for search in Graph
        TreePtrList<T>& breadthSearch(const T& startValue, TreePtrList<T>& tree) override;

        TreePtrList<T>& depthSearch(const T& startValue, TreePtrList<T>& tree) override;
        
        /// return all node in the graph
        void getAllNodeValues(std::list<T>& nodesList);

        void showStructure() const;

        void showNode() const;

        void showGraphValue() const{}

    };
}

#include "../sources/GraphIncList.cpp"

#endif