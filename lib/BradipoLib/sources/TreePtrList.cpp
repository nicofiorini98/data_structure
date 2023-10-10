#ifndef TREE_PTR_LIST_TPP
#define TREE_PTR_LIST_TPP
#pragma once
#include "TreePtrList.h"
// #include <stack>
// #include <queue>

using namespace datalib;

template <class T> TreePtrList<T>::TreePtrList() : Tree<T>() {
    
    degree=-1;
    root = nullptr;
}


//TODO debug and see if is there a way to deallocate the map
//in teoria non c'è bisogno di deallocare la mappa, già dovrebbe pensarci
//la struttura della mappa
template <class T> TreePtrList<T>::~TreePtrList() {

    std::cout << "------Call ~TreePtrList-----\n";
    int j = 0;
    for (typename std::map<T, Node<T> *>::iterator i = nodes_map.begin();
         i != nodes_map.end(); ++i) {
        delete i->second;
        //nodes_map.erase(i); //this bring to segmentation fault
        j++;
    }
}


template <class T> void TreePtrList<T>::addRoot(const T &rootValue) {
    Node<T> *root_ptr = new Node<T>(rootValue);
    this->nodes_map.insert(std::pair<T, Node<T> *>(root_ptr->value, root_ptr));
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
    parent_itr = nodes_map.find(parent);

    // il parent non esiste??
    if (parent_itr == nodes_map.end()) {
        throw std::runtime_error(
            "TreePtrList::addNode() error: used parent doesn't exist, you "
            "can't add a node without a parent");
        // std::string error("errore, parent non esiste");
        // throw error;
    }

    // check the degree of the parent
    if (((parent_itr->second)->node_list.size()) >= degree)
        throw std::runtime_error("TreePtrList::addNode() error: cannot add "
                                 "another node, max degree reached");
    // }

    // check if x already exists, if not exist add to map
    x_itr = nodes_map.find(value);
    if (x_itr == nodes_map.end()) {
        x_ptr = new Node<T>(value);
        nodes_map.insert(std::pair<T, Node<T> *>(x_ptr->value, x_ptr));
    } else {
        throw std::runtime_error("TreePtrList::addNode() error: the node is already inserted");
    }

    if (!root)
        root = x_ptr;

    // check if parent exist
    if (parent_itr == nodes_map.end()) {
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

// return the number of sons for the node x
// O(log n)
template <class T> int TreePtrList<T>::getDegree(const T &value) {
    return nodes_map.find(value)->second->node_list.size();
}

// return by referece the parent node of _x
//TODO controllare se restitiusco il riferimento giusto e non un  valore
template <class T>
T TreePtrList<T>::getParent(const T &childValue) {
    return (nodes_map.find(childValue))->second->parent->value;
}

// append the children node to the list
template <class T>
std::list<T> TreePtrList<T>::getChildren(const T &parentValue) {

    // find the itr of the target
    typename std::map<T, Node<T> *>::iterator x_itr;
    x_itr = nodes_map.find(parentValue);

    // manage a possible error
    if (x_itr == nodes_map.end()) {
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

template <class T> void TreePtrList<T>::depthSearch(const T &startValue) {

    std::cout << "Inizio ricerca in profondita partendo da: " << startValue
              << "\n";

    // initialize for stack
    std::stack<Node<T> *> stack;
    typename std::map<T, Node<T> *>::iterator nodes_map_itr;

    /// pre-conditions: if the node isn't in the tree, return error
    nodes_map_itr = nodes_map.find(startValue);

    if (nodes_map_itr == nodes_map.end()) {
        throw " the node entered for start the visit doesn't exists\n";
    }

    stack.push((*nodes_map_itr).second); // 2 s.push(root)
    while (!stack.empty()) {
        Node<T> *u = stack.top();
        stack.pop(); // pop don't return the value
        std::cout << u->value << "-->";

        if (true) {
            // visit u
            std::list<T> lista_childrens;
            lista_childrens = this->getChildren(u->value);

            typename std::list<T*>::iterator itr;
            // se la lista è vuota non devo aggiungere niente allo stack
            if (lista_childrens.empty())
                u = nullptr;
            else {

                for (auto child_itr = (lista_childrens.rbegin());
                     child_itr != lista_childrens.rend(); ++child_itr) {
                    Node<T> *appo = new Node<T>((*child_itr));
                    stack.push(appo);
                }
            }
        }
    }
    std::cout << std::endl;
}

template <class T> void TreePtrList<T>::breadthSearch(const T &startValue) {

    // initialize for stack
    std::queue<Node<T> *> queue;
    typename std::map<T, Node<T> *>::iterator nodes_map_itr;

    /// pre-conditions: if the node isn't in the tree, return error
    nodes_map_itr = nodes_map.find(startValue);

    if (nodes_map_itr == nodes_map.end()) {
        throw " the node entered for start the visit doesn't exists\n";
    }

    std::cout << "inizio visita in ampiezza\n";

    queue.push((*nodes_map_itr).second); // 2 s.push(root)
    while (!queue.empty()) {
        Node<T> *u = queue.front();
        queue.pop(); // pop don't return the value
        // std::cout << u->value << "-->";
        std::cout << u->value << "-->";

        if (true) {
            // visit u
            std::list<T> lista_childrens;
            lista_childrens = this->getChildren(u->value);

            typename std::list<T>::iterator itr;
            // se la lista è vuota non devo aggiungere niente allo stack
            if (lista_childrens.empty())
                u = nullptr;
            else {

                for (auto child_itr = (lista_childrens.begin());
                     child_itr != lista_childrens.end(); ++child_itr) {
                    Node<T> *appo = new Node<T>(*child_itr);
                    queue.push(appo);
                }
            }
        }
    }
}

template <class T> void TreePtrList<T>::showTree() {
    std::cout << std::endl;
    for (auto &n : nodes_map) {
        if (n.second->parent != nullptr) {
            std::cout << ((n.second)->parent)->value << "<---";
        } else
            std::cout << "null"
                      << "<---";

        std::cout << n.first << " --->  ";
        // print the sons if the list isn't empty
        if (!n.second->node_list.empty()) {
            for (auto &child : n.second->node_list) {
                std::cout << child->value << " ";
            }
        } else
            std::cout << "null";
        std::cout << std::endl;
    }
}

template <class T> void TreePtrList<T>::showStructure() {

    std::cout<<"TreePtrList relations: \n";
    for (auto &n : nodes_map) {
        if (n.second->parent)
            std::cout << *((n.second)->parent) << "<--";
        else
            std::cout << "// <--";

        std::cout << *(n.second) << "--> ";

        for (auto &child : n.second->node_list)
            std::cout << *child << " ";
        std::cout << "\n";
    }
}

template <class T> void TreePtrList<T>::showTreePtr() {
    std::cout << std::endl;
    for (auto &n : nodes_map) {
        if (n.second->parent != nullptr) {
            std::cout << ((n.second)->parent) << "<---";
        } else
            std::cout << "null"
                      << "<---";

        std::cout << (n.second) << " --->  ";
        // print the sons if the list isn't empty
        for (auto &child : n.second->node_list)
            std::cout << child << " ";

        std::cout << std::endl;
    }
}

// private function
template <class T>
std::list<Node<T> *> &TreePtrList<T>::getNodeList(Node<T> *value) {

    typename std::map<T, Node<T> *>::iterator x_itr;
    x_itr = nodes_map.find(value->value);
    if (x_itr != nodes_map.end()) {
        return (x_itr->second)->node_list;
    }

    std::string error("Error TreePtrList::getNodeList");
    throw error;
};

template <class T> void TreePtrList<T>::showTree2() {}

template <class T> Node<T> *TreePtrList<T>::getNode(const T value) {

    for (auto &n : nodes_map) {
        if ((n.second)->value == value)
            return n.second;
    }
    std::string error("non esiste il nodo che cerchi\n");
    throw error;
}

template <class T>
std::list<Edge<T>>& TreePtrList<T>::getAllEdges(std::list<Edge<T>>& edges){

    edges.clear(); 
    
    for(auto& n: nodes_map){
        if (!n.second->node_list.empty()) {
            for (auto &child : n.second->node_list) {
                Edge<T> e(&n.second->value,&child->value);
                edges.push_back(e);
            }
        }
    }
    return edges;
}


template <class T>
std::ostream& TreePtrList<T>::outputDotFile(std::ostream& dotFile){

    // Write the DOT file content
    dotFile << "digraph G {" << std::endl;
    
    for(auto& n: nodes_map){
        if (!n.second->node_list.empty()) {
            for (auto &child : n.second->node_list) {
                dotFile<<n.first<<" -> ";
                dotFile<< child->value << "\n";
            }
        }
    }

    dotFile << "}" << std::endl;

    std::cout << "DOT file generated as graph.dot" << std::endl;
    
    return dotFile;
}

#endif
