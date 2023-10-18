#ifndef GRAPH_EDGE_LIST_CPP
#define GRAPH_EDGE_LIST_CPP
#pragma once
#include "GraphEdgeList.h"
#include <stdexcept>
using namespace datalib;

// default constructor
template <class T> GraphEdgeList<T>::GraphEdgeList() : Graph<T>() {}

template <class T> GraphEdgeList<T>::~GraphEdgeList() {}

template <class T> void GraphEdgeList<T>::addNode(const T &value) {

    Node<T> *valuePtr;

    if (nodeExistence(value)) {
        valuePtr = nodeExistence(value);
    } else {
        valuePtr = new Node<T>(value);
    }
    Edge<T> *e = new Edge<T>(valuePtr, nullptr);
    edgeList.push_back(e);
}

template <class T> Node<T> *GraphEdgeList<T>::nodeExistence(const T &value) {
    Node<T> *node = nullptr;

    for (auto &e : this->edgeList) {
        if (e->src->value == value) {
            return e->src;
        }
        if (e->dest->value == value) {
            return e->dest;
        }
    }

    return node;
}

template <class T>
void GraphEdgeList<T>::addEdge(const T &srcValue, const T &destValue,
                               double weight) {

    /* pre-conditions
     * 1. we can't add two same edge
     */

    if (edgeExistence(srcValue, destValue)) {
        std::string error("the edge inserted already exist");
        throw error;
    }

    Node<T> *src_ptr;
    Node<T> *dest_ptr;

    if (nodeExistence(srcValue)) {
        src_ptr = nodeExistence(srcValue);
    } else {
        src_ptr = new Node<T>(srcValue);
    }

    if (nodeExistence(destValue)) {
        dest_ptr = nodeExistence(destValue);
    } else {
        dest_ptr = new Node<T>(destValue);
    }

    Edge<T> *e = new Edge<T>(src_ptr, dest_ptr);

    if (!nodeExistence(*src_ptr)) {
        ++this->numEdges;
    }
    if (!nodeExistence(*dest_ptr)) {
        ++this->numNodes;
    }

    edgeList.push_back(e);
    ++this->numEdges;
}

template <class T> int GraphEdgeList<T>::degree(const T &value) {

    int _degree = 0;
    for (auto &e : edgeList) {
        if ((e->src)->value == value && (e->dest) != nullptr)
            _degree++;
    }
    return _degree;
}

template <class T> T GraphEdgeList<T>::getValue(const T &value) const {

    for (auto &e : edgeList) {
        if ((e->dest)->value == value) {
            return (e->dest)->value;
        } else if ((e->src)->value == value) {
            return (e->src)->value;
        }
    }

    throw std::runtime_error(
        "GraphEdgeList::getValue error: the value to get doesn't exists");
}

template <class T>
void GraphEdgeList<T>::setValue(const T &oldValue, const T &newValue) {
    for (auto &e : edgeList) {
        if ((e->dest)->value == oldValue) {
            (e->dest)->value = newValue;
        } else if ((e->src)->value == oldValue) {
            (e->src)->value = newValue;
        }
    }
}

template <class T>
void GraphEdgeList<T>::setValue(Node<T> &oldNode, Node<T> &newNode) {
    for (auto &e : edgeList) {
        if ((e->dest) == oldNode) {
            (e->dest) = newNode;
        } else if ((e.src) == oldNode) {
            (e->src) = newNode;
        }
    }
}

template <class T>
std::vector<Edge<T>> GraphEdgeList<T>::getIncidentEdge(const T &value) {

    std::vector<Edge<T>> incident_edge;

    for (auto &e : edgeList) {
        if ((e->src)->value == value || (e->dest)->value == value) {
            Edge<T> appo(e);
            incident_edge.push_back(appo);
        }
    }
    return incident_edge;
}

template <class T> void GraphEdgeList<T>::deleteNode(const T &value) {

    typename std::vector<Edge<T> *>::iterator i;
    typename std::vector<T> appo;
    for (i = edgeList.begin(); i < edgeList.end(); ++i) {
        if (((*i)->src)->value == value) {
            edgeList.erase(i);
        } else if (((*i)->dest))
            edgeList.erase(i);
    }
}

template <class T>
bool GraphEdgeList<T>::edgeExistence(const T &src, const T &dest) const {

    for (auto &e : edgeList) {

        if ((e->src)->value == src && (e->dest)->value == dest)
            return true;
    }
    return false;
}

template <class T>
bool GraphEdgeList<T>::edgeExistence(const T *srcValue,
                                     const T *destValue) const {

    if (srcValue == nullptr) {
        std::string error("arco invalido\n");
        throw error;
    }

    for (auto &e : edgeList) {
        if ((e->src)->value == *srcValue && (e->dest)->value == *destValue)
            return true;
    }
    return false;
}

// return true if exists a node _x in the structure
// template <class T> bool GraphEdgeList<T>::nodeExistence(const T &x) const {
//     for (auto &e : edgeList) {
//         if ((e.src)->value == x || (e.dest)->value == x)
//             return true;
//     }
//     return false;
// }

template <class T>
bool GraphEdgeList<T>::nodeExistence(const Node<T> &value) const {
    for (auto &e : edgeList) {
        if ((e->src)->value == value.value || (e->dest)->value == value.value)
            return true;
    }
    return false;
}

template <class T>
std::list<Edge<T>> &
GraphEdgeList<T>::getAllEdges(std::list<Edge<T>> &edges) const {

    edges.clear();
    for (auto &e : this->edgeList) {
        edges.push_back(*e);
    }
    return edges;
}

template <class T>
std::list<Edge<T>> &
GraphEdgeList<T>::getIncidentEdges(const T &value, std::list<Edge<T>> &edges) {
    // posso ritornare direttamente una lista degli archi che stanno in edgeList
    for (auto &e : edgeList) {
        if ((e->dest)->value == value || (e->src)->value == value)
            edges.push_back(*e);
    }
    return edges;
}

template <class T>
std::list<Edge<T>> &
GraphEdgeList<T>::getOutgoingEdges(const T &value, std::list<Edge<T>> &edges) {
    
    for(auto& e: edgeList){
        if((e->src)->value == value){
            edges.push_back(*e);
        }
    }
	return edges;
}

template <class T>
std::list<Edge<T>*> GraphEdgeList<T>::getEdgesPtr(const T& value,std::list<Edge<T>*>& edges){

    for(auto& e: edgeList){
        if((e->src)->value == value){
            edges.push_back(e);
        }
    }
	return edges;
    
}

template <class T>
std::list<Edge<T>> &
GraphEdgeList<T>::getIncomingEdges(const T &value, std::list<Edge<T>> &edges) {
    for (auto &e : edgeList) {
        if ((e->dest)->value == value) {
            edges.push_back(*e);
        }
    }
    return edges;
}

template <class T>
TreePtrList<T> &GraphEdgeList<T>::breadthSearch(const T &startValue,
                                                TreePtrList<T> &tree) {

    //marcatura di tutti i vertici come inesplorati
	// for(auto &n: incList)
	// 	n.second->mark = unexplored;
		
	// //ricerca del nodo da cui partire
	// typename std::map<T,Node<T>*>::iterator first_node_itr;
	// first_node_itr = incList.find(startValue);
	// if(first_node_itr == incList.end()){
	// 	std::string error("the node for breadth first search doesn't exists in the graph");
	// 	throw error;
	// }
    
    // marco tutti i vertici come inesplorati
    for(auto& e: this->edgeList){
        if(e->src){e->src->mark = unexplored;}
        if(e->dest){e->dest->mark = unexplored;}
    }

    Node<T>* startValuePtr = nodeExistence(startValue);

	//l'albero è formato dal solo vertice da cui partire
	tree.addRoot(startValue);
	startValuePtr->mark = open;

	//inserire il vertice da cui partire nella frontiera (queue)
	// F.enqueque(s)
	std::queue<Node<T>*> open_node;
	open_node.push(startValuePtr);

	while(!open_node.empty()){

		//return a reference to the first element
		Node<T> *u = open_node.front(); 
		//remove the first element 
		open_node.pop(); 				
										
        if(u->mark==closed)
            continue;

        std::cout<<"visita "<<*u<<std::endl;

		u->mark = closed;
    
		//visita il vertice u (quindi prendo gli archi), prendo la destinazione del vertice u
        std::list<Edge<T>*> edges;
		for(auto &e: this->getEdgesPtr(u->value, edges)){
		 	if((e->dest)->mark == unexplored){
				//marca v come aperto
		 		(e->dest)->mark = open;
		 		open_node.push(e->dest);						
		 		tree.addNode((e->dest)->value,u->value); //rendi u padre di v in t
		 	}
		}
	}
	return tree;
}

template<class T>
TreePtrList<T>& GraphEdgeList<T>::depthSearch(const T &startValue, TreePtrList<T> &tree) {

    //marcatura di tutti i vertici come inesplorati
    // marco tutti i vertici come inesplorati
    for(auto& e: this->edgeList){
        if(e->src){e->src->mark = unexplored;}
        if(e->dest){e->dest->mark = unexplored;}
    }


   Node<T>* startValuePtr = nodeExistence(startValue);

	//l'albero è formato dal solo vertice da cui partire
	tree.addRoot(startValue);
	startValuePtr->mark = open;

    //inserire il vertice da cui partire nella frontiera (stack)
    std::stack<Node<T>*> open_node;
    open_node.push(startValuePtr);

    while(!open_node.empty()){

        //qui prendo il nodo nella coda
        Node<T> *u = open_node.top(); //return a reference to the last element inserted
        open_node.pop(); 				//remove the first element

        //visita il vertice u
        //typename std::map<T,node<T>*>::iterator u_itr;
        //u_itr = inc_list.find(*u);

        if(u->mark == closed)
            continue;

        u->mark = closed;

        //visita il vertice u (quindi prendo gli archi), prendo la destinazione del vertice u
        std::list<Edge<T>*> edges;
        for(auto &e: this->getEdgesPtr(u->value, edges)){
            auto* v = e->dest;
            if(v->mark == unexplored){
                v->mark = open; 						//marca v come aperto
                open_node.push(v);
                tree.addNode((v->value),(u->value)); //rendi u padre di v in t
                tree.updateParent(v->value,u->value);

            }
            else if((e->dest)->mark == open){
                open_node.push(e->dest);
                tree.updateParent((e->dest)->value,u->value);
            }
        }
    }

	return tree;

}

#endif