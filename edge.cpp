#ifndef EDGE_CPP
#define EDGE_CPP
#include "edge.h"

using namespace datalib;

template<class T>
edge<T>::edge(node<T>* _src,node<T>* _dest,int _weight,const std::string _mark){

	if(src==nullptr){
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
edge<T>::edge(const T *_src,const T *_dest,int _weight,const std::string &_mark){
	if(src==nullptr){
		std::string error("you can't add a (nullptr,dest) edge\n");
		throw error;
	}

	src  = new node<T>(*_src);
	dest = new node<T>(*_dest);
	weight = _weight;
	mark = _mark;

}

///copy costructor
template<class T>
edge<T>::edge(const edge<T> &_x){

	src  = _x.src;
	dest = _x.dest;
	weight = _x.weight;
	mark = _x.mark;

}

#endif