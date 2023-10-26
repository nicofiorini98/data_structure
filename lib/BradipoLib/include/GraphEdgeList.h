#ifndef GRAPH_EDGE_LIST_H
#define GRAPH_EDGE_LIST_H

#include "Graph.h"
// #include <map>
#include <vector>

namespace slothLib {

/**
 * @class GraphEdgeList
 * @brief A data structure for a graph implemented with an edge list technique.
 *
 * This class represents a graph using an edge list data structure. It inherits
 * from the Graph class and provides methods to work with the graph.
 *
 * @tparam T The type of data associated with the nodes in the graph.
 * @author Nico Fiorini
 */

template <class T> class GraphEdgeList : public Graph<T> {
  private:
    std::vector<Edge<T> *> edgeList;

    /**
     * Check the existence of an edge between source and destination values.
     * @param srcValue Source node value.
     * @param destValue Destination node value.
     * @return True if the edge exists; otherwise, false.
     */
    bool edgeExistence(const T *srcValue, const T *destValue) const;

    /**
     * Check the existence of an edge between source and destination values.
     * @param srcValue Source node value.
     * @param destValue Destination node value.
     * @return True if the edge exists; otherwise, false.
     */
    bool edgeExistence(const T &srcValue, const T &destValue) const;
    /**
     * Get pointers to edges associated with a specific node value.
     * @param value Node value.
     * @param edges List of edge pointers to be populated.
     * @return List of edge pointers.
     */
    std::list<Edge<T> *> getEdgesPtr(const T &value,
                                     std::list<Edge<T> *> &edges);

    bool nodeExistence(const Node<T> &value) const;

    /**
     * Check the existence of a node with a given value.
     * @param value Node value.
     * @return Pointer to the existing node, or nullptr if not found.
     */
    Node<T> *nodeExistence(const T &value);

    void setValue(Node<T> &oldValue, Node<T> &newValue);

  public:
    /**
     * Default constructor for GraphEdgeList.
     */
    GraphEdgeList();

    /**
     * Copy constructor for GraphEdgeList.
     * @param otherGraph Another GraphEdgeList object to copy.
     */
    GraphEdgeList(const GraphEdgeList<T> &otherGraph) {
        std::list<Edge<T>> edges;
        this->numEdges = otherGraph.numEdges;
        for (auto &e : otherGraph.getAllEdges(edges)) {
            this->addEdge(e.getSourceValue(), e.getDestinationValue(),
                          e.getWeight());
        }
    }

    /**
     * Destructor for GraphEdgeList.
     */
    virtual ~GraphEdgeList();

    void addNode(const T &value) override;

    T getValue(const T &value) const override;

    void setValue(const T &oldValue, const T &newValue) override;

    int degree(const T &value) override;

    void addEdge(const T &srcValue, const T &destValue,
                 double weight = 0) override; // add an Edge

    void addEdge(const Edge<T> &edge) override{};

    void deleteNode(const T &value) override;

    void deleteEdge(const T &srcValue, const T &destValue) override {}

    std::list<Edge<T>> &getAllEdges(std::list<Edge<T>> &edges) const override;

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
};

} // namespace slothLib

#include "../sources/GraphEdgeList.cpp"
#endif