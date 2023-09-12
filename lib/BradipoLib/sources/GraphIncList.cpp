#ifndef GRAPH_INC_LIST_CPP
#define GRAPH_INC_LIST_CPP
#include <stdexcept>
#pragma once
#include "GraphIncList.h"


using namespace datalib;

//default constructor
template<class T>
GraphIncList<T>::GraphIncList():Graph<T>(){
	

}

template<class T>
void GraphIncList<T>::addNode(const T &_x){

	Node<T>* x_ptr = new Node<T>(_x);

	incList.insert({x_ptr->value,x_ptr}); 
	++this->numNodes;

}

template<class T>
void GraphIncList<T>::addEdge(const Edge<T>& _edge){
	addEdge(&(_edge.getSourceValue()),&(_edge.getDestinationValue()));
}

template<class T>
void GraphIncList<T>::addEdge(const T& srcValue, const T& destValue){

	//TODO passaggio per riferimento
	//pre-conditions
	/* 
	1. if _src or _dest are null, then throw error
	2. if the edge exists, then don't add it and return error
	3. if the node doesn't exists,then add it
 	*/

	// typename std::map<T,node<T>*>::iterator src_itr;
	// typename std::map<T,node<T>*>::iterator dest_itr;

	//cannot insert edge with null_ptr
	//TODO adesso posso toglierlo con il passaggio byReference
	// if(srcValue == nullptr || destValue == nullptr){
	// 	std::string error("node null is not allowed\n");
	// 	throw error;
	// }

	//se l'arco esiste lancia errore
	//TODO controllare
	if(edgeExistence(&srcValue, &destValue)){
		std::string error("cannot insert same edge\n");
		throw error;
	}

	//trova il nodo src
	typename std::map<T,Node<T>*>::iterator src_itr;
	src_itr = incList.find(srcValue);

	//se src non esiste crealo
	if(src_itr==incList.end()){
		addNode(srcValue);
		src_itr = incList.find(srcValue);
	}

	//find dest node
	typename std::map<T,Node<T>*>::iterator dest_itr;
	dest_itr = incList.find(destValue);

    //create dest if doesn't exists
	if (dest_itr == incList.end()){
		addNode(destValue);
		dest_itr = incList.find(destValue);
	}

	//create edge
	Edge<T> *e = new Edge<T>(src_itr->second, dest_itr->second);

	//add edge to the structure
	edgeList.push_back(e);
	(src_itr->second)->connected_edges.push_back(e);

	++this->numEdges;
}




template <class T>
void GraphIncList<T>::deleteNode(const T& value){

	//erase the node _x and the edges it is involved in

	//inizio a rimuovere il nodo nella inc_list

	//get the node and erase from the map
	typename std::map<T,Node<T>*>::iterator x_itr;
	x_itr = incList.find(value);
	incList.erase(x_itr);

	//delete the others edge with _x in others node
	for(auto &n: incList){
		typename std::list<Edge<T>*>::iterator e_itr;
		for(e_itr=(n.second)->connected_edges.begin(); e_itr != (n.second)->connected_edges.end();){
			if(*((*e_itr)->dest) == value)
				e_itr = n.second->connected_edges.erase(e_itr);
			else
				e_itr++;
			
		}
	}

	//delete the edge with _x in the edgeLists
	typename std::list<Edge<T>*>::iterator e_itr;
	for(e_itr = edgeList.begin(); e_itr != edgeList.end();){
		if(*((*e_itr)->src) == value || *((*e_itr)->dest) == value ){
			e_itr = edgeList.erase(e_itr);
		}
		else
			e_itr++;
	}

}

template<class T>
void GraphIncList<T>::deleteEdge(const T &srcValue, const T &destValue){
	
	//delete the edge on inc_lists
	for(auto &n: incList){
		typename std::list<Edge<T>*>::iterator e_itr;
		for(e_itr=(n.second)->connected_edges.begin(); e_itr != (n.second)->connected_edges.end();){
			if( *(*e_itr)->src == srcValue  && *(*e_itr)->dest == destValue)
				e_itr = n.second->connected_edges.erase(e_itr);
			else
				e_itr++;
		}
	}

	//delete edge on edgeLists
	typename std::list<Edge<T>*>::iterator e_itr;
	for(e_itr = edgeList.begin(); e_itr != edgeList.end();){
		if(*((*e_itr)->src) == srcValue && *((*e_itr)->dest) == destValue){ 
			e_itr = edgeList.erase(e_itr);
		}
		else
			e_itr++;
	}
}

template<class T>
void GraphIncList<T>::deleteEdge(const Edge<T>& e){
	deleteEdge(e.src,e.dest);
}

template<class T>
int GraphIncList<T>::maxDegree(){

	int max = 0;
	for(auto &n: incList){
		if(max < (n.second)->connected_edges.size())
			max = (n.second)->connected_edges.size();
	}

	return max;
}

template<class T>
int GraphIncList<T>::degree(const T& nodeValue){

	for(auto &n: incList){
		if((n.first) == nodeValue)
			return ((*n.second).connected_edges.size());
	}
	throw std::runtime_error("GraphIncList<T>::degree(---) error: Il nodo "+nodeValue+ " non esiste");
}

//todo controllare
template<class T>
bool GraphIncList<T>::isAdjacent(const T &_src, const T &_dest){



	return false;
}


// //todo aggiustare con l'interfaccia nuova
// template<class T>
// void GraphIncList<T>::breadthSearch(const T& startValue, TreePtrList<T>& tree){

// 	/*
// 	 * Algoritmo visitaBFS(vertice s) ---> albero (OK)
// 	 * 	 marca tutti i vertici come inesplorati   (OK)
// 	 *   marca il vertice s come aperto
// 	 *   T <-- albero formato da un solo vertice s 
// 	 * 	 Coda F
// 	 *   f.enqueque(s)
// 	 *   while(not F.isempty()) do 
// 	 *   	u <-- F.dequeue()
// 	 *   	marca u come chiuso
// 	 *      visita il vertice u
// 	 *      for each (arco(u,v)  del grafo) do 
// 	 * 			if (v è inesplorato) then
// 	 * 				marca il vertice v come aperto
// 	 * 				F.enqueque(v)
// 	 * 				rendi u padre di v in T
// 	 * 	return T.
// 	*/

// 	//marcatura di tutti i vertici come inesplorati
// 	for(auto &n: incList)
// 		n.second->mark = unexplored;
		
// 	//ricerca del nodo da cui partire
// 	typename std::map<T,Node<T>*>::iterator first_node_itr;
// 	first_node_itr = incList.find(startValue);
// 	if(first_node_itr == incList.end()){
// 		std::string error("the node for breadth first search doesn't exists in the graph");
// 		throw error;
// 	}


// 	//l'albero è formato dal solo vertice da cui partire
// 	// _tree.addNode(new)
// 	tree.addNode(new T(first_node_itr->first),nullptr);
// 	(first_node_itr->second)->mark = open;

// 	//inserire il vertice da cui partire nella frontiera (queue)
// 	// F.enqueque(s)
// 	std::queue<Node<T>*> open_node;
// 	open_node.push((first_node_itr->second));

// 	while(!open_node.empty()){

// 		//qui prendo il nodo nella coda
// 		Node<T> *u = open_node.front(); //return a reference to the first element
// 		open_node.pop(); 				//remove the first element 

// 		//visita il vertice u
// 		//typename std::map<T,node<T>*>::iterator u_itr;
// 		//u_itr = inc_list.find(*u); 
		
// 		u->mark= closed;
		
// 		//visita il vertice u (quindi prendo gli archi), prendo la destinazione del vertice u
// 		for(auto &e: u->connected_edges){
// 		 	if((e->dest)->mark == unexplored){
// 		 		(e->dest)->mark = open; 										  //marca v come aperto
// 		 		open_node.push(e->dest);						
// 		 		tree.addNode(new T((e->dest)->value),new T(u->value)); //rendi u padre di v in t
// 		 	}
// 		}
// 	}
// }


// template<class T>
// void GraphIncList<T>::depthSearch(const T &startValue, TreePtrList<T> &tree) {

//     // marcatura di tutti i vertici come inesplorati
//     for(auto &n: incList)
//         n.second->mark = unexplored;

//     //ricerca del nodo da cui partire
//     typename std::map<T,Node<T>*>::iterator first_node_itr;
//     first_node_itr = incList.find(startValue);
//     if(first_node_itr == incList.end()){
//         std::string error("the node for breadth first search doesn't exists in the graph");
//         throw error;
//     }

// 	tree.addNode(new T(first_node_itr->first),nullptr);
// 	//marca il vertice iniziale come aperto
//     (first_node_itr->second)->mark = open;

//     //inserire il vertice da cui partire nella frontiera (stack)
//     std::stack<Node<T>*> open_node;
//     open_node.push((first_node_itr->second));

//     while(!open_node.empty()){

//         //qui prendo il nodo nella coda
//         Node<T> *u = open_node.top(); //return a reference to the last element inserted
//         open_node.pop(); 				//remove the first element

//         //visita il vertice u
//         //typename std::map<T,node<T>*>::iterator u_itr;
//         //u_itr = inc_list.find(*u);

//         //if(u->mark == closed)
//             //continue;

//         u->mark = closed;

//         //visita il vertice u (quindi prendo gli archi), prendo la destinazione del vertice u
//         for(auto &e: u->connected_edges){
//             auto* v = e->dest;
//             if(v->mark == unexplored){
//                 v->mark = open; 						//marca v come aperto
//                 open_node.push(v);
//                 tree.addNode(&(v->value),&(u->value)); //rendi u padre di v in t
//                 tree.updateParent(v->value,u->value);

//             }
//             else if((e->dest)->mark == open){
//                 open_node.push(e->dest);
//                 tree.updateParent((e->dest)->value,u->value);
//             }
//         }
//     }
// }


template<class T>
void GraphIncList<T>::showStructure() const{

	for(auto &n: incList ){
		std::cout << *(n.second) << "-->";
		for(auto &e: (n.second)->connected_edges){
			std::cout <<"("<< e->getSourceValue() << "," <<e->getDestinationValue()<<")";
		}
		std::cout << "\n";
	}
	for(auto &e: edgeList){
		std::cout << *e;
	}
}

template<class T>
bool GraphIncList<T>::edgeExistence(const Edge<T> &edge) const{

	for(auto &e: edgeList ){
		 if(((e->src) == edge.src) && 
		 	 (e->dest == edge.dest))
		 	 return true;
	}
	return false;
}


template<class T>
bool GraphIncList<T>::edgeExistence(const T* srcValue, const T* destValue) const{

	//todo controllare
	Edge<T> edge(srcValue, destValue);
	return edgeExistence(edge);

}

template<class T>
bool GraphIncList<T>::nodeExistence(const T* nodeValue) const{

	for(auto &n: this->inc_list){
		if((n.second)->value == *nodeValue)
			return true;
	}
	return false;
}


template<class T>
void GraphIncList<T>::showNode() const{
	
	for(auto &n: incList ){
		std::cout << (n.second) << "-->";
		for(auto &e: (n.second)->connected_edges){
			std::cout <<"("<< e->src << "," <<e->dest<<")";
		}
		std::cout << "\n";
	}
	for(auto &e: edgeList){
		std::cout << *e;
	}
}

template<class T>
void GraphIncList<T>::getIncidentEdges(const T& value, std::list<Edge<T>>& edges) {
    //posso ritornare direttamente una lista degli archi che stanno in edgeList
    for(auto& e: edgeList){
        if(*(e->dest) == value || (*e->src) == value)
            edges.push_back(*e);
    }
}

template<class T>
void GraphIncList<T>::getOutgoingEdges(const T &value, std::list<Edge<T>>& edges) {
    for(auto& e: edgeList){
        if(*(e->src) == value){
            edges.push_back(*e);
        }
    }
}

template<class T>
void GraphIncList<T>::getIncomingEdges(const T &value, std::list<Edge<T>>& edges) {
    for(auto& e: edgeList){
        if(*(e->dest) == value){
            edges.push_back(*e);
        }
    }
}


#endif