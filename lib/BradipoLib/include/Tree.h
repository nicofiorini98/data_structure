#ifndef TREE_H
#define TREE_H

#include "BasicGraph.h"
#include "Edge.h"
#include "Node.h"
#include <list>
#include <vector>

/**
 * \class Tree
 * \brief This class is a base class for various tree implementations
 *
 *
 * \author Nico Fiorini
 * \date 03/03/2021
 */

namespace datalib {

template <class T> class Tree : public BasicGraph<T> {
  protected:
    
    Node<T> *root;

  public:
    /// Costructor
    Tree() { this->numNodes = 0; }

    /// virtual destructor
    virtual ~Tree() {}

    /// return the number of sons for the node x
    virtual int getDegree(const T &value) = 0;

    /// return the father of the node childValue
    virtual T getParent(const T &childValue) = 0;

    /// return a list with the children of the node parentValue
    virtual std::list<T> getChildren(const T &parentValue) = 0;

    /// add root in the Tree
    virtual void addRoot(const T &rootValue) = 0;

    virtual std::list<Edge<T>> &getAllEdges(std::list<Edge<T>> &edges) = 0;

    /// add a Node in the Tree
    virtual void addNode(const T &value, const T &parent) = 0;
    
    // virtual void deleteNode(const T& value)=0;

    /// add childrens to node value
    virtual void addChildren(const T &value, const std::list<T> &children) = 0;

    // TODO da controllare
    virtual void depthSearch(const T &startValue) = 0;

    // TODO da controllare
    virtual void breadthSearch(const T &startValue) = 0;

    // TODO implementare
    virtual T getValue(const T &nodeValue) const override = 0;

    // TODO implementare
    virtual void setValue(const T &oldValue, const T &newValue) override = 0;

    // TODO implementare
    virtual void markNode(const T &value, marking mark) override {}

    // used in the searches
    virtual void updateParent(const T &childValue, const T &newParent) = 0;

    /// overloading operator >>
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

    /// overloading operator >>
    friend std::ostream &operator<<(std::ostream &os, Tree<T> &t) {
        std::list<Edge<T>> edges;
        // edges = t.getAllEdges(edges);
        for (auto &e : t.getAllEdges(edges)) {
            os << e << "\n";
        }
        return os;
    }
};
} // namespace datalib

#endif