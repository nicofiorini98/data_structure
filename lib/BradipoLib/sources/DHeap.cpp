#ifndef DHEAP_CPP
#define DHEAP_CPP
#include "Node.h"
#include <cmath>
#include <vector>
#pragma once

#include "DHeap.h"
#include "TreePosVector.h"
#include <stdexcept>

using namespace datalib;

template <class T>
DHeap<T>::DHeap(int degree, int size, bool isMin, const std::vector<T> &values) {

    this->degree = degree;
    this->isMin = isMin;

    int height = (log(size) / log(this->degree)) + 1;

    this->treePosVector = new TreePosVector<T>(this->degree, height);

    /*
    Costruzione di un heap in tempo O(n):
    1. Creiamo un albero di taglia e dimensioe appropriata in cui mettiamo gl
    oggetti dell'array
    */

    // riempimento vettore posizione mantenendo una struttura completa
    // fino al penultimo livello, il valore 0 deve essere sempre nullo
    if(!values.empty()){
        this->insertFromArray(values);
    }

}

template <class T>
void DHeap<T>::insertFromArray(const std::vector<T> &values) {

    (this->treePosVector)->addValuesFromVector(values);

    heapify(1);
}

// todo testare
// procedura che chiama se stessa in modo ricorsivo
template <class T> void DHeap<T>::heapify(int posNode) {

    //make sure that the function doesn't continue if the pos is bigger than vector
    if(posNode >= (this->treePosVector)->vecNode.size())
        return;

    bool isLeaf = this->isLeaf((this->treePosVector)->vecNode[posNode]->value);
    if (isLeaf) {
        return;
    }

    // for each child of vecNode[posNode]
    // call heapify with the child positions 
    for (int i = 0; i < degree; i++) {
        if (( this->treePosVector)->vecNode[(posNode * 2) + i]) {
            this->heapify((posNode * 2) + i);
        }
    }
    fixHeap(posNode);
}

template <class T> void DHeap<T>::fixHeap(int posNode) {

    T nodeValue = this->treePosVector->vecNode[posNode]->value;
    // std::cout<<"fixheap call with value: "<<nodeValue<<std::endl;

    if (this->isLeaf(nodeValue)) {
        return;
    } else {

        int posMax = (this->treePosVector)->getMaxChildPos(posNode,this->isMin);

        T childMaxValue = this->treePosVector->vecNode[posMax]->value;

		//if node is smaller than the maxChild, swap the positions
        if (!this->isMin && nodeValue < childMaxValue) {
            (this->treePosVector)->swapPositionValue(posNode, posMax);
        }else if(this->isMin && nodeValue > childMaxValue){
            (this->treePosVector)->swapPositionValue(posNode, posMax);
        }

        this->fixHeap(posMax);
    }
}


template<class T>
T DHeap<T>::getFirstValue(){
    if(!this->isEmpty()){
        return this->treePosVector->vecNode[1]->value;
    }else{
        throw std::runtime_error("DHeap<T>::getMaxValue() error: the instance is empty, can't get max value");
    }
}

template <class T>
T DHeap<T>::popValue(){

    if(!this->isEmpty()){
        T value = this->getFirstValue();
        this->deleteValue(this->getFirstValue());
        return value;
    }else{
        throw std::runtime_error("DHeap::popMaxValue() error: the instance is empty, can't return the max value");
    }
}

//TODO to test the min, like setValue
template <class T> void DHeap<T>::deleteValue(const T &nodeValue) {
    // trovare il nodo da cancellare
    // scambiarlo con una foglia in modo che mantengo la struttura
    // poi chiamare una procedura che fa moveHigh o moveLow a seconda
    // se è più grande o più piccolo del padre

    // search position of the node to delete

    // get the iterator of the node
    typename std::vector<Node<T> *>::iterator value_itr;
    value_itr = datalib::trova((this->treePosVector)->vecNode.begin(),
                               (this->treePosVector)->vecNode.end(), nodeValue);

    if (value_itr != (this->treePosVector)->vecNode.end()) {

        // get the positions to swap
        int posLeaf = this->getLeaf();
        int pos2Delete = (*value_itr)->pos;

        if(pos2Delete == posLeaf){
            delete (this->treePosVector)->vecNode[posLeaf];
            (this->treePosVector)->vecNode[posLeaf] = nullptr;
            return;
        }

        (this->treePosVector)->swapPositionValue(posLeaf, pos2Delete);

        //delete node, and assign the nullptr to the position deleted
        delete (this->treePosVector)->vecNode[posLeaf];
        (this->treePosVector)->vecNode[posLeaf] = nullptr;

		// get the parent of the node if exist
        int posParent = 1;
        if(pos2Delete > 1){
            posParent = (this->treePosVector)->getParentPos(pos2Delete);
        }

        // if the parent is bigger, try to push down the node, 
        //otherwise push up the node
        if (!this->isMin) {
            if ((this->treePosVector)->vecNode[posParent]->value >
                    (this->treePosVector)->vecNode[pos2Delete]->value ||
                posParent == 1)
                moveLow(pos2Delete);
            else
                moveHigh(pos2Delete);

        } else {
            if ((this->treePosVector)->vecNode[posParent]->value >
                    (this->treePosVector)->vecNode[pos2Delete]->value ||
                posParent == 1)
                moveLow(pos2Delete);
            else
                moveHigh(pos2Delete);
        }
    } else {
        throw std::runtime_error(
            "DHeap::deleteValue error: the value to delete doesn't exist");
    }
}

template<class T>
bool DHeap<T>::isEmpty(){
    if((this->treePosVector)->vecNode[1])
        return false;
    else
        return true;
}

template <class T> int DHeap<T>::getLeaf() {

    Node<T> *leaf;

    for (auto &value : this->treePosVector->vecNode) {
        if (value)
            leaf = value;
    }

    return leaf->pos;
}

template <class T> void DHeap<T>::insert(const T &nodeValue) {
    // add the node to the last leaf
    //  int lastLeaf = this->getLeaf();
    int lastLeaf = this->insertToLeaf(nodeValue);

    moveHigh(lastLeaf);
}

template<class T>
void DHeap<T>::setValue(const T& oldValue,const T& newValue){
    
    typename std::vector<Node<T> *>::iterator value_itr;
    value_itr = datalib::trova((this->treePosVector)->vecNode.begin(),
                               (this->treePosVector)->vecNode.end(), oldValue);

    if (value_itr != (this->treePosVector)->vecNode.end()) {

        int posValue = (*value_itr)->pos;
        (*value_itr)->value = newValue;
		// get the parent of the node if exist
        int posParent = 1;
        if(posValue > 1){
            posParent = (this->treePosVector)->getParentPos(posValue);
        }

        // if the parent is bigger, try to push down the node, 
        //otherwise push up the node
        if (!this->isMin) {
            if ((this->treePosVector)->vecNode[posParent]->value >
                    (this->treePosVector)->vecNode[posValue]->value)
                moveLow(posValue);
            else
                moveHigh(posValue);

        } else {
            if ((this->treePosVector)->vecNode[posParent]->value > (this->treePosVector)->vecNode[posValue]->value)
                moveHigh(posValue);
            else
                moveLow(posValue);
        }
    } else {
        throw std::runtime_error(
            "DHeap::changeValue error: the value to change doesn't exist");
    }

}

template <class T> int DHeap<T>::insertToLeaf(const T &nodeValue) {

    if (!(this->treePosVector)->vecNode[1]) {
        (this->treePosVector)->addRoot(nodeValue);
        return 1;
    } else {
        int lastLeaf = getLeaf();

        Node<T> *leaf = new Node<T>(nodeValue);
        leaf->pos = lastLeaf + 1;
        (this->treePosVector)->vecNode[lastLeaf + 1] = leaf;
        return (lastLeaf + 1);
    }
}

template <class T> void DHeap<T>::moveHigh(int posNode) {
    /*
    Pre-conditions
    1.  1 =< posNode <= vecNode.size()
     */

    if (posNode < 1 && posNode < (this->treePosVector)->vecNode.size()) {
        throw std::runtime_error(
            "the position is not permitted in the structure");
    }

    if (posNode == 1) {
        return;
    }

    T nodeValue = (this->treePosVector)->vecNode[posNode]->value;

    T parentValue = (this->treePosVector)
                        ->vecNode[this->treePosVector->getParentPos(posNode)]
                        ->value;

    // add min
    if(!this->isMin){
        while (posNode > 1 && nodeValue > parentValue) {

            // get parent positions and swap the values
            int posParent = (this->treePosVector)->getParentPos(posNode);
            (this->treePosVector)->swapPositionValue(posNode, posParent);
            posNode = posParent;

            // update parent value if the node has parent
            if (posNode > 1) {
                parentValue =
                    (this->treePosVector)
                        ->vecNode[this->treePosVector->getParentPos(posNode)]
                        ->value;
            }
        }
        
    }else{
        while (posNode > 1 && nodeValue < parentValue) {

            // get parent positions and swap the values
            int posParent = (this->treePosVector)->getParentPos(posNode);
            (this->treePosVector)->swapPositionValue(posNode, posParent);
            posNode = posParent;

            // update parent value if the node has parent
            if (posNode > 1) {
                parentValue =
                    (this->treePosVector)
                        ->vecNode[this->treePosVector->getParentPos(posNode)]
                        ->value;
            }
        }
    }
    return;
}

template <class T> void DHeap<T>::moveLow(int posNode) {

    /*
    sia u il figlio di v con il max valore,se esiste
    if(v non ha figli o chiave(v)>=chiave(u)) break
    swapPositions()
     */

	int posChild;
	T value,childValue;
    

    while (true) {

		// getting the values from the starting two positions
		value = (this->treePosVector)->vecNode[posNode]->value;

		if(value && this->isLeaf(value)){
			return;
		}

		posChild = (this->treePosVector)->getMaxChildPos(posNode,this->isMin);

		childValue = (this->treePosVector)->vecNode[posChild]->value;

        // todo add min
        if(!this->isMin){
            if(value > childValue )
                return;
        }else{
            if(value <childValue)
            return;
        }

        (this->treePosVector)->swapPositionValue(posNode, posChild);

        // update the positions for the next cycle
        posNode = posChild;

    }
}

template <class T> bool DHeap<T>::isLeaf(const T &nodeValue) {

    // ritorna true se il nodo non ha figli
    int numChildren = (this->treePosVector)->getNumChildren(nodeValue);

    if (numChildren == 0)
        return true;

    return false;
}

template <class T> DHeap<T>::~DHeap() {

    delete treePosVector;
    std::cout << "~Dheap() called\n";
}

#endif /* DHEAP_CPP */