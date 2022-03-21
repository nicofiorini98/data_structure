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

        std::vector<Edge<T>> edge_list;

        void getIncidentEdges(const T& node,std::list<Edge<T>>& _list) override;
        void getOutgoingEdges(const T& node,std::list<Edge<T>>& _list) override;
        void getIncomingEdges(const T& node,std::list<Edge<T>>& _list) override;
        bool edge_existence(const T *_src,const T *_dest) const;
        bool edge_existence(const T &_src,const T &_dest) const;
        bool node_existence(const T &_x) const;
        bool node_existence(const Node<T> &_x) const;
        void addNode(Node<T> *_x);

    public:
        ///Default costructor for the GraphAdjList
        GraphEdgeList();

        ///Costructor with a vector of Edge
        // GraphAdjList(const std::vector<Edge> &_edges);
        ///virtual Destructor
        virtual ~GraphEdgeList(){}

        ///add a Node x in the graph
        void addNode(const T &_x) override;
        int degree(const T &_x)   override;

        ///add an Edge (x,y) in the graph
        void addEdge(const T *_src,const T *_dest) override;
        void addEdge(const Edge<T>& _edge){};
        void deleteNode(const T &_x)override;                        //remove a Node in the graph
        void deleteEdge(const T &_src,const T &_dest)override{}      //remove a Edge in the graph
        int maxDegree()override{}
        bool isAdjacent(const T &_src,const T &_dest)override{};       //return true if the edge(x,y) exist, else return false
        // void deleteEdge(const Edge &_edge);               //remove a Edge in the graph
		// int grade(const T &_x){}

        std::vector<Edge<T>> getIncidentEdge(const T &_x);          //return the incident edge of the Node x
        void getAdjNode(const T &_x){}
        void showStructure() const{}
        void showNode() const;
        //void showGraphPos() const;
        void showGraphValue() const{};

        //method for search on graph
        void markNode(const T& node,marking mark){}

        friend std::ostream& operator<<(std::ostream& os,const GraphEdgeList<T> &_graph){
            for(auto &e: _graph.edge_list){
                os<<e;
                os<<"\n";
            }
            return os;
        }
    };
    
}


#include "GraphEdgeList.cpp"
#endif