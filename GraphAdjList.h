#include "Graph.h"
#include <map>
#include <vector>


class GraphAdjList: public Graph
{
    std::map<int,std::list<Node*>> adj_lists;
     
public:
    GraphAdjList():Graph(){}
    GraphAdjList(const std::vector<Edge> &_edges);
    virtual ~GraphAdjList(){}

    void addNode(const Node &x);
    void addEdge(const Node &x,const Node &y);
    void addEdge(const Edge& _edge);
    void deleteNode(const Node &x);               //remove a Node in the graph
    void deleteEdge(const Node &x,const Node &y);               //remove a Edge in the graph
    void deleteEdge(const Edge &_edge);               //remove a Edge in the graph
    int grade(const Node &x){}

    //TODO da implementare 
    void getIncidentEdge(const Node &x){}          //return the incident edge of the Node x
    void getAdjNode(const Node &x){}


    void showGraph() const;
    //void showGraphPos() const;
    void showGraphValue() const;



};
