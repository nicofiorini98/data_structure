#ifndef TREE_H
#define TREE_H

#include "BasicGraph.h"
#include "Edge.h"
#include "Node.h"
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <vector>

namespace slothLib {
/**
 * @brief A generic tree data structure for representing hierarchical
 * relationships.
 *
 * This class is a generic tree data structure that represents hierarchical
 * relationships between nodes. It extends the BasicGraph class and provides
 * methods for adding and manipulating nodes within the tree.
 *
 * \author Nico Fiorini
 * @tparam T The type of data held by each node in the tree.
 */

template <class T> class Tree : public BasicGraph<T> {
  protected:
    Node<T> *root; /**< The root node of the tree. */
    int degree; /**< The maximum number of child nodes for each parent node. */

  public:
    /**
     * @brief Default constructor for creating an empty tree.
     */
    Tree() { this->numNodes = 0; }

    /**
     * @brief Copy constructor for creating a deep copy of another tree.
     * @param tree The tree to be copied.
     */
    Tree(const Tree<T> &tree) {

        this->degree = tree.getDegree();
        this->addRoot(tree.getRoot());

        std::list<Edge<T>> ed;
        for (auto &e : tree.getAllEdges(ed)) {
            this->addNode(e.getDestinationValue(), e.getSourceValue());
        }
    }

    /**
     * @brief Virtual destructor for Tree class.
     */
    virtual ~Tree() {}

    /**
     * @brief Output the tree as a DOT file for visualization.
     * @param dotFile The output stream to write the DOT file.
     * @return The output stream after writing the DOT file.
     */
    std::ostream &outputDotFile(std::ostream &dotFile) const override;

    /**
     * @brief Get the degree of the tree, which is the maximum number of child
     * nodes for each parent node.
     * @return The degree of the tree.
     */
    int getDegree() const { return this->degree; }

    /**
     * @brief Get the parent of a specific child node.
     * @param childValue The value of the child node for which the parent is
     * sought.
     * @return The parent node's value.
     */
    virtual T getParent(const T &childValue) = 0;

    /**
     * @brief Get a list of children nodes for a specific parent node.
     * @param parentValue The value of the parent node for which children are
     * sought.
     * @return A list of children nodes' values.
     */
    virtual std::list<T> getChildren(const T &parentValue) const = 0;

    /**
     * @brief Add a root node to the tree.
     * @param rootValue The value of the root node to be added.
     */
    virtual void addRoot(const T &rootValue){};

    /**
     * @brief Add a node to the tree with a specific parent node.
     * @param value The value of the node to be added.
     * @param parent The value of the parent node.
     */
    virtual void addNode(const T &value, const T &parent) {}

    /**
     * @brief Get the root node's value.
     * @return The value of the root node.
     */
    virtual T getRoot() const { return root->value; };

    /**
     * @brief Get a list of all edges in the tree.
     * @param edges The list to which the edges will be added.
     * @return The list of all edges in the tree.
     */
    virtual std::list<Edge<T>> &
    getAllEdges(std::list<Edge<T>> &edges) const = 0;

    /**
     * @brief Add children nodes to a specific node.
     * @param value The value of the parent node.
     * @param children A list of values for the children nodes to be added.
     */
    virtual void addChildren(const T &value, const std::list<T> &children) = 0;

    /**
     * @brief Perform a breadth-first search on the tree and retrieve the values
     * of nodes in the order visited.
     * @param values The list to which the values will be added.
     * @return The list of values resulting from the breadth-first search.
     */
    std::list<T> &breadthSearch(std::list<T> &values) const;

    /**
     * @brief Perform a depth-first search on the tree and retrieve the values
     * of nodes in the order visited.
     * @param values The list to which the values will be added.
     * @return The list of values resulting from the depth-first search.
     */
    std::list<T> &depthSearch(std::list<T> &values) const;

    virtual T getValue(const T &nodeValue) const override = 0;

    virtual void setValue(const T &oldValue, const T &newValue) override = 0;

    /**
     * @brief Overloads the input stream operator to read a Tree from a text
     * stream.
     *
     * This operator allows you to read a Tree object from an input stream using
     * a specified delimiter.
     *
     * @param is The input stream to read from.
     * @param t The Tree object to populate.
     * @return The input stream after reading the Tree.
     */
    friend std::istream &operator>>(std::istream &is, Tree<T> &t) {
        // pre-conditions
        // the input work with csv format --> node2add, parent
        // example with string:
        // a,l
        std::string line, x_string, parent_string;

        // read line-by-line
        while (std::getline(is, line)) {

            auto *x = new T;
            auto *parent = new T;

            std::stringstream str(line); // converte la riga in uno stream
            std::getline(str, x_string,
                         t.delimiter); // leggo lo stream della riga fino al
                                       // carattere delimitatore
            std::stringstream str1(
                x_string); // converte il primo campo in uno stream
            str1 >> *x;    // viene utilizzata la funzione >> per l'input del
                           // primo campo
            std::getline(str, parent_string,
                         t.delimiter); // continuo a leggere per trovare il
                                       // secondo campo

            if (parent_string.empty()) {
                t.addRoot(*x);
                continue;
            }

            std::stringstream str2(parent_string);
            str2 >> *parent;
            t.addNode(*x, *parent);

            // deallocate x and parent to avoid memory leak
            delete x;
            delete parent;
        }
        return is;
    }

    /**
     * @brief Overloads the output stream operator to write a Tree to a text
     * stream.
     *
     * This operator allows you to write a Tree object to an output stream.
     *
     * @param os The output stream to write to.
     * @param t The Tree object to write.
     * @return The output stream after writing the Tree.
     */
    friend std::ostream &operator<<(std::ostream &os, Tree<T> &t) {
        std::list<Edge<T>> edges;
        for (auto &e : t.getAllEdges(edges)) {
            os << e << "\n";
        }
        return os;
    }
};
} // namespace slothLib

#include "../sources/Tree.cpp"
#endif