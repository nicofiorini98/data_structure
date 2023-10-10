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
/**
 * \class Tree
 * \brief This class is an implementation of tree
 * This is the most flexible implementation of this library, because doesn't have degree
 * limits of node. Doesn't have limit in terms of size.
 *
 * \author Nico Fiorini
 * \date 03/03/2021
 *
 */
namespace datalib {

/* --------------   Implementazione Iterator  -------------------*/

template <typename TreePtrList> class TreePtrListIterator {
public:
  using ValueType = typename TreePtrList::ValueType;
  using PointerType = ValueType *;
  using ReferenceType = ValueType &;

  TreePtrListIterator(PointerType ptr) : mPtr(ptr) {}

  // TODO vedere se continuare a implementare
  ReferenceType operator*() const { return *mPtr; }
  PointerType operator->() { return mPtr; }
  TreePtrListIterator &operator++();
  TreePtrListIterator operator++(int);

  friend bool operator==(const TreePtrListIterator &a,
                         const TreePtrListIterator &b) {
    return a.mPtr == b.mPtr;
  }
  friend bool operator!=(const TreePtrListIterator &a,
                         const TreePtrListIterator &b) {
    return a.mPtr != b.mPtr;
  }

private:
  PointerType mPtr;
};

/* --------------   Implementazione TreePtrList -------------------*/

template <class T> class TreePtrList : public Tree<T> {
private:

  using ValueType = T;
  using Iterator = TreePtrListIterator<TreePtrList<T>>;

  int degree;

  Node<T> *root;

  std::map<T, Node<T> *> nodes_map;

  std::list<Node<T> *> &getNodeList(Node<T> *value);

  int getNumChildren(Node<T> *value) { return value->node_list.size(); }

  Node<T> *getNode(const T value);

public:

  // TODO togliere o implementare
  Iterator begin() { return Iterator(root); }

  /// Costructor
  TreePtrList();

  /// virtual destructor
  // TODO  controllare
  ~TreePtrList(); 

  /// return the number of sons for the node x
  int getDegree(const T &value) override;

  T getParent(const T &childValue) override;

  /// return a vector of the node x
  std::list<T> getChildren(const T& parentValue) override;

  /// add root in the Tree
  void addRoot(const T& rootValue) override;

  /// add a node in the Tree, permitted only if root exist
  ///\param _node is the node to add in the Tree
  ///\param _father is the parent of the node to be inserted,
  /// if not specified the node is the root of the Tree
  void addNode(const T& value, const T& parent)
      override; // ok, viene usato per l'inizializzazione dell'albero

  /// add children to node value
  void addChildren(const T &value, const std::list<T> &children) override;

  // TODO implementare come esempio ? 
  /// print the node following a DFS visit
  void depthSearch(const T &startValue) override;

  // TODO implementare come esempio ?
  /// print the node following BFS visit
  void breadthSearch(const T &startValue) override;

  void updateParent(const T &child, const T &newParent) override;


  void showTree();

  void showTreePtr();

  void showStructure();

  void showTree2();
  // aggiungi sotto albero
  // rimuovi sotto albero

  std::ostream& outputDotFile(std::ostream& dotFile);

  friend std::ostream &operator<<(std::ostream &os, TreePtrList<T> t) {
    for (auto &n : t.nodes_map) {
      for (auto &child : t.getNodeList(n.second)) {
        os << *(n.second) << " " << *child <<"\n";
      }
    }
    return os;
  }

};
} // namespace datalib

#include "../sources/TreePtrList.cpp"
#endif