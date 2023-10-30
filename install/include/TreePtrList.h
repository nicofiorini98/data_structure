#ifndef TREE_PTR_LIST_H
#define TREE_PTR_LIST_H
#include <iostream>
//#include <fstream>
#include "Node.h"
#include "Tree.h"
#include <map>
#include <queue>
#include <sstream>
#include <stack>

namespace slothLib {
/**
 * \class TreePtrList
 * \brief This class is an implementation of a tree structure.
 *
 * This implementation provides a flexible tree structure that doesn't have
 * degree limits for nodes and has no specific size limits.
 *
 * \author Nico Fiorini
 */

template <class T> class TreePtrList : public Tree<T> {
  private:
    std::map<T, Node<T> *>
        nodesMap; /**< A map that stores nodes in the tree. */

    std::list<Node<T> *> &getNodeList(Node<T> *value);

    int getNumChildren(Node<T> *value) { return value->node_list.size(); }

    Node<T> *getNode(const T value);

  public:
    /**
     * \brief Constructor for the TreePtrList.
     */
    TreePtrList();

    /**
     * \brief Copy constructor for the TreePtrList.
     *
     * @param tree The tree to be copied.
     */
    TreePtrList(const TreePtrList<T> &tree) : Tree<T>(tree) {}

    /**
     * \brief Destructor for the TreePtrList.
     */
    ~TreePtrList();

    std::list<Edge<T>> &getAllEdges(std::list<Edge<T>> &edges) const override;

    T getValue(const T &nodeValue) const override;

    void setValue(const T &oldValue, const T &newValue) override;

    T getParent(const T &childValue) override;

    std::list<T> getChildren(const T &parentValue) const override;

    void addRoot(const T &rootValue) override;

    void addNode(const T &value, const T &parent) override;

    void addChildren(const T &value, const std::list<T> &children) override;

    void updateParent(const T &child, const T &newParent);
};
} // namespace slothLib

#endif
#include "../sources/TreePtrList.cpp"