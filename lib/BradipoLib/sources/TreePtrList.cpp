#ifndef TREE_PTR_LIST_CPP
#define TREE_PTR_LIST_CPP
#pragma once
#include <stdexcept>
#include "TreePtrList.h"
// #include <stack>
// #include <queue>

using namespace datalib;

template <class T>
TreePtrList<T>::TreePtrList() : Tree<T>() {
    
    this->degree=-1;
    this->root = nullptr;
}


template <class T> TreePtrList<T>::~TreePtrList() {

    std::cout << "------Call ~TreePtrList-----\n";
    int j = 0;
    for (typename std::map<T, Node<T> *>::iterator i = nodesMap.begin();
         i != nodesMap.end(); ++i) {
        delete i->second;
        j++;
    }
}


template <class T> void TreePtrList<T>::addRoot(const T &rootValue) {
    Node<T> *root_ptr = new Node<T>(rootValue);
    this->nodesMap.insert(std::pair<T, Node<T> *>(root_ptr->value, root_ptr));
    this->root = root_ptr;
    this->numNodes++;
}

template <class T>
void TreePtrList<T>::addNode(const T &value, const T &parent) {

    if(!this->root){
        throw std::runtime_error("TreePosVector::addNode() error: root doesn't "
                                 "exist, insert root before to add other node");
    }

    Node<T> *x_ptr;

    // x_itr and parent_itr are dependent names
    typename std::map<T, Node<T> *>::iterator x_itr;
    typename std::map<T, Node<T> *>::iterator parent_itr;

    // pre-conditions:
    // 1. the node x to add must be different from nullptr
    // 2. the node parent must exists if different from nullptr
    // 3. the parent nullptr means that x is the root
    // 4. x will be the root if parent is nullptr and even the root is nullptr

    // if (parent) {
    parent_itr = nodesMap.find(parent);

    // il parent non esiste??
    if (parent_itr == nodesMap.end()) {
        throw std::runtime_error(
            "TreePtrList::addNode() error: used parent doesn't exist, you "
            "can't add a node without a parent");
        // std::string error("errore, parent non esiste");
        // throw error;
    }

    // check the degree of the parent
    if (((parent_itr->second)->node_list.size()) >= (this->degree))
        throw std::runtime_error("TreePtrList::addNode() error: cannot add "
                                 "another node, max degree reached");
    // }

    // check if x already exists, if not exist add to map
    x_itr = nodesMap.find(value);
    if (x_itr == nodesMap.end()) {
        x_ptr = new Node<T>(value);
        nodesMap.insert(std::pair<T, Node<T> *>(x_ptr->value, x_ptr));
    } else {
        throw std::runtime_error("TreePtrList::addNode() error: the node is already inserted");
    }

    if (!this->root)
        this->root = x_ptr;

    // check if parent exist
    if (parent_itr == nodesMap.end()) {
        throw std::runtime_error("TreePtrList::addNode() error: the parent "
                                 "entered doesn't exist");
    }

    // questo porta a dei cicli che non sono permessi nell'albero, devo fare
    // un controllo
    x_ptr->parent = (parent_itr->second);

    // update children of the parent
    (x_ptr->parent)->addChildren({x_ptr});

    this->numNodes++;
}

template <class T>
void TreePtrList<T>::addChildren(const T &value, const std::list<T> &children) {

    try {
        for (auto &child : children)
            addNode(child, value);
    } catch (std::string error) {
        std::cout << error << "\n";
    }
}


// return by referece the parent node of _x
//TODO controllare se restitiusco il riferimento giusto e non un  valore
template <class T>
T TreePtrList<T>::getParent(const T &childValue) {
    return (nodesMap.find(childValue))->second->parent->value;
}

// append the children node to the list
template <class T>
std::list<T> TreePtrList<T>::getChildren(const T& parentValue) const {

    // find the itr of the target
    typename std::map<T, Node<T> *>::const_iterator x_itr;
    x_itr = nodesMap.find(parentValue);

    // manage a possible error
    if (x_itr == nodesMap.end()) {
        std::string error(
            "TreePtrList::getChildren il nodo inserito non esiste");
        throw error;
    }

    std::list<T> children;

    // copy the children node into the list
    for (auto &nodo : x_itr->second->node_list) {
        children.push_back((nodo->value));
    }
    return children;
}

template<class T>
T TreePtrList<T>::getValue(const T& nodeValue) const{

    typename std::map<T, Node<T> *>::const_iterator valueItr;
    valueItr = nodesMap.find(nodeValue);
    
    if(valueItr != nodesMap.end()){
        return ((*valueItr).second)->value;
    }else{
        throw std::runtime_error("TreePtrList<T>::getValue : error the node with this value doesn't exists");
    }

}

template<class T>
void TreePtrList<T>::setValue(const T &oldValue, const T &newValue){

    //allocate the new Node 
    Node<T>* newNode = new Node(newValue);
    
    //trova il nodo src e aggiorno il valore, assegnando anche una nuova 
	//chiave alla mappa
	typename std::map<T,Node<T>*>::iterator oldItr;
	oldItr = nodesMap.find(oldValue);
	Node<T>* oldNode = (*oldItr).second;
    
    if(oldItr == nodesMap.end()){
        delete newNode;
        throw std::runtime_error("TreePtrList<T>::SetValue : error the oldValue node to change doesn't exists");
    }

    for(auto& n: nodesMap){
        for(auto& child: (n.second)->node_list){
            if(child->value == oldValue){
                child = newNode;
            }                  
        }
	}
    
	newNode->node_list = oldNode->node_list;

    nodesMap.erase(oldValue);
    nodesMap.insert(std::pair<T,Node<T>*>(newValue,newNode));
    delete oldNode;
    return;

}



template <class T>
void TreePtrList<T>::updateParent(const T &child, const T &newParent) {

    // preconditions: can't update the roots

    // devo aggiornare parent, togliendo il figlio
    // devo aggiornare new_parent aggiungendo il figlio
    // devo aggiornare il puntatore interno al parent di _x
    Node<T> *x = getNode(child);
    Node<T> *parent = x->parent;
    Node<T> *new_parent = getNode(newParent);

    parent->node_list.remove(x);
    new_parent->addChildren({x});
    x->parent = new_parent;
}


// private function
template <class T>
std::list<Node<T> *> &TreePtrList<T>::getNodeList(Node<T> *value) {

    typename std::map<T, Node<T> *>::iterator x_itr;
    x_itr = nodesMap.find(value->value);
    if (x_itr != nodesMap.end()) {
        return (x_itr->second)->node_list;
    }

    std::string error("Error TreePtrList::getNodeList");
    throw error;
};


template <class T> Node<T> *TreePtrList<T>::getNode(const T value) {

    for (auto &n : nodesMap) {
        if ((n.second)->value == value)
            return n.second;
    }
    std::string error("non esiste il nodo che cerchi\n");
    throw error;
}

template <class T>
std::list<Edge<T>>& TreePtrList<T>::getAllEdges(std::list<Edge<T>>& edges) const{

    edges.clear(); 
    
    for(auto& n: nodesMap){
        if (!n.second->node_list.empty()) {
            for (auto &child : n.second->node_list) {
                Edge<T> e(&n.second->value,&child->value);
                edges.push_back(e);
            }
        }
    }
    return edges;
}




#endif
