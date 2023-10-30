#ifndef NODE_H
#define NODE_H

#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

// todo togliere il pos nella classe node
namespace slothLib {
/**
 * \enum marking
 * \brief Enumeration for marking nodes during searches.
 */
enum marking { unexplored, open, closed };

//! @cond HIDE_THIS
template <class T> class Edge;

template <class T> class TreePosVector;
//! @endcond

/**
 * \class Node
 * \brief Represents a node in a graph or tree data structure.
 *
 * This class defines the structure for a node in a graph or tree. It includes
 * various attributes and methods to handle nodes.
 *
 * \author Nico Fiorini
 */
template <class T> class Node {
  private:
    /// The value associated with the node.
    T value;

    /// Marking for node during searches.
    marking mark = unexplored;

    /// List of outgoing nodes, used for TreePtrList.
    std::list<Node<T> *> node_list;

    /// List of connected edges, used for GraphIncList.
    std::list<Edge<T> *> connected_edges;

    /// Pointer to the parent node.
    Node<T> *parent;

    /// Attribute utility for TreePosVector.
    int pos;

    /// Number of children for the node.
    int num_children;

    // private constructor
    Node(T value, Node<T> *parent);

    // utility function for TreePtrList
    void addChildren(const std::list<Node<T> *> &_children);

  public:
    /**
     * \brief Default constructor for Node.
     */
    Node() {}

    /**
     * \brief Constructor for Node with a specified value.
     *
     * @param value The value to associate with the node.
     */
    Node(T value);

    Node(const Node<T> &x);

    /**
     * \brief Destructor for Node.
     */
    ~Node();

    /**
     * \brief Getter to retrieve the value associated with the node.
     *
     * @return The value associated with the node.
     */
    T getValue() const { return value; }

    /**
     * \brief Setter to change the value associated with the node.
     *
     * @param value The new value to be associated with the node.
     */
    void setValue(T value) { this->value = value; }

    /**
     * \brief Overloaded assignment operator for Node.
     *
     * @param x The node to assign values from.
     * @return A reference to the assigned node.
     */
    Node<T> &operator=(const Node<T> &x);

    /**
     * \brief Overloaded equality operator for nodes.
     *
     * @param x The node to compare with.
     * @return True if nodes are equal, false otherwise.
     */
    bool operator==(const Node<T> &x) const;
    /**
     * \brief Overloaded less than operator for nodes.
     *
     * @param x The node to compare with.
     * @return True if the node is less than the given node, false otherwise.
     */
    bool operator<(const Node<T> &x) const;
    /**
     * \brief Overloaded less than or equal to operator for nodes.
     *
     * @param x The node to compare with.
     * @return True if the node is less than or equal to the given node, false
     * otherwise.
     */

    /**
     * \brief Overloaded greater than operator for nodes.
     *
     * @param x The node to compare with.
     * @return True if the node is greater than the given node, false otherwise.
     */
    bool operator<=(const Node<T> &x) const;

    /**
     * \brief Overloaded greater than or equal to operator for nodes.
     *
     * @param x The node to compare with.
     * @return True if the node is greater than or equal to the given node,
     * false otherwise.
     */
    bool operator>(const Node<T> &x) const;
    /**
     * \brief Overloaded inequality operator for nodes.
     *
     * @param x The node to compare with.
     * @return True if nodes are not equal, false otherwise.
     */
    bool operator>=(const Node<T> &x) const;
    /**
     * \brief Overloaded inequality operator for nodes.
     *
     * @param x The node to compare with.
     * @return True if nodes are not equal, false otherwise.
     */
    bool operator!=(const Node<T> &x) const;
    
    friend std::istream& operator>>(std::istream &is, Node<T>& node)
    {
        is >> node.value;
        return is;
    }

    /**
     * \brief Overloaded output stream operator for nodes.
     *
     * @param os The output stream.
     * @param node The node to write values from.
     * @return The output stream after writing.
     */
    friend std::ostream &operator<<(std::ostream &os, const Node<T> &node) {
        os << node.value;
        return os;
    }

    // Friend classes.
    template <class U> friend class BasicGraph;
    template <class U> friend class Graph;
    template <class U> friend class Tree;
    template <class U> friend class TreePtrList;
    template <class U> friend class TreePosVector;
    template <class U> friend class GraphAdjList;
    template <class U> friend class Edge;
    template <class U> friend class GraphEdgeList;
    template <class U> friend class GraphIncList;
    template <class U, class W> friend class DHeap;
};

} // namespace slothLib
#include "../sources/Node.cpp"

#endif
