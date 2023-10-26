#ifndef EDGE_H
#define EDGE_H
#include "Node.h"
#include <iostream>
#include <sstream>
#include <string>

namespace slothLib {

/**
 * @class Edge
 * @brief Represents an edge in a graph.
 *
 * This class defines an edge in a graph. It stores information about the
 * source, destination, and weight of the edge.
 *
 * @tparam T The type of data associated with the nodes in the edge.
 */
template <class T> class Edge {

  private:
    Node<T>* src;       ///< Pointer to the source node.
    Node<T>* dest;      ///< Pointer to the destination node.
    double weight;     ///< Weight of the edge.
    char delimiter = ',';  ///< Delimiter used for stream I/O.

    /**
     * Private constructor for creating an edge.
     * @param src Pointer to the source node.
     * @param dest Pointer to the destination node.
     * @param weight Weight of the edge.
     * @param mark Mark associated with the edge (optional).
     */
    Edge(Node<T> *src, Node<T> *dest, int weight = 0,
         const std::string mark = "");

  public:
    /**
     * Default constructor for Edge.
     */
    Edge() : src(nullptr), dest(nullptr), weight(0) {}
    
    /**
     * Public constructor for creating an edge.
     * @param src Pointer to the source node.
     * @param dest Pointer to the destination node.
     * @param weight Weight of the edge.
     * @param mark Mark associated with the edge (optional).
     */
    Edge(const T *src, const T *dest, int weight = 0,
         const std::string &mark = "");

    /**
     * Copy constructor for Edge.
     * @param x Another Edge object to copy.
     */
    Edge(const Edge<T> &x);

    /**
     * Destructor for Edge. It cleans up allocated memory for source and destination nodes.
     */
    ~Edge() {
        delete src;
        delete dest;
    }

    /**
     * Get the source value of the edge.
     * @return Source node's value.
     */
    T getSourceValue() const { return (src->value); }

    /**
     * Get the destination value of the edge.
     * @return Destination node's value.
     */ 
    T getDestinationValue() const { return (dest->value); }

    /**
     * Get the weight of the edge.
     * @return Weight of the edge.
     */
    double getWeight() const { return this->weight; }

    /**
     * Set the weight of the edge.
     * @param weight New weight for the edge.
     */
    void setWeight(double weight) { this->weight = weight; }

    /**
     * Overloaded output stream operator for Edge.
     * @param os Output stream.
     * @param edge Edge object to be written to the stream.
     * @return Reference to the output stream.
     */
    friend std::ostream &operator<<(std::ostream &os, const Edge<T> &edge) {
        os << edge.getSourceValue() << edge.delimiter
           << edge.getDestinationValue();
        return os;
    }

    /**
     * Overloaded input stream operator for Edge.
     * @param is Input stream.
     * @param edge Edge object to read from the stream.
     * @return Reference to the input stream.
     */
    friend std::istream &operator>>(std::istream &is, Edge<T> &edge) {

        if ((edge.src)) {
            delete (edge.src);
        }

        if ((edge.dest)) {
            delete (edge.dest);
        }

        edge.src = new Node<T>();
        edge.dest = new Node<T>();

        std::string line;
        std::getline(is, line, ',');
        std::stringstream str(line);
        str >> (*edge.src);

        std::getline(is, line);
        std::stringstream str2(line);
        str2 >> (*edge.dest);

        return is;
    }

    template <class U> friend class Graph;

    template <class U> friend class GraphEdgeList;

    template <class U> friend class GraphIncList;
};
} // namespace slothLib

#include "../sources/Edge.cpp"

#endif