
#ifndef TREE_POS_VECTOR_CPP
#define TREE_POS_VECTOR_CPP
#include "Node.h"
#include <stdexcept>
#include "TreePosVector.h"
#include "Tree.h"
#include <math.h>

using namespace slothLib;

// I need to know the grade of the tree and the
// num_nodes for instatiate the tree
template <class T>
TreePosVector<T>::TreePosVector(int maxDegree, int height) : Tree<T>() {
    // initialization parameter
    this->degree = maxDegree;
    this->root = nullptr;
    this->height = height;

    // computation of maxNumNodes allowed from the data_structure
    maxNumNodes = 0;
    for (int i = 0; i <= height; i++) {
        maxNumNodes += pow(this->degree, i);
    }

    // initialization vector (nullptr)
    vecNode.resize(this->maxNumNodes);

    // std::cout<<"size of the vector: "<<vecNode.size()<<"\n";
}


template <class T>
TreePosVector<T>::~TreePosVector() {
    for(auto& n : vecNode){
        delete n;
    }
}

// template <class T>
// int TreePosVector<T>::getDegree(const T &value) const {
//     typename std::vector<Node<T> *>::iterator x_itr;
//     x_itr = slothLib::trova(vecNode.begin(), vecNode.end(), value);
//     // std::cout<<"TreePosVector::getDegree() --> "<<(*x_itr)->value<<"\n";
//     if (x_itr != vecNode.end()) {
//         return (*x_itr)->num_children;
//     } else {
//         throw std::runtime_error(
//             "TreePosVector::getDegree(const T& value) error: node non presente nell'albero");
//     }
// };



template<class T>
int TreePosVector<T>::getNumChildren(const T& value){

    typename std::vector<Node<T> *>::iterator x_itr;
    x_itr = slothLib::trova(vecNode.begin(), vecNode.end(), value);

    int count_children = 0;

    if (x_itr != vecNode.end()) {
        int pos = (*x_itr)->pos;
        for(int i=0; i<this->degree ; i++){
            if(vecNode[(pos * (this->degree)) +i ] && (pos*(this->degree)+i) < vecNode.size()){
                count_children++;
            }
        }
        return count_children;
    } else {
        throw std::runtime_error(
            "TreePosVector::getNumChildren(const T& value) error: nodo non presente nell'albero");
    }
}

template<class T>
T TreePosVector<T>::getParent(const T &childValue) {

    typename std::vector<Node<T> *>::iterator x_itr;
    x_itr = slothLib::trova(vecNode.begin(), vecNode.end(), childValue);


    //il padre è vecNode[ parteInteraInferiore(index/degree)]
    if (x_itr != vecNode.end()) {
        int parte_intera_inferiore = (int)floor(((*x_itr)->pos)/this->degree);
        return vecNode[parte_intera_inferiore]->value;
    } else 
        throw std::runtime_error("TreePosVector::getParent(const T& childValue) error: node doesn't exists in the tree");

}

template<class T>
std::list<T> TreePosVector<T>::getChildren(const T& parentValue) const {

    typename std::vector<Node<T> *>::const_iterator parent_itr;
    parent_itr = slothLib::trova(vecNode.begin(), vecNode.end(), parentValue);

    std::list<T> children;
    if (parent_itr != vecNode.end()) {
        int pos = (*parent_itr)->pos;
        for(int i = 0; i < (this->degree) ; i++){
            int childPos = (pos * (this->degree)) + i ;
            
            if(childPos < vecNode.size() && vecNode[(childPos)]){

                T value = vecNode[childPos]->value;

                children.push_back(vecNode[childPos]->value);
            }
        }
        return children;
    } else {
        throw std::runtime_error(
            "TreePosVector::getChildren(const T& parentValue) error: node doesn't exist in the Tree");
    }

}

//add the values directly in the vector O(n)
template <class T>
void TreePosVector<T>::addValuesFromVector(const std::vector<T>& values){

    int i=0;

	for(auto& value: values){
        
		Node<T>* nodeValue = new Node<T>(value);
        nodeValue->pos = i+1;
		vecNode[i+1] = nodeValue;
		i++;

	}
}

template<class T>
T TreePosVector<T>::getValue(const T& nodeValue) const{

    typename std::vector<Node<T> *>::const_iterator x_itr;
    x_itr = slothLib::trova(vecNode.begin(), vecNode.end(), nodeValue);
    
    if(x_itr != vecNode.end()){
        return (*x_itr)->value;
    }else{
        throw std::runtime_error("TreePosVector<T>::getValue : error the node with this value doesn't exists");
    }

}

template<class T>
void TreePosVector<T>::setValue(const T &oldValue, const T &newValue){

    typename std::vector<Node<T> *>::iterator oldItr;
    oldItr = slothLib::trova(vecNode.begin(), vecNode.end(), oldValue);
    
    if(oldItr != vecNode.end()){
        (*oldItr)->value = newValue;
        return;
    }else{
        throw std::runtime_error("TreePosVector<T>::setValue : error the oldValue node to change doesn't exists"); }

}

template<class T>
int TreePosVector<T>::getParentPos(int posChild){
    if(posChild == 1){
        throw std::runtime_error("TreePosVector<T>::getParentPos : error the node is the Root");
    }

    int parte_intera_inferiore = (int)floor(((posChild)/this->degree)); 
    return parte_intera_inferiore;

}


template<class T>
void TreePosVector<T>::swapPositionValue(int posNode1, int posNode2){
    /* 
    Pre-conditions 
    1. Le due posizioni devono stare nel vettore
     */

    Node<T>* node1 = this->vecNode[posNode1];
    //cambio valore e aggiornamento posizione
    this->vecNode[posNode1] = this->vecNode[posNode2];
    this->vecNode[posNode1]->pos = posNode1;

    this->vecNode[posNode2] = node1;
    this->vecNode[posNode2]->pos = posNode2;
    return;
}

template <class T>
void TreePosVector<T>::addRoot(const T &rootValue){
    Node<T> *x_ptr = new Node<T>(rootValue);
    this->root = x_ptr;
    vecNode[1] = x_ptr;
    x_ptr->pos = 1;
}



template <class T>
void TreePosVector<T>::addNode(const T &value, const T &parent) {

    
    if(!this->root){
        throw std::runtime_error("TreePosVector::addNode() error: root doesn't "
                                 "exist, insert root before to add other node");
    }

    // local iterator, typename because are nested dependent names
    typename std::vector<Node<T> *>::iterator x_itr;
    typename std::vector<Node<T> *>::iterator parent_itr;

    x_itr = slothLib::trova(vecNode.begin(), vecNode.end(), value);

    if (x_itr != vecNode.end()) {
        // std::string error = "The node" + value + "already exist in the Tree";
        throw std::runtime_error("TreePosVector::addNode() error: The node already exist in the Tree");
    }

    parent_itr = slothLib::trova(vecNode.begin(), vecNode.end(), parent);

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
}

template<class T>
bool TreePosVector<T>::isLeaf(const T& value){
    // ritorna true se il nodo non ha figli
    int numChildren = this->getNumChildren(value);

    if (numChildren == 0)
        return true;

    return false;
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
    x_itr = slothLib::trova(vecNode.begin(), vecNode.end(), value);

    // preconditions 1
    if (x_itr == vecNode.end()) {
        throw std::runtime_error(
            "TreePosVector::addChildren() error: value can't be null");
    }

    int pos = (*x_itr)->pos;

    // preconditions 2
    if (((*x_itr)->num_children + children.size()) > this->degree)
            throw std::runtime_error("TreePosVector::addChildren() error: max degree of the node reached");

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

    x_itr = slothLib::trova(vecNode.begin(), vecNode.end(), *value);

    typename std::vector<Node<T> *>::iterator child_itr;
    child_itr = slothLib::trova(vecNode.begin(), vecNode.end(), *child);

    // preconditions 1
    if (x_itr == vecNode.end()) {
        throw std::runtime_error("TreePosVector::addChild() error: can't add a null_ptr");
    }

    // precondition 2
    if (((*x_itr)->num_children + 1) > (this->degree)) {
        throw std::runtime_error("TreePosVector::addChild() error: max child nodes reached");
    }
    
    // pre-condition 3
    if (child_itr != vecNode.end()) {
        throw std::runtime_error("TreePosVector::addChild() error: the child to add already exist");
    }

    int pos = (*x_itr)->pos;
    int pos_child = (pos * (this->degree)) + (*x_itr)->num_children;

    Node<T> *child2add = new Node<T>(*child);

    vecNode[pos_child] = child2add;
    vecNode[pos_child]->pos = pos_child;

    ++(*x_itr)->num_children;
}


template<class T>
std::list<Edge<T>>& TreePosVector<T>::getAllEdges(std::list<Edge<T>>& edges) const{

    edges.clear();

    for (auto &node : vecNode) {
        if (node != nullptr) {
            int pos = node->pos;
            for (int i = 0; i < (this->degree); i++) {
                if (vecNode[pos * 2 + i] != nullptr){
                    Edge<T> e(&(vecNode[pos]->value),&(vecNode[pos*2+i]->value));
                    edges.push_back(e);
                }
            }
        }
    }
    return edges;
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
