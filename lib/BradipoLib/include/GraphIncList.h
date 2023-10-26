#ifndef GRAPH_INC_LIST_H
#define GRAPH_INC_LIST_H

#include "Edge.h"
#include "Graph.h"
#include <map>
#include <vector>

namespace slothLib {

/**
 * @class GraphIncList
 * @brief This class is a data structure for a graph, implemented using an
 * incidence list technique.
 *
 * This class inherits from the Graph class and is designed to represent a graph
 * structure with an incidence list.
 *
 * @tparam T The type of the nodes in the graph.
 * @author Nico Fiorini
 */
template <class T> class GraphIncList : public Graph<T> {
  private:
    /// The incidence list data structure.
    std::map<T, Node<T> *> incList;
    /// A list of edges.
    std::list<Edge<T> *> edgeList;

    // bool edge_existence(const T &_src,const T &_dest) const;
    bool edgeExistence(const Edge<T> &edge) const;

    bool edgeExistence(const T *srcValue, const T *destValue) const;

    bool nodeExistence(const T *nodeValue) const;

  public:

    /**
     * @brief Default constructor for the GraphIncList.
     */
    GraphIncList();

    /**
     * @brief Copy constructor for the GraphIncList.
     *
     * @param otherGraph The graph to be copied.
     */
    GraphIncList(const GraphIncList<T> &otherGraph) {
        std::list<Edge<T>> edges;
        this->numEdges = otherGraph.numEdges;
        for (auto &e : otherGraph.getAllEdges(edges)) {
            this->addEdge(e.getSourceValue(), e.getDestinationValue(),
                          e.getWeight());
        }
    }

    /**
     * @brief Destructor for the GraphIncList.
     */
    virtual ~GraphIncList();

    void addNode(const T &value) override;

    int degree(const T &nodeValue) override;

    std::list<Edge<T>> &getAllEdges(std::list<Edge<T>> &edges) const override;

    T getValue(const T &nodeValue) const override;

    void setValue(const T &oldValue, const T &newValue) override;

    void addEdge(const T &srcValue, const T &destValue,
                 double weight = 0) override;

    void addEdge(const Edge<T> &edge) override;

    void deleteNode(const T &value) override;

    
    void deleteEdge(const T &srcValue, const T &destValue) override;

    /**
     * @brief Delete an edge from the graph structure.
     * 
     * @param edge to delete.
     */
    void deleteEdge(const Edge<T> &edge);

    std::list<Edge<T>> &getIncidentEdges(const T &value,
                                         std::list<Edge<T>> &edges) override;

    std::list<Edge<T>> &getOutgoingEdges(const T &value,
                                         std::list<Edge<T>> &edges) override;

    std::list<Edge<T>> &getIncomingEdges(const T &value,
                                         std::list<Edge<T>> &edges) override;

    TreePtrList<T> &breadthSearch(const T &startValue,
                                  TreePtrList<T> &tree) override;

    TreePtrList<T> &depthSearch(const T &startValue,
                                TreePtrList<T> &tree) override;

    // void getAllNodeValues(std::list<T> &nodesList);
};
} // namespace slothLib

#include "../sources/GraphIncList.cpp"

#endif