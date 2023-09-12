#ifndef DHEAP_CPP 
#define DHEAP_CPP
#include "Node.h"
#include <cmath>
#include <vector>
#pragma once

#include <stdexcept>
#include "DHeap.h"
#include "TreePosVector.h"

using namespace datalib;

template <class T>
DHeap<T>::DHeap(int degree, int size, const std::vector<T>& values){

	this->degree = degree;

	int height = (log(size) / log(this->degree)) + 1;


	this->treePosVector = new TreePosVector<T>(this->degree,height);
	
	/* 
	Costruzione di un heap in tempo O(n): 
	1. Creiamo un albero di taglia e dimensioe appropriata in cui mettiamo gl oggetti dell'array
 	*/
	// std::cout<<(this->heapTree)->vecNode[0]<<"\n";

  	// riempimento vettore posizione mantenendo una struttura completa
	// fino al penultimo livello, il valore 0 deve essere sempre nullo
	this->insertFromArray(values);

	//todo qui va fatto l'heapify

	// (this->treePosVector)->showStructure();
	
}

template<class T>
void DHeap<T>::insertFromArray(const std::vector<T>& values){

    (this->treePosVector)->addValuesFromVector(values);

	// qui vado a chiamare la procedura heapify
	heapify(1);

}


//todo testare
//procedura che chiama se stessa in modo ricorsivo
template<class T>
void DHeap<T>::heapify(int posNode){
	
	//devo chiamare la procedura ricorsivamente
	// per ogni figlio del nodo
	
	//caso base
	//if(T è vuoto){
		//return
	//}
	// si ferma quando sono arrivato alla foglia, non ho niente da aggiustare
	bool isLeaf = this->isLeaf((this->treePosVector)->vecNode[posNode]->value);
	if(isLeaf){
		return;
	}

	//for each child of vecNode[posNode]
	//chiama heapify con la posizione del figlio
	// heapify()
	for(int i=0; i<degree;i++){
		if((this->treePosVector)->vecNode[(posNode*2)+i]){
			this->heapify((posNode*2)+i);
		}
	}
	fixHeap(posNode);

}
//private
//TODO to debug
template<class T>
void DHeap<T>::fixHeap(int posNode){

	//utilizzato solo internamente
	T nodeValue = this->treePosVector->vecNode[posNode]->value;

	if(this->isLeaf(nodeValue)){
		return;
	}
	else{
		//sia u il figlio di v con chiave massima
		int posMax = (this->treePosVector)->getMaxChildPos(posNode); // todo error here, parent Node to provide
		T childMaxValue = this->treePosVector->vecNode[posMax]->value;
		std::cout<<"posMax: "<<posMax<<"\n";
			
		//if chiave(V) < chiave(u)
		if(nodeValue < childMaxValue){
			//scambia chiave(v),chiave(u)
			(this->treePosVector)->swapPositionValue(posNode,posMax);
			// (this->treePosVector)->vecNode[posNode] = childMaxValue;
			// (this->treePosVector)->vecNode[posMax] = nodeValue;
		}
		this->fixHeap(posMax);
	}
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

		//get parent positions and swap the values
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
	int numChildren = (this->treePosVector)->getNumChildren(nodeValue);
	bool test = numChildren == 0;
	if(test){
		return true;
	}
	return false;

}




template <class T>
DHeap<T>::~DHeap(){

	delete treePosVector;
	std::cout<<"~Dheap() called\n";

}



#endif /* DHEAP_CPP */