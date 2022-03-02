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

}

template<class T>
void graph_inc_list<T>::addEdge(const edge<T>& _edge){
	addEdge(&(_edge.getSourceValue()),&(_edge.getDestinationValue()));
}

template<class T>
void graph_inc_list<T>::addEdge(const T *_src,const T *_dest){

	//pre-conditions
	/* 
	1. if _src or _dest are null, then throw error
	2. if the edge exists, then don't add it and return error
	3. if the node doesn't exists,then add it
 	*/

	// typename std::map<T,node<T>*>::iterator src_itr;
	// typename std::map<T,node<T>*>::iterator dest_itr;

	//cannot insert edge with null_ptr
	if(_src == nullptr || _dest == nullptr){
		std::string error("node null is not allowed\n");
		throw error;
	}

	//se l'arco esiste lancia errore
	if(edge_existence(_src,_dest)){
		std::string error("cannot insert same edge\n");
		throw error;
	}

	//trova il nodo src
	typename std::map<T,node<T>*>::iterator src_itr;
	src_itr = inc_list.find(*_src);

	//se src non esiste crealo
	if(src_itr==inc_list.end()){
		addNode(*_src);
		src_itr = inc_list.find(*_src);
	}

	//trova il nodo dest
	typename std::map<T,node<T>*>::iterator dest_itr;
	dest_itr = inc_list.find(*_dest);

	//se dest non esiste crealo
	if (dest_itr == inc_list.end()){
		addNode(*_dest);
		dest_itr = inc_list.find(*_dest);
	}

	//creazione arco
	//std::cout<<"arco: "<<*(src_itr->second)<<"\n";
	edge<T> *e = new edge<T>(src_itr->second,dest_itr->second);
	//std::cout<<"boh\n";

	//aggiungere arco alle strutture
	edge_list.push_back(e);
	(src_itr->second)->connected_edges.push_back(e);

}




template <class T>
void graph_inc_list<T>::deleteNode(const T& _x){

	//erase the node _x and the edges it is involved in

	//inizio a rimuovere il nodo nella inc_list

	//get the node and erase from the map
	typename std::map<T,node<T>*>::iterator x_itr;
	x_itr = inc_list.find(_x);
	inc_list.erase(x_itr);

	//delete the others edge with _x in others node
	for(auto &n: inc_list){
		typename std::list<edge<T>*>::iterator e_itr;
		for(e_itr=(n.second)->connected_edges.begin(); e_itr != (n.second)->connected_edges.end();){
			if(*((*e_itr)->dest) == _x)
				e_itr = n.second->connected_edges.erase(e_itr);
			else
				e_itr++;
			
		}
	}

	//delete the edge with _x in the edge_lists
	typename std::list<edge<T>*>::iterator e_itr;
	for(e_itr = edge_list.begin(); e_itr != edge_list.end();){
		if(*((*e_itr)->src) == _x || *((*e_itr)->dest) == _x ){
			e_itr = edge_list.erase(e_itr);
		}
		else
			e_itr++;
	}

}

template<class T>
void graph_inc_list<T>::deleteEdge(const T &_src,const T &_dest){
	
	//delete the edge on inc_lists
	for(auto &n: inc_list){
		typename std::list<edge<T>*>::iterator e_itr;
		for(e_itr=(n.second)->connected_edges.begin(); e_itr != (n.second)->connected_edges.end();){
			if( *(*e_itr)->src == _src  && *(*e_itr)->dest == _dest)
				e_itr = n.second->connected_edges.erase(e_itr);
			else
				e_itr++;
		}
	}

	//delete edge on edge_lists
	typename std::list<edge<T>*>::iterator e_itr;
	for(e_itr = edge_list.begin(); e_itr != edge_list.end();){
		if(*((*e_itr)->src) == _src && *((*e_itr)->dest) == _dest){ 
			e_itr = edge_list.erase(e_itr);
		}
		else
			e_itr++;
	}
}

template<class T>
void graph_inc_list<T>::deleteEdge(const edge<T>& e){
	deleteEdge(e.src,e.dest);
}

template<class T>
int graph_inc_list<T>::max_degree(){

	int max = 0;
	for(auto &n: inc_list){
		if(max < (n.second)->connected_edges.size())
			max = (n.second)->connected_edges.size();
	}

	return max;

}

template<class T>
int graph_inc_list<T>::degree(const T& _x){

	// for(auto &n: inc_list){
	// 	if(*n.second == _x)
	// 		return ((*n.second).connected_edges.size());
	// 	else{
	// 		std::string error("degree: il nodo non esiste");
	// 		throw error;
	// 	}
	// }

}

//todo controllare
template<class T>
bool graph_inc_list<T>::isAdjacent(const T &_src, const T &_dest){
	//edge<T> e(_src,_dest);
	//return edge_existence(e);
	//TODO da fare
	return false;
}


template<class T>
void graph_inc_list<T>::breadthFirstSearch(const T& _first_node,tree_ptr_list<T>& _tree){

	/*
	 * Algoritmo visitaBFS(vertice s) ---> albero (OK)
	 * 	 marca tutti i vertici come inesplorati   (OK)
	 *   marca il vertice s come aperto
	 *   T <-- albero formato da un solo vertice s 
	 * 	 Coda F
	 *   f.enqueque(s)
	 *   while(not F.isempty()) do 
	 *   	u <-- F.dequeue()
	 *   	marca u come chiuso
	 *      visita il vertice u
	 *      for each (arco(u,v)  del grafo) do 
	 * 			if (v è inesplorato) then
	 * 				marca il vertice v come aperto
	 * 				F.enqueque(v)
	 * 				rendi u padre di v in T
	 * 	return T.
	*/

	//marcatura di tutti i vertici come inesplorati
	for(auto &n: inc_list)
		n.second->mark = unexplored;
		
	//ricerca del nodo da cui partire
	typename std::map<T,node<T>*>::iterator first_node_itr;
	first_node_itr = inc_list.find(_first_node);
	if(first_node_itr == inc_list.end()){
		std::string error("the node for breadth first search doesn't exists in the graph");
		throw error;
	}


	//l'albero è formato dal solo vertice da cui partire
	_tree.addNode(&(first_node_itr->second)->value);
	(first_node_itr->second)->mark = open;

	//inserire il vertice da cui partire nella frontiera (queue)
	// F.enqueque(s)
	std::queue<node<T>*> open_node;
	open_node.push((first_node_itr->second));

	while(!open_node.empty()){

		//qui prendo il nodo nella coda
		node<T> *u = open_node.front(); //return a reference to the first element
		open_node.pop(); 				//remove the first element 

		//visita il vertice u
		//typename std::map<T,node<T>*>::iterator u_itr;
		//u_itr = inc_list.find(*u); 
		
		u->mark= closed;
		
		//visita il vertice u (quindi prendo gli archi), prendo la destinazione del vertice u
		for(auto &e: u->connected_edges){
		 	if((e->dest)->mark == unexplored){
		 		(e->dest)->mark = open; 						//marca v come aperto
		 		open_node.push(e->dest);						
		 		_tree.addNode(&((e->dest)->value),&(u->value)); //rendi u padre di v in t
		 	}
		}
	}
}



template<class T>
void graph_inc_list<T>::showStructure() const{

	for(auto &n: inc_list ){
		std::cout << *(n.second) << "-->";
		for(auto &e: (n.second)->connected_edges){
			std::cout <<"("<< e->getSourceValue() << "," <<e->getDestinationValue()<<")";
		}
		std::cout << "\n";
	}
	for(auto &e: edge_list){
		std::cout << *e;
	}
}

template<class T>
bool graph_inc_list<T>::edge_existence(const edge<T> &_e) const{

	for(auto &e: edge_list ){
		 if(((e->src) == _e.src) && 
		 	 (e->dest == _e.dest))
		 	 return true;
	}
	return false;
}


template<class T>
bool graph_inc_list<T>::edge_existence(const T* _src,const T* _dest) const{

	//todo controllare
	edge<T> e(_src,_dest);
	return edge_existence(e);

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
void graph_inc_list<T>::showNode() const{
	
	for(auto &n: inc_list ){
		std::cout << (n.second) << "-->";
		for(auto &e: (n.second)->connected_edges){
			std::cout <<"("<< e->src << "," <<e->dest<<")";
		}
		std::cout << "\n";
	}
	for(auto &e: edge_list){
		std::cout << *e;
	}
}

#endif