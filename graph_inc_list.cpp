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
	inc_list.insert(std::pair<T,node<T>*>(src_ptr->value,src_ptr)); 

	this->num_node++;

}


template<class T>
void graph_inc_list<T>::addEdge(const T *_src,const T *_dest){


}


template<class T>
void graph_inc_list<T>::showStructure() const{

	for(auto n: inc_list )
		std::cout<<n<<"\n";

}



#endif