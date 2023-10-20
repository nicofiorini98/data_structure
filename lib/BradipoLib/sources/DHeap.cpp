#ifndef DHEAP_CPP
#define DHEAP_CPP
#pragma once
#include "Node.h"
#include <cmath>
#include <vector>

#include "DHeap.h"
#include "TreePosVector.h"
#include <stdexcept>

using namespace slothLib;

#define VEC (this->treePosVector)->vecNode
#define TREE (this->treePosVector)
    
template <class K, class T>
DHeap<K, T>::DHeap(int degree, int size, bool isMin,
                   const std::vector<std::pair<K,T>> &values) {

    this->degree = degree;
    this->isMin = isMin;

    int height = (log(size) / log(this->degree)) + 1;

    this->treePosVector = new TreePosVector<std::pair<K,T>>(this->degree, height);

    /*
    Costruzione di un heap in tempo O(n):
    1. Creiamo un albero di taglia e dimensioe appropriata in cui mettiamo gl
       oggetti dell'array
    */

    if (!values.empty()) {
        this->insertFromArray(values);
    }
}

template <class K, class T>
void DHeap<K, T>::insertFromArray(const std::vector<std::pair<K,T>> &values) {

    (this->treePosVector)->addValuesFromVector(values);

    heapify(1);
}

template <class K, class T> void DHeap<K, T>::heapify(int posNode) {

    // recursion function
    if (posNode >= (this->treePosVector)->vecNode.size())
        return;

    bool isLeaf = this->isLeaf((this->treePosVector)->vecNode[posNode]->value);
    if (isLeaf) {
        return;
    }

    // for each child of vecNode[posNode]
    // call heapify with the child positions
    for (int i = 0; i < degree; i++) {
        if ((this->treePosVector)->vecNode[(posNode * 2) + i]) {
            this->heapify((posNode * 2) + i);
        }
    }
    fixHeap(posNode);
}

template <class K, class T>
void DHeap<K, T>::fixHeap(int posNode) {

    std::pair<K,T> nodeValue = this->treePosVector->vecNode[posNode]->value;

    if (this->isLeaf(nodeValue)) {
        return;
    } else {

        int posMax = this->getChildPos(posNode);

        std::pair<K,T> childMaxValue = this->treePosVector->vecNode[posMax]->value;

        // if node is smaller than the maxChild, swap the positions
        if (!this->isMin && nodeValue.first < childMaxValue.first) {
            (this->treePosVector)->swapPositionValue(posNode, posMax);
        } else if (this->isMin && nodeValue.first > childMaxValue.first) {
            (this->treePosVector)->swapPositionValue(posNode, posMax);
        }

        this->fixHeap(posMax);
    }
}

template <class K,class T>
std::pair<K,T> DHeap<K, T>::getFirstValue() {
    if (!this->isEmpty()) {
        return VEC[1]->value;
    } else {
        throw std::runtime_error("DHeap<K,T>::getMaxValue() error: the "
                                 "instance is empty, can't get max value");
    }
}

template <class K, class T>
std::pair<K,T> DHeap<K, T>::popValue() {
    if (!this->isEmpty()) {
        std::pair<K,T> value = this->getFirstValue();
        this->deleteByKey(value.first);
        return value;
    } else {
        throw std::runtime_error("DHeap::popMaxValue() error: the instance is "
                                 "empty, can't return the max value");
    }
}


template <class K, class T>
void DHeap<K, T>::deleteByKey(const K &keyValue) {
    //get the position to delete
    int pos2Delete = this->findByKey(keyValue);

    this->deleteByPos(pos2Delete);
}

template <class K, class T>
void DHeap<K, T>::deleteByValue(const T &value) {
    
    //get the position to delete
    int pos2Delete = this->findByValue(value);

    this->deleteByPos(pos2Delete);
}


template <class K,class T>
void DHeap<K, T>::deleteByPos(int pos2Delete){

    if (pos2Delete != -1) {

        // get the positions to swap
        int posLeaf = this->getLeaf();

        if (pos2Delete == posLeaf) {
            delete VEC[posLeaf];
            VEC[posLeaf] = nullptr;
            return;
        }

        TREE->swapPositionValue(posLeaf, pos2Delete);

        // delete node, and assign the nullptr to the position deleted
        delete VEC[posLeaf];
        VEC[posLeaf] = nullptr;

        // get the parent of the node if exist
        int posParent = 1;
        if (pos2Delete > 1) {
            posParent = TREE->getParentPos(pos2Delete);
        }

        // if the parent is bigger, try to push down the node,
        // otherwise push up the node
        if (!this->isMin) {
            if (VEC[posParent]->value.first > VEC[pos2Delete]->value.first || posParent == 1)
                moveLow(pos2Delete);
            else
                moveHigh(pos2Delete);
        } else {
            if (VEC[posParent]->value.first < VEC[pos2Delete]->value.first || posParent == 1)
                moveLow(pos2Delete);
            else
                moveHigh(pos2Delete);
        }
    } else {
        throw std::runtime_error(
            "DHeap::deleteValue error: the value to delete doesn't exist");
    }
}

template <class K,class T>
bool DHeap<K, T>::isEmpty() {
    
    //return true if the root exists
    // else false
    if (VEC[1])
        return false;
    else
        return true;
}

template <class K, class T>
int DHeap<K, T>::getLeaf() {

    Node<std::pair<K,T>> *leaf;

    for (auto &value : VEC) {
        if (value)
            leaf = value;
    }

    return leaf->pos;
}

template <class K, class T>
void DHeap<K, T>::insert(const std::pair<K,T>& value) {
    int lastLeaf = this->insertToLeaf(value);

    moveHigh(lastLeaf);
}

template <class K, class T>
void DHeap<K, T>::changeValue(const K& key, const T& newValue) {

    int posKey = this->findByKey(key);

    if (posKey != -1) {
        
        (VEC[posKey]->value).second = newValue;

    } else {
        throw std::runtime_error(
            "DHeap::changeValue error: the key to change the value doesn't exist");
    }
}


template <class K, class T>
void DHeap<K,T>::changeKey(const K& newKey, const T& element){

    int posValue = this->findByValue(element);
    
    VEC[posValue]->value.first = newKey;
    
    if (posValue != -1) {

        // get the parent of the node if exist
        int posParent = 1;
        if (posValue > 1) {
            posParent = TREE->getParentPos(posValue);
        }

        // if the parent is bigger, try to push down the node,
        // otherwise push up the node
        if (!this->isMin) {
            if ((VEC[posParent]->value).first > (VEC[posValue]->value).first)
                moveLow(posValue);
            else
                moveHigh(posValue);

        } else {
            if (VEC[posParent]->value > VEC[posValue]->value)
                moveHigh(posValue);
            else
                moveLow(posValue);
        }
    } else {
        throw std::runtime_error(
            "DHeap::changeKey error: the value for changing the key doesn't exist");
    }
    
    
}

template <class K, class T>
int DHeap<K, T>::insertToLeaf(const std::pair<K,T>& value) {

    if (!VEC[1]) {
        TREE->addRoot(value);
        return 1;
    } else {
        int lastLeaf = getLeaf();

        Node<std::pair<K,T>> *leaf = new Node<std::pair<K,T>>(value);
        leaf->pos = lastLeaf + 1;
        VEC[lastLeaf + 1] = leaf;
        return (lastLeaf + 1);
    }
}

template<class K, class T>
K DHeap<K, T>::getKeyByValue(const T& value){
    int posValue = this->findByValue(value);
    
    if(posValue != -1){
        return VEC[posValue]->value.first;
    }else{
        throw std::runtime_error("DHeap<K, T>::getKeyByValue error: the value to search doesn't exists");
    }

}

template <class K, class T>
void DHeap<K, T>::moveHigh(int posNode) {
    /*
    Pre-conditions
    1.  1 =< posNode <= vecNode.size()
     */

    if (posNode < 1 && posNode < VEC.size()) {
        throw std::runtime_error(
            "the position is not permitted in the structure");
    }

    if (posNode == 1) {
        return;
    }

    std::pair<K,T> nodeValue = VEC[posNode]->value;

    std::pair<K,T> parentValue = VEC[TREE->getParentPos(posNode)]->value;

    if (!this->isMin) {
        while (posNode > 1 && nodeValue.first > parentValue.first) {

            // get parent positions and swap the values
            int posParent = TREE->getParentPos(posNode);
            TREE->swapPositionValue(posNode, posParent);
            posNode = posParent;

            // update parent value if the node has parent
            if (posNode > 1) {
                parentValue = VEC[TREE->getParentPos(posNode)]->value;
            }
        }

    } else {
        while (posNode > 1 && nodeValue.first < parentValue.first) {

            // get parent positions and swap the values
            int posParent = TREE->getParentPos(posNode);
            TREE->swapPositionValue(posNode, posParent);
            posNode = posParent;

            // update parent value if the node has parent
            if (posNode > 1) {
                parentValue = VEC[TREE->getParentPos(posNode)]->value;
            }
        }
    }
    return;
}

template <class K, class T>
void DHeap<K, T>::moveLow(int posNode) {

    /*
    sia u il figlio di v con il max valore,se esiste
    if(v non ha figli o chiave(v)>=chiave(u)) break
    swapPositions()
    */

    int posChild;
    std::pair<K,T> value, childValue;

    while (true) {

        // getting the values from the starting two positions
        value = VEC[posNode]->value;

        if (VEC[posNode] && this->isLeaf(value)) {
            return;
        }

        posChild = this->getChildPos(posNode);

        childValue = VEC[posChild]->value;

        if (!this->isMin) {
            if (value.first > childValue.first)
                return;
        } else {
            if (value.first < childValue.first)
                return;
        }

        TREE->swapPositionValue(posNode, posChild);

        // update the positions for the next cycle
        posNode = posChild;
    }
}

template <class K, class T>
bool DHeap<K, T>::isLeaf(const std::pair<K,T>& value) {

    // return tru if the node doesn't have child
    int numChildren = (this->treePosVector)->getNumChildren(value);

    if (numChildren == 0)
        return true;

    return false;
}


template <class K, class T>
int DHeap<K,T>::getChildPos(int posNode){

    if (VEC[posNode]) {

        int priorPos = (posNode * degree) ;

        for(int i = 0; i < degree ; i++){
            int childPos = (posNode * degree) + i ;
            if(childPos < VEC.size() && VEC[(childPos)]){

                std::pair<K,T> maxValue = VEC[priorPos]->value;
                std::pair<K,T> value = VEC[childPos]->value;

                if(!this->isMin && value.first > maxValue.first){
                    priorPos = childPos;
                }else if(this->isMin && value.first < maxValue.first){
                    priorPos = childPos;
                }
            }
        }
        return priorPos;
    } else {
        throw std::runtime_error(
            "TreePosVector::getChildren(const T& parentValue) error: node doesn't exist in the Tree");
    } 
}



template <class K,class T>
int DHeap<K,T>::findByKey(const K& keyValue){

    for(auto& node: VEC){
        if(node && (node->value).first == keyValue){
            return node->pos;
        }
    } 
    return -1;
}

template <class K,class T>
int DHeap<K,T>::findByValue(const T& value){


    for(auto& node: VEC){
        if(node && (node->value).second == value){
            return node->pos;
        }
    } 
    return -1;
}

template <class K, class T>
DHeap<K, T>::~DHeap() {

    delete treePosVector;
    std::cout << "~Dheap() called\n";
}

#endif /* DHEAP_CPP */