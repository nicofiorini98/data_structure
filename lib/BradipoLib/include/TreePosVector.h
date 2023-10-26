#ifndef TREE_POS_VECTOR_H
#define TREE_POS_VECTOR_H
#include "Tree.h"
#include <sstream>
/*
 * Sia T=(N,A), un albero d-ario con n nodi,
 * un vettore posizionale è un array P di dimensione n
 * tale che P[v] contiene l'informazione associata al nodo v,
 * e tale che l'informazione associata all'i-esimo figlio di v è in posizione
 * P[d*v+i] per 0<i<d-1
 *
 * Per comodità l'indice 0 lo posso lascia perde.
 */

namespace slothLib {

/**
 * @class TreePosVector
 * @brief A Tree data structure implemented with vector positions.
 *
 * The TreePosVector class represents a tree data structure implemented using
 * vector positions. It imposes structural constraints on the maximum node
 * degree and the maximum tree height.
 *
 * @tparam T The type of the nodes in the tree.
 * @author Nico Fiorini
 */
template <class T> class TreePosVector : public Tree<T> {
  private:
    /// Vector of suitably positioned nodes.
    std::vector<Node<T> *> vecNode;
    int maxNumNodes;
    int height;

    /**
     * Get the position of a node in the vector.
     * @param value The node for which to find the position.
     * @return The position of the node in the vector.
     */
    int getPos(Node<T> *value) { return value->pos; }

    /**
     * Get the position of the parent node given the child's position.
     * @param posChild The position of the child node.
     * @return The position of the parent node.
     */
    int getParentPos(int posChild);

    /**
     * Add a child node to a parent node.
     * @param value The parent node's value.
     * @param child The child node's value.
     */
    void addChild(const T *value, const T *child);

    /**
     * Swap the positions and values of two nodes.
     * @param posNode1 The position of the first node.
     * @param posNode2 The position of the second node.
     */
    void swapPositionValue(int posNode1, int posNode2);

    /**
     * Check if a node is a leaf node.
     * @param value The node's value.
     * @return True if the node is a leaf; otherwise, false.
     */
    bool isLeaf(const T &value);

    /**
     * Add a list of values to the tree.
     * @param values The list of values to add.
     */
    void addValuesFromVector(const std::vector<T> &values);

  public:
    /**
     * Default constructor for TreePosVector.
     * @param maxDegree The maximum degree of the nodes.
     * @param height The maximum height of the tree.
     */
    TreePosVector(int maxDegree, int height);

    /**
     * Copy constructor for TreePosVector.
     * @param tree The tree to be copied.
     */
    TreePosVector(const TreePosVector<T> &tree) {
        // initialization parameter
        this->degree = tree.degree;
        // this->root = ;
        this->height = tree.height;

        // computation of maxNumNodes allowed from the data_structure
        maxNumNodes = 0;
        for (int i = 0; i <= this->height; i++) {
            maxNumNodes += pow(this->degree, i);
        }

        // initialization vector (nullptr)
        vecNode.resize(this->maxNumNodes);

        this->addRoot(tree.getRoot());

        std::list<Edge<T>> ed;
        for (auto &e : tree.getAllEdges(ed)) {
            this->addNode(e.getDestinationValue(), e.getSourceValue());
        }
    }

    ///@brief Virtual Destructor
    virtual ~TreePosVector();

    /**
     * Get a list of all edges in the tree.
     * @param edges The list to be populated with edges.
     * @return List of edges.
     */
    std::list<Edge<T>> &getAllEdges(std::list<Edge<T>> &edges) const override;

    T getValue(const T &nodeValue) const override;

    void setValue(const T &oldValue, const T &newValue) override;

    /**
     * Get the number of children of a specific node.
     * @param value The value of the node.
     * @return The number of children.
     */
    int getNumChildren(const T &value);

    T getParent(const T &childValue) override;

    std::list<T> getChildren(const T &parentValue) const override;

    void addRoot(const T &rootValue) override;

    void addNode(const T &value, const T &parent) override;

    void addChildren(const T &value, const std::list<T> &children) override;

    template <class U, class W> friend class DHeap;
};

template <class T>
typename std::vector<Node<T> *>::iterator
trova(typename std::vector<Node<T> *>::iterator begin,
      typename std::vector<Node<T> *>::iterator end, const T &value) {

    int i = 0;
    typename std::vector<Node<T> *>::iterator appo;
    for (appo = begin; appo != end; ++appo) {

        // if appo is nullptr, don't check equality, it is certainly
        // different
        if (*appo == nullptr)
            continue;

        if (**appo == value) {
            return appo;
        }
    }
    return end;
}

template <class T>
typename std::vector<Node<T> *>::const_iterator
trova(typename std::vector<Node<T> *>::const_iterator begin,
      typename std::vector<Node<T> *>::const_iterator end, const T &value) {

    int i = 0;
    typename std::vector<Node<T> *>::const_iterator appo;
    for (appo = begin; appo != end; ++appo) {

        // if appo is nullptr, don't check equality, it is certainly
        // different
        if (*appo == nullptr)
            continue;

        if (**appo == value) {
            return appo;
        }
    }
    return end;
}
} // namespace slothLib

#include "../sources/TreePosVector.cpp"
#endif