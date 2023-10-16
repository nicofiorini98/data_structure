#ifndef GRAPH_INC_LIST_CPP
#define GRAPH_INC_LIST_CPP
#pragma once
#include <stdexcept>
#include "GraphIncList.h"


using namespace datalib;

//default constructor
template<class T>
GraphIncList<T>::GraphIncList():Graph<T>(){}

template <class T>
GraphIncList<T>::~GraphIncList(){
	
	for(auto& n: this->incList){
		delete n.second;
	}
	for(auto&e: this->edgeList){
		e->src = nullptr;
		e->dest = nullptr;
		delete e;
	}
}

template<class T>
void GraphIncList<T>::addNode(const T &_x){

	Node<T>* x_ptr = new Node<T>(_x);

	incList.insert({x_ptr->value,x_ptr}); 
	++this->numNodes;

}

template<class T>
void GraphIncList<T>::addEdge(const Edge<T>& edge){
	addEdge(edge.getSourceValue(),edge.getDestinationValue(),edge.getWeight());
}

template<class T>
void GraphIncList<T>::addEdge(const T& srcValue, const T& destValue,double weight){

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
	if(src_itr == incList.end()){
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

	//TODO to create edge with weight
	//create edge
	Edge<T> *e = new Edge<T>(src_itr->second, dest_itr->second,weight);

	//add edge to the structure
	edgeList.push_back(e);
	(src_itr->second)->connected_edges.push_back(e);

	++this->numEdges;
}

template <class T>
T GraphIncList<T>::getValue(const T& nodeValue)const {
	//trova il nodo src
	//

	// return (this->incList[nodeValue])->value;
	typename std::map<T,Node<T>*>::const_iterator valueItr;
	valueItr = incList.find(nodeValue);
	
	if(valueItr != incList.end()){
		return (*valueItr).first;
	}else{
		throw std::runtime_error("GraphIncList<T>::getValue error: nodeValue doesn't exists in the Graph");
	}
}

//TODO non è banale, in quanto devo mantenere anche le relazioni tra i nodi
//trovo ogni arco che punta a quel nodo, e aggiorno il valore con un nuovo nodo allocato
template <class T>
void GraphIncList<T>::setValue(const T& oldValue,const T& newValue){
	
	//creare un nuovo nodo oldValue
	Node<T>* newNode = new Node(newValue);
	
	//trova il nodo src e aggiorno il valore, assegnando anche una nuova 
	//chiave alla mappa
	typename std::map<T,Node<T>*>::iterator oldItr;
	oldItr = incList.find(oldValue);
	Node<T>* oldNode = (*oldItr).second;
	
	//aggiorno il puntatore al nuovo nodo ad ogni arco
	for(auto& e: edgeList){
		if(e->src == oldNode){
			e->src = newNode;
		}else if(e->dest == oldNode){
			e->dest = newNode;
		}
	}

	newNode->connected_edges = oldNode->connected_edges;


	if(oldItr != incList.end()){
		// ((*oldItr).second)->value = newValue;
		// incList[newValue] = incList[oldValue];
		// incList.erase(oldValue);
		incList.erase(oldValue);
		incList.insert(std::pair<T,Node<T>*>(newValue,newNode));
		return;

	}else{
		throw std::runtime_error("GraphIncList<T>::getValue error: nodeValue doesn't exists in the Graph");
	}
}


template<class T>
void GraphIncList<T>::getAllNodeValues(std::list<T>& nodesList){
	nodesList.clear();

	for(auto &n: incList){
		nodesList.push_back(n.first);
	}	
	return;
	
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
int GraphIncList<T>::degree(const T& nodeValue){

	for(auto &n: incList){
		if((n.first) == nodeValue)
			return ((*n.second).connected_edges.size());
	}
	throw std::runtime_error("GraphIncList<T>::degree(---) error: The node inserted doesn't exist");
}

//TODO controllare
template<class T>
bool GraphIncList<T>::isAdjacent(const T &_src, const T &_dest){



	return false;
}


//todo aggiustare con l'interfaccia nuova
template<class T>
void GraphIncList<T>::breadthSearch(const T& startValue, TreePtrList<T>& tree){

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
	for(auto &n: incList)
		n.second->mark = unexplored;
		
	//ricerca del nodo da cui partire
	typename std::map<T,Node<T>*>::iterator first_node_itr;
	first_node_itr = incList.find(startValue);
	if(first_node_itr == incList.end()){
		std::string error("the node for breadth first search doesn't exists in the graph");
		throw error;
	}


	//l'albero è formato dal solo vertice da cui partire
	// _tree.addNode(new)
	tree.addRoot(first_node_itr->first);
	(first_node_itr->second)->mark = open;

	//inserire il vertice da cui partire nella frontiera (queue)
	// F.enqueque(s)
	std::queue<Node<T>*> open_node;
	open_node.push((first_node_itr->second));

	while(!open_node.empty()){

		//qui prendo il nodo nella coda
		Node<T> *u = open_node.front(); //return a reference to the first element
		open_node.pop(); 				//remove the first element 

		u->mark= closed;
		
		//visita il vertice u (quindi prendo gli archi), prendo la destinazione del vertice u
		for(auto &e: u->connected_edges){
		 	if((e->dest)->mark == unexplored){
		 		(e->dest)->mark = open; 										  //marca v come aperto
		 		open_node.push(e->dest);						
		 		tree.addNode((e->dest)->value,u->value); //rendi u padre di v in t
		 	}
		}
	}
}



template<class T>
void GraphIncList<T>::showStructure() const{

	std::cout<<"GraphEdgeList relations:\n";
	for(auto &n: incList ){
		std::cout << *(n.second) << "-->";
		for(auto &e: (n.second)->connected_edges){
			std::cout <<"("<< e->getSourceValue() << "," <<e->getDestinationValue()<<")";
		}
		std::cout << "\n";
	}
	std::cout<<"\n +++++++++\nGraphEdgeList structures:\n";
	for(auto &e: edgeList){
		std::cout << *e<<"\n";
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
std::list<Edge<T>>& GraphIncList<T>::getAllEdges(std::list<Edge<T>> &edges)const{
	edges.clear();	
	
	for(auto &e: this->edgeList){
		edges.push_back(*e);	
	}

	return edges;
}

template<class T>
std::list<Edge<T>>& GraphIncList<T>::getIncidentEdges(const T& value, std::list<Edge<T>>& edges) {
    //posso ritornare direttamente una lista degli archi che stanno in edgeList
    for(auto& e: edgeList){
        if(*(e->dest) == value || (*e->src) == value)
            edges.push_back(*e);
    }
	return edges;
}

template<class T>
std::list<Edge<T>>& GraphIncList<T>::getOutgoingEdges(const T &value, std::list<Edge<T>>& edges) {
    for(auto& e: edgeList){
        if(*(e->src) == value){
            edges.push_back(*e);
        }
    }
	return edges;
}

template<class T>
std::list<Edge<T>>& GraphIncList<T>::getIncomingEdges(const T &value, std::list<Edge<T>>& edges) {
    for(auto& e: edgeList){
        if(*(e->dest) == value){
            edges.push_back(*e);
        }
    }
	return edges;
}


#endif