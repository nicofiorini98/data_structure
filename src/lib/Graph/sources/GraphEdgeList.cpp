#ifndef GRAPH_EDGE_LIST_CPP
#define	GRAPH_EDGE_LIST_CPP

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
	edge_list.push_back(e);

}

// template<class T>
// void GraphEdgeList<T>::addNode(node<T>* _x){
// 	edge<T> e(_x,nullptr);
// 	edge_list.push_back(e);
// }


template<class T>
void GraphEdgeList<T>::addEdge(const T *_src, const T *_dest){

	/* pre-conditions
	 * 1. we can't add two same edge 
	 * 2. 
     */

	// typename std::vector<edge<T>>::iterator src_itr; 
	// typename std::vector<edge<T>>::iterator dest_itr; 

	if(edge_existence(_src,_dest)){
		std::string error("the edge inserted already exist");
		throw error;
	}

	Node<T> *src_ptr  = new Node<T>(*_src);
	Node<T> *dest_ptr = new Node<T>(*_dest);

	Edge<T> e(src_ptr, dest_ptr);


	//TODO da controllare, non è giusto
	if(!node_existence(*src_ptr)){
		++this->num_edge;
	}
	if(!node_existence(*dest_ptr)){
		++this->num_node;
	}

	edge_list.push_back(e);
	++this->num_edge;
	//ragionare sui grafi orientati e non, in questo caso sto facendo 
	//i grafi orientati, per i non posso usare un attriibuto dell'arco
}

template<class T>
int GraphEdgeList<T>::degree(const T &_x){

	int _degree = 0;
	for(auto &e: edge_list){
		if((e.src)->value == _x && (e.dest)!=nullptr)
			_degree++;
	}
	return _degree;
}

template<class T>
std::vector<Edge<T>> GraphEdgeList<T>::getIncidentEdge(const T &_x){

	std::vector<Edge<T>> incident_edge;

	for(auto &e: edge_list){
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
	for(i = edge_list.begin();i<edge_list.end();++i){
		if((i->src)->value == _x){
			edge_list.erase(i);
		}
		else if((i->dest)->value)
			edge_list.erase(i);
	}

}

//return true if exists an edge (_src,_dest) in the structure
template<class T>
bool GraphEdgeList<T>::edge_existence(const T &_src, const T &_dest) const{

	//TODO da finire
	// typename std::vector<edge<T>>::iterator appo_itr;

	for(auto &e: edge_list){
		// if(appo_itr.src == nullptr || appo_itr.dest == nullptr)
		// 	continue;

		if((e.src)->value == _src && (e.dest)->value == _dest)
			return true;
	}
	return false;
}

template<class T>
bool GraphEdgeList<T>::edge_existence(const T *_src, const T *_dest) const{

	if(_src==nullptr){
		std::string error("arco invalido\n");
		throw error;
	}
	

	for(auto &e: edge_list){
		// if(appo_itr.src == nullptr || appo_itr.dest == nullptr)
		// 	continue;

		if((e.src)->value == *_src && (e.dest)->value == *_dest)
			return true;
	}
	return false;
}

//return true if exists a node _x in the structure
template<class T>
bool GraphEdgeList<T>::node_existence(const T &_x) const{
	for(auto &e:edge_list){
		if((e.src)->value == _x || (e.dest)->value==_x)
			return true;
	}
	return false;
}

template<class T>
bool GraphEdgeList<T>::node_existence(const Node<T> &_x) const{
	for(auto&e: edge_list){
		if((e.src)->value == _x.value || (e.dest)->value==_x.value)
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

	for(auto& e: edge_list)
		std::cout<<"( "<< e.getSourceValue()<<" )\n";


}

template<class T>
void GraphEdgeList<T>::getIncidentEdges(const T &node, std::list<Edge<T>> &_list) {
    //posso ritornare direttamente una lista degli archi che stanno in edge_list
    for(auto& e: edge_list){
        if(*(e->dest) == node || (*e->src) == node)
            _list.push_back(*e);
    }
}

template<class T>
void GraphEdgeList<T>::getOutgoingEdges(const T &node, std::list<Edge<T>> &_list) {
    for(auto& e: edge_list){
        if(*(e->src) == node){
            _list.push_back(*e);
        }
    }
}

template<class T>
void GraphEdgeList<T>::getIncomingEdges(const T &node, std::list<Edge<T>> &_list) {
    for(auto& e: edge_list){
        if(*(e->dest) == node){
            _list.push_back(*e);
        }
    }
}

template<class T>
bool GraphEdgeList<T>::isAdjacent(const T &_src, const T &_dest) {
    //todo
    return false;
}

#endif