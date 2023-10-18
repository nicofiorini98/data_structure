#ifndef EDGE_CPP
#define EDGE_CPP
#pragma once
#include "Edge.h"

using namespace datalib;

template<class T>
Edge<T>::Edge(Node<T>* src, Node<T>* dest, int weight, const std::string mark){

	if(src==nullptr){
		std::string error("you can't add a (nullptr,dest) edge\n");
		throw error;
	}
	this->src  = src;
	this->dest = dest;
	this->weight = weight;
	this->mark = mark;

}

//todo ricontrollare questa funzione, non sono convinto che va bene 
template<class T>
Edge<T>::Edge(const T *_src, const T *_dest, int _weight, const std::string &_mark){

	if(_src==nullptr){
		std::string error("you can't add a (nullptr,dest) edge\n");
		throw error;
	}

	src  = new Node<T>(*_src);
	dest = new Node<T>(*_dest);
	weight = _weight;
	mark = _mark;

}

///copy costructor
template<class T>
Edge<T>::Edge(const Edge<T> &x){
	
	this->src  = new Node(*(x.src));
	this->dest = new Node(*(x.dest));
	weight = x.weight;
	mark = x.mark;

}

#endif