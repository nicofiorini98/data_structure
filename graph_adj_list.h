#include "graph.h"
#include <map>
#include <vector>

/**
 * \class GraphAdjList
 * \brief This class is a data structure for a graph,
 * is implemented with Adjacency List.
 * 
 * Inherits from Graph class 
 * An AdjList is ideal for Breadth-first search
 * and Depth-first search. 
 * \author Nico Fiorini
 */
namespace datalib{


    class graph_adj_list: public graph
    {
    private: 
        std::map<int,std::list<node*>> adj_lists;
        
    public:
        ///Default costructor for the GraphAdjList
        graph_adj_list(): graph(){}

        ///Costructor with a vector of Edge
        graph_adj_list(const std::vector<Edge> &_edges);
        ///virtual Destructor
        virtual ~graph_adj_list(){}

        ///add a Node x in the graph
        void addNode(const node &x);
        ///add an Edge (x,y) in the graph
        void addEdge(const node &x,const node &y);
        void addEdge(const Edge& _edge);
        void deleteNode(const node &x);                             //remove a Node in the graph
        void deleteEdge(const node &x,const node &y);               //remove a Edge in the graph
        void deleteEdge(const Edge &_edge);               //remove a Edge in the graph
        int grade(const node &x){}

        void getIncidentEdge(const node &x){}          //return the incident edge of the Node x
        void getAdjNode(const node &x){}


        void showGraph() const;
        //void showGraphPos() const;
        void showGraphValue() const;



    };

}