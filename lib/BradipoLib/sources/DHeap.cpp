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

// Code optimization macros
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

    // Check if the given position exceeds the size of the heap.
    if (posNode >= (this->treePosVector)->vecNode.size())
        return;

    // Determine if the current node is a leaf node.
    bool isLeaf = this->isLeaf((this->treePosVector)->vecNode[posNode]->value);
    if (isLeaf) {
        return;
    }

    // Iterate through the children of the current node.
    // Call heapify recursively for each child's position.
    for (int i = 0; i < degree; i++) {
        if ((this->treePosVector)->vecNode[(posNode * 2) + i]) {
            this->heapify((posNode * 2) + i);
        }
    }
    
    // Perform a heap-fixing operation on the current node.
    fixHeap(posNode);
}

template <class K, class T>
void DHeap<K, T>::fixHeap(int posNode) {

    // Get the value of the node at posNode
    std::pair<K,T> nodeValue = VEC[posNode]->value;

    // Check if the node is a leaf node; if so, the heap is already fixed
    if (this->isLeaf(nodeValue)) {
        return;
    } else {

        // Find the position of the child with the maximum (or minimum) value
        int posMax = this->getChildPos(posNode);

        // Get the value of the child with the maximum (or minimum) value
        std::pair<K,T> childMaxValue = this->treePosVector->vecNode[posMax]->value;

        // Check if the node is smaller than the maxChild, and swap their positions if needed
        if (!this->isMin && nodeValue.first < childMaxValue.first) {
            (this->treePosVector)->swapPositionValue(posNode, posMax);
        } else if (this->isMin && nodeValue.first > childMaxValue.first) {
            (this->treePosVector)->swapPositionValue(posNode, posMax);
        }

        // Recursively fix the heap starting from the child node
        this->fixHeap(posMax);
    }
}

template <class K,class T>
std::pair<K,T> DHeap<K, T>::getFirstValue() {
    if (!this->isEmpty()) {
        // Return the value of the root node
        return VEC[1]->value;
    } else {
        // If the heap is empty, throw an exception with an error message
        throw std::runtime_error("DHeap<K,T>::getMaxValue() error: the "
                                 "instance is empty, can't get max value");
    }
}

template <class K, class T>
std::pair<K,T> DHeap<K, T>::popValue() {
    if (!this->isEmpty()) {
        // Get the maximum (or minimum) value from the heap
        std::pair<K,T> value = this->getFirstValue();
        // Delete the value by its key, which also updates the heap
        this->deleteByKey(value.first);
        return value;
    } else {
        // If the heap is empty, throw an exception with an error message
        throw std::runtime_error("DHeap::popMaxValue() error: the instance is "
                                 "empty, can't return the max value");
    }
}


template <class K, class T>
void DHeap<K, T>::deleteByKey(const K &keyValue) {
    // Find the position of the element with the specified key
    int pos2Delete = this->findByKey(keyValue);

    // Delete the element by its position, which updates the heap structure
    this->deleteByPos(pos2Delete);
}

template <class K, class T>
void DHeap<K, T>::deleteByValue(const T &value) {
    
    // Find the position of the element with the specified key
    int pos2Delete = this->findByValue(value);

    // Delete the element by its position, which updates the heap structure
    this->deleteByPos(pos2Delete);
}

template <class K, class T> void DHeap<K, T>::deleteByPos(int pos2Delete) {

    if (pos2Delete != -1) {

        // Get the position of a leaf nodep
        int posLeaf = this->getLeaf();

        // If the element to delete is a leaf node, delete it and set the
        // position to nullptr
        if (pos2Delete == posLeaf) {
            delete VEC[posLeaf];
            VEC[posLeaf] = nullptr;
            return;
        }

        // Swap the positions of the leaf node and the element to be deleted
        TREE->swapPositionValue(posLeaf, pos2Delete);

        // Delete the leaf node and set its position to nullptr
        delete VEC[posLeaf];
        VEC[posLeaf] = nullptr;

        // Determine the parent of the node, if it exists
        int posParent = 1;
        if (pos2Delete > 1) {
            posParent = TREE->getParentPos(pos2Delete);
        }

        // If the parent is bigger or it's the root, try to push down the node;
        // otherwise, push up the node
        if (!this->isMin) {
            if (VEC[posParent]->value.first > VEC[pos2Delete]->value.first ||
                posParent == 1)
                moveLow(pos2Delete);
            else
                moveHigh(pos2Delete);
        } else {
            if (VEC[posParent]->value.first < VEC[pos2Delete]->value.first ||
                posParent == 1)
                moveLow(pos2Delete);
            else
                moveHigh(pos2Delete);
        }
    } else {
        // If the specified position is invalid, throw an exception with an
        // error message
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

    // Initialize a pointer to a leaf node
    Node<std::pair<K,T>> *leaf;

    // Iterate through the heap's elements to find the last non-null element
    for (auto &value : VEC) {
        if (value)
            leaf = value;
    }

    // Return the position of the leaf node
    return leaf->pos;
}

template <class K, class T>
void DHeap<K, T>::insert(const std::pair<K,T>& value) {
    // Insert the element into a leaf position and get the position of the last leaf

    int lastLeaf = this->insertToLeaf(value);

    // Move the element up in the heap to maintain the heap property
    moveHigh(lastLeaf);
    
    // Update the root of the tree to the new root
    this->treePosVector->root = VEC[1];

}

/**
 * @brief Change the value associated with a specific key in the D-ary heap.
 *
 * This method changes the value associated with a specific key in the D-ary heap. It first
 * finds the position of the element with the given key and then updates its value.
 *
 * @param key The key for which you want to change the associated value.
 * @param newValue The new value to associate with the key.
 * @throw std::runtime_error if the specified key doesn't exist in the heap.
 */
template <class K, class T>
void DHeap<K, T>::changeValue(const K& key, const T& newValue) {

    // Find the position of the element with the specified key
    int posKey = this->findByKey(key);

    if (posKey != -1) {
        // Update the value associated with the key to the new value
        (VEC[posKey]->value).second = newValue;
    } else {
        // If the specified key is not found, throw an exception with an error message
        throw std::runtime_error("DHeap::changeValue error: the key to change the value doesn't exist");
    }
}


/**
 * @brief Change the key associated with a specific element in the D-ary heap.
 *
 * This method changes the key associated with a specific element in the D-ary heap. It first
 * finds the position of the element with the given value, updates its key, and then adjusts
 * the element's position in the heap to maintain the heap property.
 *
 * @param newKey The new key to associate with the element.
 * @param element The element for which you want to change the associated key.
 * @throw std::runtime_error if the specified element doesn't exist in the heap.
 */
template <class K, class T>
void DHeap<K, T>::changeKey(const K& newKey, const T& element) {

    // Find the position of the element with the specified value
    int posValue = this->findByValue(element);
    
    // Update the key associated with the element to the new key
    VEC[posValue]->value.first = newKey;
    
    if (posValue != -1) {

        // Determine the parent of the node, if it exists
        int posParent = 1;
        if (posValue > 1) {
            posParent = TREE->getParentPos(posValue);
        }

        // If the parent is bigger, try to push down the node; otherwise, push up the node
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
        // If the specified element is not found, throw an exception with an error message
        throw std::runtime_error("DHeap::changeKey error: the element for changing the key doesn't exist");
    }
}


template <class K, class T>
int DHeap<K, T>::insertToLeaf(const std::pair<K, T>& value) {

    // If the root is empty, add the element as the root
    if (!VEC[1]) {
        TREE->addRoot(value);
        return 1;
    } else {
        // Find the position of the last leaf node
        int lastLeaf = getLeaf();

        // Create a new leaf node with the specified value
        Node<std::pair<K, T>> *leaf = new Node<std::pair<K, T>>(value);
        leaf->pos = lastLeaf + 1;

        // Add the leaf node to the heap
        VEC[lastLeaf + 1] = leaf;

        // Return the position of the inserted element (leaf node)
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

/**
 * @brief Move a node up in the D-ary heap to maintain the heap property.
 *
 * This method moves a node up in the D-ary heap to maintain the heap property. It ensures that
 * the parent node has a higher (or lower, depending on the heap type) key than the moved node.
 *
 * @param posNode The position of the node to move.
 * @throw std::runtime_error if the specified position is invalid.
 */
template <class K, class T>
void DHeap<K, T>::moveHigh(int posNode) {
    /*
    Pre-conditions
    1.  1 <= posNode <= VEC.size()
    */

    if (posNode < 1 || posNode > VEC.size()) {
        // If the specified position is not within the valid range, throw an exception
        throw std::runtime_error("DHeap::moveHigh error: the position is not permitted in the structure");
    }

    if (posNode == 1) {
        // The node is already at the root, so there's no need to move it further
        return;
    }

    // Retrieve the value of the node at the specified position
    std::pair<K, T> nodeValue = VEC[posNode]->value;

    // Retrieve the value of the parent node
    std::pair<K, T> parentValue = VEC[TREE->getParentPos(posNode)]->value;

    if (!this->isMin) {
        // If it's a max-heap, move the node up while its key is greater than the parent's key
        while (posNode > 1 && nodeValue.first > parentValue.first) {
            // Get the position of the parent node and swap their values
            int posParent = TREE->getParentPos(posNode);
            TREE->swapPositionValue(posNode, posParent);
            posNode = posParent;

            // Update the parent value if the node has a parent
            if (posNode > 1) {
                parentValue = VEC[TREE->getParentPos(posNode)]->value;
            }
        }
    } else {
        // If it's a min-heap, move the node up while its key is smaller than the parent's key
        while (posNode > 1 && nodeValue.first < parentValue.first) {
            // Get the position of the parent node and swap their values
            int posParent = TREE->getParentPos(posNode);
            TREE->swapPositionValue(posNode, posParent);
            posNode = posParent;

            // Update the parent value if the node has a parent
            if (posNode > 1) {
                parentValue = VEC[TREE->getParentPos(posNode)]->value;
            }
        }
    }
    return;
}


/**
 * @brief Move a node down in the D-ary heap to maintain the heap property.
 *
 * This method moves a node down in the D-ary heap to maintain the heap property. It ensures
 * that the node has a higher (or lower, depending on the heap type) key than its children.
 *
 * @param posNode The position of the node to move.
 */
template <class K, class T>
void DHeap<K, T>::moveLow(int posNode) {

    /*
    sia u il figlio di v con il max valore, se esiste:
    - Se v non ha figli o chiave(v) >= chiave(u), break
    - Altrimenti, swapPositions()
    */

    int posChild;
    std::pair<K, T> value, childValue;

    while (true) {

        // Get the values from the starting two positions
        value = VEC[posNode]->value;

        // If the node is a leaf or doesn't exist, return
        if (VEC[posNode] && this->isLeaf(value)) {
            return;
        }

        // Find the position of the child with the max value
        posChild = this->getChildPos(posNode);

        // Get the value of the child node
        childValue = VEC[posChild]->value;

        if (!this->isMin) {
            // If it's a max-heap and the value is greater than or equal to the child's value, break
            if (value.first >= childValue.first) {
                break;
            }
        } else {
            // If it's a min-heap and the value is smaller than or equal to the child's value, break
            if (value.first <= childValue.first) {
                break;
            }
        }

        // Swap the positions of the node and the child
        TREE->swapPositionValue(posNode, posChild);

        // Update the position for the next cycle
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
}

#endif /* DHEAP_CPP */