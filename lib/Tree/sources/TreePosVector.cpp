
#ifndef TREE_POS_VECTOR_CPP
#define TREE_POS_VECTOR_CPP
#include "Node.h"
#pragma once
#include "TreePosVector.h"
#include "Tree.h"
#include <math.h>

using namespace datalib;

// I need to know the grade of the tree and the
// num_nodes for instatiate the tree
template <class T>
TreePosVector<T>::TreePosVector(int maxDegree, int height) : Tree<T>() {
    // initialization parameter
    this->degree = maxDegree;
    root = nullptr;
    this->height = height;

    // computation of maxNumNodes allowed from the data_structure
    maxNumNodes = 0;
    for (int i = 0; i <= height; i++) {
        maxNumNodes += pow(degree, i);
    }

    // initialization vector (nullptr)
    vecNode.resize(this->maxNumNodes);

    // std::cout<<"size of the vector: "<<vecNode.size()<<"\n";
}

template <class T>
void TreePosVector<T>::addRoot(const T &rootValue){
    Node<T> *x_ptr = new Node<T>(rootValue);
    root = x_ptr;
    vecNode[1] = x_ptr;
    x_ptr->pos = 1;
}

template <class T>
void TreePosVector<T>::addNode(const T& value, const T& parent) {

    static int call = 0;
    call++;

    // local iterator, typename because are nested dependent names
    typename std::vector<Node<T> *>::iterator x_itr;
    typename std::vector<Node<T> *>::iterator parent_itr;

    // pre-conditions:
    // 1. the node x to add must be different from nullptr
    // 2. the node parent must exists if different from nullptr
    // 3. the parent nullptr means that x is the root if the root exists
    //   otherwise x become the root (only the first node inserted can be the
    //   root)

    // pre-condition 1
    //TODO not needed anymore with reference parameter
    // if (value == nullptr) {
    //     throw std::runtime_error("TreePosVector::addNode() error: You can't "
    //                              "add a null value to the Tree");
    // }

    // check if x already exists
    // std::cout<<"prima di trova: "<<std::endl<< (*vecNode.begin())->value;
    // if((*vecNode.begin())==nullptr)
    //     std::cout<<"vettore nodo nullo\n";

    x_itr = datalib::trova(vecNode.begin(), vecNode.end(), value);

    if (x_itr != vecNode.end()) {
        std::string error = "The node" + value + "already exist in the Tree";
        throw std::runtime_error("TreePosVector::addNode() error: " + error);
    }

    // MEGLIO NON FARLO QUI, ANCORA NON SO SE DEVO LANCIARE UN ERRORE PER IL
    // PARENT O NO vedere dove farlo, perchè senza questo da segmentation fault
    // if(!root)
    // root = x_ptr;

    // TODO qui devo decide dove vado ad inserire il nodo, e lo devo inserire in
    // base alla posizione del padre

    // if (parent) {

        parent_itr = datalib::trova(vecNode.begin(), vecNode.end(), parent);

        // pre-condition 2: parent can't be different from the null_ptr
        if (parent_itr == vecNode.end()) {
            // is only for debugging
            throw std::runtime_error("TreePosVector::addNode() error: the "
                                     "parent entered doesn't exist");
        }
        try {
            T a = value;
            addChild(&parent, &a);
        } catch (std::string &error) {
            throw error;
        }
    // } 

    //TODO non serve più con addRoot
    // else // padre nullo, aggiornare radice
    // {
    //     if (root) {
    //         throw std::runtime_error("TreePosVector::addNode() error: root "
    //                                  "already exist, supply a parent ");
    //     } else {
    //         Node<T> *x_ptr = new Node<T>(*value);
    //         root = x_ptr;
    //         vecNode[1] = x_ptr;
    //         x_ptr->pos = 1;
    //     }
    // }
}

// add childrens to node x, x must exists
template <class T>
void TreePosVector<T>::addChildren(const T &value,
                                   const std::list<T> &children) {

    /* Preconditions
     * 1. the node _x must exists, and must be in the vecNode
     * 2. the nodes to be added must have enough space
     * TODO 3. the child node to be added it must not exist
    */

    typename std::vector<Node<T> *>::iterator x_itr;
    x_itr = datalib::trova(vecNode.begin(), vecNode.end(), value);

    // preconditions 1
    if (x_itr == vecNode.end()) {
        throw std::runtime_error(
            "TreePosVector::addChildren() error: value can't be null");
    }

    int pos = (*x_itr)->pos;

    // preconditions 2
    if (((*x_itr)->num_children + children.size()) > this->degree) {
        throw std::runtime_error(
            "TreePosVector::addChildren() error: max degree of the node" +
            value + " reached");
    }

    for (auto &n : children) {
        Node<T> *child2add = new Node<T>(n);

        // add childrens in vecNode in the proper positions
        int pos_childrens = (pos * this->degree) + (*x_itr)->num_children;

        vecNode[pos_childrens] = child2add;
        child2add->pos = pos_childrens;

        ++(*x_itr)->num_children;
    }
}

template <class T>
void TreePosVector<T>::addChild(const T *value, const T *child) {
    /* Preconditions
     * 1. the node value must exists, and must be in the vecNode
     * 2. the nodes to be added must have enough space
     * 3. the child node to be added it must not exist
     */

    typename std::vector<Node<T> *>::iterator x_itr;

    x_itr = datalib::trova(vecNode.begin(), vecNode.end(), *value);

    typename std::vector<Node<T> *>::iterator child_itr;
    child_itr = datalib::trova(vecNode.begin(), vecNode.end(), *child);

    // preconditions 1
    if (x_itr == vecNode.end()) {
        std::string error("error: _x can't be null pointer\n");
        throw error;
    }

    // precondition 2
    if (((*x_itr)->num_children + 1) > degree) {
        std::string error("error: max child node reached\n");
        throw error;
    }
    // pre-condition 3
    if (child_itr != vecNode.end()) {
        std::string error("the child to add, already exists in tree\n");
        throw error;
    }

    int pos = (*x_itr)->pos;
    int pos_child = (pos * degree) + (*x_itr)->num_children;

    Node<T> *child2add = new Node<T>(*child);

    vecNode[pos_child] = child2add;
    vecNode[pos_child]->pos = pos_child;

    ++(*x_itr)->num_children;
}

template <class T> void TreePosVector<T>::showStructure() const{

    std::cout << "\n\n Stampa di Tree_pos_vector: \n";

    for (auto &n : vecNode) {
        if (n) {
            std::cout << n->value << ", puntatore: " << n << "\n";
        } else if (n == nullptr)
            std::cout << "nullptr\n";
    }
    std::cout << std::endl;
}

// template <class T>
// int tree_pos_vector<T>::getNumChildren(node<T>* _x){
//     return _x->num_children;
// }

// convention of print tree
template <class T> void TreePosVector<T>::showTree() const{
    //{ padre figlio1 } { padre figlio2 } { padre2 figlio1}
    std::cout << "\nStampa TreePosVector:\n";
    // stampa del root

    std::cout << "root: " << this->root->value;

    for (auto &node : vecNode) {

        if (node != nullptr) {
            int pos = node->pos;
            if (vecNode[pos / 2] != nullptr)
                std::cout << *vecNode[pos / 2];
            // else
            //     std::cout << "//";

            if (vecNode[pos / 2] != nullptr)
                std::cout << "<--" << *vecNode[pos];
            // else
            //     std::cout << "//";

            // ciclo per la stampa di ogni ciclo del nodo
            for (int i = 0; i < this->degree; i++) {
                if (vecNode[pos * 2 + i] != nullptr)
                    std::cout << "-->" << *vecNode[pos * 2 + i];
            }
            std::cout << "\n";
        }
    }
}

template <class T>
typename std::vector<Node<T> *>::iterator
trova(typename std::vector<Node<T> *>::iterator begin,
      typename std::vector<Node<T> *>::iterator end, const T& value) {

    int i = 0;
    typename std::vector<Node<T> *>::iterator appo;
    for (appo = begin; appo != end; ++appo) {

        // if appo is nullptr, don't check equality, it is certainly different
        if (*appo == nullptr)
            continue;

        if (**appo.value == value) {
            return appo;
        }
    }
    return end;
}

#endif
