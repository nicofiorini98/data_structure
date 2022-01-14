#ifndef GRAPH_EDGE_LIST_H 
#define GRAPH_EDGE_LIST_H


#include "graph.h"
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
    class graph_edge_list: public graph<T>{
    private: 

        bool edge_existence(const T *_src,const T *_dest) const;
        bool edge_existence(const T &_src,const T &_dest) const;
        bool node_existence(const T &_x) const;
        bool node_existence(const node<T> &_x) const;
        void addNode(node<T> *_x);
        // bool edge_existence(const edge<T> _e) const;
        std::vector<edge<T>> edge_list; 
        // std::map<T,node<T>*> adj_lists;   

    public:
        ///Default costructor for the GraphAdjList
        graph_edge_list();

        ///Costructor with a vector of Edge
        // graph_adj_list(const std::vector<Edge> &_edges);
        ///virtual Destructor
        virtual ~graph_edge_list(){} 

        ///add a Node x in the graph
        void addNode(const T &_x);
        int degree(const T &_x);

        ///add an Edge (x,y) in the graph
        void addEdge(const T *_src,const T *_dest);
        void addEdge(const edge<T>& _edge){};
        void deleteNode(const T &_x);                        //remove a Node in the graph
        void deleteEdge(const T &_src,const T &_dest){}      //remove a Edge in the graph
        // void deleteEdge(const Edge &_edge);               //remove a Edge in the graph
		// int grade(const T &_x){}

        std::vector<edge<T>> getIncidentEdge(const T &_x);          //return the incident edge of the Node x
        void getAdjNode(const T &_x){}
        void showStructure() const{}
        void showNode() const;
        //void showGraphPos() const;
        void showGraphValue() const{};

        friend std::ostream& operator<<(std::ostream& os,const graph_edge_list<T> &_graph){
            for(auto &e: _graph.edge_list){
                os<<e;
                os<<"\n";
            }
            return os;
        }
    };
    
}


#include "graph_edge_list.cpp"
#endif