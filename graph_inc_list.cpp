#ifndef GRAPH_INC_LIST_CPP
#define GRAPH_INC_LIST_CPP

#include "graph_inc_list.h"

using namespace datalib;

//default constructor
template<class T>
graph_inc_list<T>::graph_inc_list():graph<T>(){

}

template<class T>
void graph_inc_list<T>::addNode(const T &_x){

	node<T>* src_ptr = new node<T>(_x);
	// inc_list.insert(std::pair<T,node<T>*>(src_ptr->value,src_ptr)); 
	inc_list.insert({src_ptr->value,src_ptr}); 
	this->num_node++;

}

template<class T>
void graph_inc_list<T>::addEdge(const T *_src,const T *_dest){

	//pre-conditions
	/* 
	1. if _src or _dest are null, then throw error
	2. se l'arco esiste, allora non aggiungerlo, e ritorna errore
	3. se un nodo non esiste, va aggiunto
	
	 */
	// typename std::map<T,node<T>*>::iterator src_itr;
	// typename std::map<T,node<T>*>::iterator dest_itr;

	if(_src == nullptr || _dest == nullptr){
		std::string error("node null is not allowed\n");
		throw error;
	}

	edge<T> e(_src,_dest); //(non voglio dire niente, ma mesa st'arco viene eliminato)
	if(edge_existence(e)){
		std::string error("cannot insert same edge");
		throw error;
	}

	if(!node_existence(_src))
		addNode(*_src);

	if(!node_existence(_dest))
		addNode(*_dest);

	edge_list.push_back(e);

	typename std::map<T,node<T>*>::iterator src_itr;


}


template<class T>
void graph_inc_list<T>::showStructure() const{

	for(auto &n: inc_list )
		std::cout<<*(n.second)<<"\n";

}

template<class T>
bool graph_inc_list<T>::edge_existence(const edge<T> _e) const{

	for(auto &e: edge_list ){
		if(((e.getSourceValue()) == _e.getSourceValue()) && 
			 (e.getDestinationValue() == _e.getDestinationValue()))
			 return true;
	}
	return false;
}

template<class T>
bool graph_inc_list<T>::node_existence(const T* _x) const{

	for(auto &n: this->inc_list){
		if((n.second)->value == *_x)
			return true;
	}
	return false;
}

template<class T>
typename std::map<T,node<T>*>::iterator graph_inc_list<T>::getNode(const T* _n) const{

}

#endif