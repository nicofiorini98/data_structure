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

template <class T> class TreePtrList : public Tree<T> {
private:

  int degree;

  // Node<T> *root;

  std::map<T, Node<T>*> nodes_map;

  std::list<Node<T> *> &getNodeList(Node<T> *value);

  int getNumChildren(Node<T> *value) { return value->node_list.size(); }

  Node<T> *getNode(const T value);

public:

  /// Costructor
  TreePtrList();

  /// virtual destructor
  // TODO  controllare
  ~TreePtrList(); 
  

  /// return the number of sons for the node x
  int getDegree(const T &value) override;

  /// return the nodeValue in the TreePtrList if exists
  T getValue(const T &nodeValue) const override;

  void setValue(const T &oldValue, const T &newValue) override;

  T getParent(const T &childValue) override;

  /// return a vector of the node x
  std::list<T> getChildren(const T& parentValue) override;

  /// add root in the Tree
  void addRoot(const T& rootValue) override;

  /// add a node in the Tree, permitted only if root exist
  ///\param _node is the node to add in the Tree
  ///\param _father is the parent of the node to be inserted,
  /// if not specified the node is the root of the Tree
  void addNode(const T& value, const T& parent)override;

  /// add children to node value
  void addChildren(const T &value, const std::list<T> &children) override;

  // TODO implementare come esempio ? 
  /// print the node following a DFS visit
  void depthSearch(const T &startValue) override;

  // TODO implementare come esempio ?
  /// print the node following BFS visit
  void breadthSearch(const T &startValue) override;

  void updateParent(const T &child, const T &newParent) override;


  // void showTree();

  // void showTreePtr();

  // void showStructure();


  std::ostream& outputDotFile(std::ostream& dotFile);
  
  std::list<Edge<T>>& getAllEdges(std::list<Edge<T>>& edges) override;

};
} // namespace datalib

#include "../sources/TreePtrList.cpp"
#endif