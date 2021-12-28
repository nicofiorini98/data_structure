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

	node<T>* x_ptr = new node<T>(_x);

	inc_list.insert({x_ptr->value,x_ptr}); 
	++this->num_node;
	//std::cout << "inserito nodo:" << *x_ptr;

}

template<class T>
void graph_inc_list<T>::addEdge(const edge<T>& _edge){
	addEdge(_edge.getSourceValue(),_edge.getDestinationValue());
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

	edge<T>* e = new edge<T>(_src,_dest);

	if(edge_existence(*e)){
		std::string error("cannot insert same edge\n");
		throw error;
	}

	typename std::map<T,node<T>*>::iterator src_itr;
	src_itr = inc_list.find(*_src);

	if(src_itr==inc_list.end()){
		addNode(*_src);
	}

	typename std::map<T,node<T>*>::iterator dest_itr;
	dest_itr = inc_list.find(*_dest);

	if (dest_itr == inc_list.end()) {
		addNode(*_dest);
	}
	
	edge_list.push_back(e);
	//(src_itr->second)->edge_list.push_back(e);  //riga che da problemi, controllare

}


template<class T>
void graph_inc_list<T>::showStructure() const{

	for(auto &n: inc_list )
	{
		std::cout<<*(n.second)<<"\n";
		//for(auto e: (n.second)->edge_list){
			//std::cout << e;
		//}
	}


	/*std::cout << "stampa edge_list\n";
	for(auto e: this->edge_list)
	{
		std::cout << e << "\n";
	}*/
}


//TODO controllare
template<class T>
bool graph_inc_list<T>::edge_existence(const edge<T> &_e) const{

	//for(auto &e: edge_list ){
	//	// if(((e.getSourceValue()) == _e.getSourceValue()) && 
	//	// 	 (e.getDestinationValue() == _e.getDestinationValue()))
	//	// 	 return true;
	//}
	return false;
}

//TODO controllare
template<class T>
bool graph_inc_list<T>::node_existence(const T* _x) const{

	for(auto &n: this->inc_list){
		if((n.second)->value == *_x)
			return true;
	}
	return false;
}


#endif