#ifndef DHEAP_CPP 
#define DHEAP_CPP
#include "Node.h"
#include <cmath>
#pragma once

#include <stdexcept>
#include "DHeap.h"
#include "TreePosVector.h"

using namespace datalib;

template <class T>
DHeap<T>::DHeap(int degree, int size ,const std::vector<T>& values){

	this->degree = degree;

	//todo controllare altezza
	if(values.size()>=size){
		throw std::runtime_error("the number of values is bigger than size, use bigger size");
	}

	int height = log(size) / log(this->degree);
	std::cout<<"height of heap is: "<< height;
	this->treePosVector = new TreePosVector<T>(this->degree,height);
	// std::cout<<(this->heapTree)->vecNode[0]<<"\n";

  	// riempimento vettore posizione mantenendo una struttura completa
	// fino al penultimo livello, il valore 0 deve essere sempre nullo
	(this->treePosVector)->addValuesFromVector(values);
 	

	//todo qui va fatto l'heapify


	(this->treePosVector)->showStructure();
	

}

template<class T>
int DHeap<T>::getLeaf(){
	Node<T>* leaf;

	for(auto& value: this->treePosVector->vecNode){
		if(value){
			leaf=value;
			std::cout<<value->value<<"\n";
		}
	}

	return leaf->pos;
}


template<class T>
void DHeap<T>::deleteMax(){
	// here we change the max with the last leaf and we repair the 
	// heap with fixHeap


}

template<class T>
bool DHeap<T>::isLeaf(const T& nodeValue){
	//ritorna true se il nodo non ha figli

	bool test = this->treePosVector->getChildren(nodeValue).empty();
	if(test){
		return true;
	}
	return false;
}

template<class T>
void DHeap<T>::fixHeap(int posNode){
	// if(this->treePosVector->vecNode[posNode])
}

template <class T>
DHeap<T>::~DHeap(){

	delete treePosVector;
	std::cout<<"~Dheap() called\n";

}



#endif /* DHEAP_CPP */