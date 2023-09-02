#ifndef EDGE_CPP
#define EDGE_CPP
#pragma once
#include "Edge.h"

using namespace datalib;

template<class T>
Edge<T>::Edge(Node<T>* _src, Node<T>* _dest, int _weight, const std::string _mark){

	if(_src==nullptr){
		std::string error("you can't add a (nullptr,dest) edge\n");
		throw error;
	}
	src  = _src;
	dest = _dest;
	weight = _weight;
	mark = _mark;

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
Edge<T>::Edge(const Edge<T> &_x){

	src  = _x.src;
	dest = _x.dest;
	weight = _x.weight;
	mark = _x.mark;

}

#endif