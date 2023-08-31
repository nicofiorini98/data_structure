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
 * \brief This class is a base class for various tree implementations
 *
 *
 * \author Nico Fiorini
 * \date 03/03/2021
 *
 * manage the nullptr for the root and the leafs
 */
namespace datalib {

/* --------------   Implementazione Iterator  -------------------*/

template <typename TreePtrList> class TreePtrListIterator {
public:
  using ValueType = typename TreePtrList::ValueType;
  using PointerType = ValueType *;
  using ReferenceType = ValueType &;

  TreePtrListIterator(PointerType ptr) : mPtr(ptr) {}

  // TODO da implementare
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

  // get node by value
  //  void getNode(T _value);

public:
  Iterator begin() { return Iterator(root); }
  /// \param _degree Costructor with default parameter,
  /// if degree is not specified, Tree doesn't have a particular degree
  TreePtrList(int degree = -1);

  /// virtual destructor
  ~TreePtrList(); // todo controllare

  // friend std::ostream &operator<<(std::ostream &is, TreePtrList<T> &t);
  /// return the number of sons for the node x
  int getDegree(const T &value) override; // ok

  /// return the parent of the node x
  void getParent(const T &value,
                 T &parent) override; // todo ok se non è root, controllare

  /// return a vector of the node x
  // void getChildren(const T &_x,std::list<T>& _list);
  void getChildren(const T &value, std::list<T> &children) override;

  void addRoot(const T& rootValue) override;
  /// add a node in the Tree
  ///\param _node is the node to add in the Tree
  ///\param _father is the parent of the node to be inserted,
  /// if not specified the node is the root of the Tree
  void addNode(const T& value, const T& parent)
      override; // ok, viene usato per l'inizializzazione dell'albero

  // add children to node _x
  void addChildren(const T &value, const std::list<T> &children) override;

  // void removeChild(const T& _x);

  /// print the node following a DFS visit
  void depthSearch(const T &startValue) override;

  /// print the node following BFS visit
  void breadthSearch(const T &startValue) override;

  void updateParent(const T &child, const T &newParent) override;

  void showTree();

  void showTreePtr();

  void showStructure();

  void showTree2();
  // aggiungi sotto albero
  // rimuovi sotto albero

  /// overloading operator >>
  friend std::istream &operator>>(std::istream &is, TreePtrList<T> &t) {
    // pre-conditions
    // the input work with csv format --> node2add, parent
    // example with string:
    // a
    // a,l
    // se il padre non è fornito, il nodo è la radice
    std::string line, x_string, parent_string;

    // read line-by-line
    while (std::getline(is, line)) {

      auto *x = new T;
      auto *parent = new T;

      std::stringstream str(line); // converte la riga in uno stream
      std::getline(str, x_string,
                   t.delimiter); // leggo lo stream della riga fino al carattere
                                 // delimitatore
      std::stringstream str1(x_string); // converte il primo campo in uno stream
      str1 >> *x; // viene utilizzata la funzione >> per l'input del primo campo
      std::getline(
          str, parent_string,
          t.delimiter); // continuo a leggere per trovare il secondo campo

      if (parent_string.empty()) {
        t.addRoot(*x);
        continue;
      }

      std::stringstream str2(parent_string);
      str2 >> *parent;
      t.addNode(*x, *parent);

      //deallocate x and parent to avoid memory leak
      delete x;
      delete parent;
    }
    return is;
  }

  friend std::ostream &operator<<(std::ostream &os, TreePtrList<T> t) {
    for (auto &n : t.nodes_map) {
      for (auto &child : t.getNodeList(n.second)) {
        os << "( " << *(n.second) << " " << *child << " )"
           << "\n";
      }
      // for(int i=0; i < t.getNumChildren(n.second);i++ )
    }
    return os;
  }
};
} // namespace datalib

#include "../sources/TreePtrList.cpp"
#endif