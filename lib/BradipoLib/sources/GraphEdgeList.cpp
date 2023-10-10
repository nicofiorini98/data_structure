#ifndef GRAPH_EDGE_LIST_CPP
#define	GRAPH_EDGE_LIST_CPP
#pragma once
#include "GraphEdgeList.h"
using namespace datalib;

//default constructor
template<class T>
GraphEdgeList<T>::GraphEdgeList(): Graph<T>(){
	
}

//this function add a node with an edge to nullptr
template<class T>
void GraphEdgeList<T>::addNode(const T &_x){

	Node<T>* x_ptr = new Node<T>(_x);
	Edge<T> e(x_ptr, nullptr);
	edgeList.push_back(e);

}

// template<class T>
// void GraphEdgeList<T>::addNode(node<T>* _x){
// 	edge<T> e(_x,nullptr);
// 	edgeList.push_back(e);
// }


template<class T>
void GraphEdgeList<T>::addEdge(const T *srcValue, const T *destValue){

	/* pre-conditions
	 * 1. we can't add two same edge 
	 * 2. 
     */

	// typename std::vector<edge<T>>::iterator src_itr; 
	// typename std::vector<edge<T>>::iterator dest_itr; 

	if(edgeExistence(srcValue,destValue)){
		std::string error("the edge inserted already exist");
		throw error;
	}

	Node<T> *src_ptr  = new Node<T>(*srcValue);
	Node<T> *dest_ptr = new Node<T>(*destValue);

	Edge<T> e(src_ptr, dest_ptr);


	//TODO da controllare, non è giusto
	if(!nodeExistence(*src_ptr)){
		++this->num_edge;
	}
	if(!nodeExistence(*dest_ptr)){
		++this->num_node;
	}

	edgeList.push_back(e);
	++this->num_edge;
	//ragionare sui grafi orientati e non, in questo caso sto facendo 
	//i grafi orientati, per i non posso usare un attriibuto dell'arco
}

template<class T>
int GraphEdgeList<T>::degree(const T &value){

	int _degree = 0;
	for(auto &e: edgeList){
		if((e.src)->value == value && (e.dest)!=nullptr)
			_degree++;
	}
	return _degree;
}

template<class T>
std::vector<Edge<T>> GraphEdgeList<T>::getIncidentEdge(const T &_x){

	std::vector<Edge<T>> incident_edge;

	for(auto &e: edgeList){
		if((e.src)->value == _x || (e.dest)->value == _x){
			Edge<T> appo(e);
			incident_edge.push_back(appo);
		}
	}
	return incident_edge;
}

template<class T>
void GraphEdgeList<T>::deleteNode(const T &_x){

	typename std::vector<Edge<T>>::iterator i;
	typename std::vector<T> appo;
	for(i = edgeList.begin();i<edgeList.end();++i){
		if((i->src)->value == _x){
			edgeList.erase(i);
		}
		else if((i->dest)->value)
			edgeList.erase(i);
	}

}

//return true if exists an edge (_src,_dest) in the structure
template<class T>
bool GraphEdgeList<T>::edgeExistence(const T &_src, const T &_dest) const{

	//TODO da finire
	// typename std::vector<edge<T>>::iterator appo_itr;

	for(auto &e: edgeList){
		// if(appo_itr.src == nullptr || appo_itr.dest == nullptr)
		// 	continue;

		if((e.src)->value == _src && (e.dest)->value == _dest)
			return true;
	}
	return false;
}

template<class T>
bool GraphEdgeList<T>::edgeExistence(const T *srcValue, const T *destValue) const{

	if(srcValue==nullptr){
		std::string error("arco invalido\n");
		throw error;
	}
	

	for(auto &e: edgeList){
		// if(appo_itr.src == nullptr || appo_itr.dest == nullptr)
		// 	continue;

		if((e.src)->value == *srcValue && (e.dest)->value == *destValue)
			return true;
	}
	return false;
}

//return true if exists a node _x in the structure
template<class T>
bool GraphEdgeList<T>::nodeExistence(const T &x) const{
	for(auto &e:edgeList){
		if((e.src)->value == x || (e.dest)->value==x)
			return true;
	}
	return false;
}

template<class T>
bool GraphEdgeList<T>::nodeExistence(const Node<T> &value) const{
	for(auto&e: edgeList){
		if((e.src)->value == value.value || (e.dest)->value==value.value)
			return true;
	}
	return false;
}

	
// template<class T>
// bool GraphEdgeList<T>::edge_existence(const edge<T> _e) const{

// 	//TODO ricontrollare
// 	edge_existence(_e.getSourceValue(),_e.getDestinationValue());

// }
	

template<class T>
void GraphEdgeList<T>::showNode() const{

	for(auto& e: edgeList)
		std::cout<<"( "<< e.getSourceValue()<<" )\n";


}

template<class T>
std::list<Edge<T>>& GraphEdgeList<T>::getAllEdges(std::list<Edge<T>> &edges){
	edges.clear();	
	
	for(auto &e: this->edgeList){
		edges.push_back(e);
	}
	return edges;
}

template<class T>
void GraphEdgeList<T>::getIncidentEdges(const T &value, std::list<Edge<T>> &edges) {
    //posso ritornare direttamente una lista degli archi che stanno in edgeList
    for(auto& e: edgeList){
        if(*(e->dest) == value || (*e->src) == value)
            edges.push_back(*e);
    }
}

template<class T>
void GraphEdgeList<T>::getOutgoingEdges(const T &value, std::list<Edge<T>> &edges) {
    for(auto& e: edgeList){
        if(*(e->src) == value){
            edges.push_back(*e);
        }
    }
}

template<class T>
void GraphEdgeList<T>::getIncomingEdges(const T &value, std::list<Edge<T>> &edges) {
    for(auto& e: edgeList){
        if(*(e->dest) == value){
            edges.push_back(*e);
        }
    }
}

template<class T>
bool GraphEdgeList<T>::isAdjacent(const T &srcValue, const T &destValue) {
    //todo
    return false;
}

#endif