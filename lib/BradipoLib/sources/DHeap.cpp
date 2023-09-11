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

	// std::cout<<"height of heap is: "<< height;

	this->treePosVector = new TreePosVector<T>(this->degree,height);
	// std::cout<<(this->heapTree)->vecNode[0]<<"\n";

  	// riempimento vettore posizione mantenendo una struttura completa
	// fino al penultimo livello, il valore 0 deve essere sempre nullo
	// (this->treePosVector)->addValuesFromVector(values);
 	

	//todo qui va fatto l'heapify

	// (this->treePosVector)->showStructure();
	
}

template<class T>
int DHeap<T>::getLeaf(){

	Node<T>* leaf;

	for(auto& value: this->treePosVector->vecNode){
		if(value){
			leaf=value;
			// std::cout<<value->value<<"\n";
		}
	}

	return leaf->pos;
}



template<class T>
void DHeap<T>::insert(const T& nodeValue){
	//aggiungere il nodo dopo l'ultima foglia
	// int lastLeaf = this->getLeaf();
	int lastLeaf = this->insertToLeaf(nodeValue);

	// if(lastLeaf <= (this->treePosVector)->vecNode.size()){
		// Node<T>* node = new Node(nodeValue);
		// node->pos = lastLeaf + 1 ;
		// (this->treePosVector)->vecNode[lastLeaf +1] = node;
	// 	moveHigh(node->pos);
	// }
	moveHigh(lastLeaf);
}

template<class T>
int DHeap<T>::insertToLeaf(const T& nodeValue){


	if(!(this->treePosVector)->vecNode[1]){
		(this->treePosVector)->addRoot(nodeValue);
		return 1;
	}else{
		int lastLeaf = getLeaf();

		Node<T>* leaf = new Node<T>(nodeValue);
		leaf->pos = lastLeaf +1;
		(this->treePosVector)->vecNode[lastLeaf + 1 ] = leaf;
		return (lastLeaf +1);
	}
}

template<class T>
void DHeap<T>::moveHigh(int posNode){
	/* 
	Pre-conditions
	1.  1 =< posNode <= vecNode.size()
	 */
	
	if(posNode < 1 && posNode < (this->treePosVector)->vecNode.size()){
		throw std::runtime_error("the position is not permitted in the structure");
	}
	
	if(posNode==1){
		return;
	}
	
	T nodeValue = (this->treePosVector)->vecNode[posNode]->value;

	T parentValue = (this->treePosVector)->vecNode[this->treePosVector->getParentPos(posNode)]->value;

	while( posNode > 1 && nodeValue > parentValue){

		int posParent = (this->treePosVector)->getParentPos(posNode);
		(this->treePosVector)->swapPositionValue(posNode,posParent);
		posNode = posParent;

		//update parent value if the node has parent
		if(posNode > 1){
			parentValue = (this->treePosVector)->vecNode[this->treePosVector->getParentPos(posNode)]->value;
		}

	}
	return;
}

template<class T>
void DHeap<T>::deleteMax(){
	// here we change the max with the last leaf and we repair the 
	// heap with fixHeap
}


template<class T>
bool DHeap<T>::isLeaf(const T& nodeValue){
	//ritorna true se il nodo non ha figli

	// std::cout<<"Test TreePosVector::getChildren(\"9\")";

    // std::list<int> children = this->treePosVector->getChildren(nodeValue);

    // for(auto& c: children){
    //     std::cout<<"\n--> "<<c;
    // }

	bool test = this->treePosVector->getChildren(nodeValue).empty();
	if(test){
		return true;
	}
	return false;
}

//private
//TODO to debug
template<class T>
void DHeap<T>::fixHeap(int posNode){

	//utilizzato solo internamente
	T nodeValue = this->treePosVector->vecNode[posNode];

	if(this->isLeaf(nodeValue)){
		return;
	}
	else{
		//sia u il figlio di v con chiave massima
		int posMax = (this->treePosVector)->getMaxChildPos(); // todo error here, parent Node to provide
		T childMaxValue = this->treePosVector->vecNode[posMax];
		std::cout<<"posMax: "<<posMax<<"\n";
			
		//if chiave(V) < chiave(u)
		if(nodeValue < childMaxValue){
			//scambia chiave(v),chiave(u)
			(this->treePosVector)->vecNode[posNode] = childMaxValue;
			(this->treePosVector)->vecNode[posMax] = nodeValue;
		}
		this->fixHeap(posMax);
	}
}

template <class T>
DHeap<T>::~DHeap(){

	delete treePosVector;
	std::cout<<"~Dheap() called\n";

}



#endif /* DHEAP_CPP */