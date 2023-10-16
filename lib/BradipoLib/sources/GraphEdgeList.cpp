#ifndef GRAPH_EDGE_LIST_CPP
#define GRAPH_EDGE_LIST_CPP
#pragma once
#include <stdexcept>
#include "GraphEdgeList.h"
using namespace datalib;

// default constructor
template <class T> GraphEdgeList<T>::GraphEdgeList() : Graph<T>() {}

template <class T> GraphEdgeList<T>::~GraphEdgeList() {}

template <class T> void GraphEdgeList<T>::addNode(const T &_x) {

    Node<T> *x_ptr = new Node<T>(_x);
    Edge<T> e(x_ptr, nullptr);
    edgeList.push_back(e);

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

    Node<T> *src_ptr = new Node<T>(srcValue);
    Node<T> *dest_ptr = new Node<T>(destValue);

    Edge<T> e(src_ptr, dest_ptr);

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
        if ((e.src)->value == value && (e.dest) != nullptr)
            _degree++;
    }
    return _degree;
}

template <class T> T GraphEdgeList<T>::getValue(const T &value) const {

    for (auto &e : edgeList) {
        if ((e.dest)->value == value) {
            return (e.dest)->value;
        } else if ((e.src)->value == value) {
            return (e.src)->value;
        }
    }

    throw std::runtime_error(
        "GraphEdgeList::getValue error: the value to get doesn't exists");
}

template <class T>
void GraphEdgeList<T>::setValue(const T &oldValue, const T &newValue) {
    for (auto &e : edgeList) {
        if ((e.dest)->value == oldValue) {
            (e.dest)->value = newValue;
        } else if ((e.src)->value == oldValue) {
            (e.src)->value = newValue;
            (e.src)->value;
        }
    }
}

template <class T>
std::vector<Edge<T>> GraphEdgeList<T>::getIncidentEdge(const T &value) {

    std::vector<Edge<T>> incident_edge;

    for (auto &e : edgeList) {
        if ((e.src)->value == value || (e.dest)->value == value) {
            Edge<T> appo(e);
            incident_edge.push_back(appo);
        }
    }
    return incident_edge;
}

template <class T> void GraphEdgeList<T>::deleteNode(const T &value) {

    typename std::vector<Edge<T>>::iterator i;
    typename std::vector<T> appo;
    for (i = edgeList.begin(); i < edgeList.end(); ++i) {
        if ((i->src)->value == value) {
            edgeList.erase(i);
        } else if ((i->dest))
            edgeList.erase(i);
    }
}

template <class T>
bool GraphEdgeList<T>::edgeExistence(const T &_src, const T &_dest) const {

    for (auto &e : edgeList) {

        if ((e.src)->value == _src && (e.dest)->value == _dest)
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
        if ((e.src)->value == *srcValue && (e.dest)->value == *destValue)
            return true;
    }
    return false;
}

// return true if exists a node _x in the structure
template <class T> bool GraphEdgeList<T>::nodeExistence(const T &x) const {
    for (auto &e : edgeList) {
        if ((e.src)->value == x || (e.dest)->value == x)
            return true;
    }
    return false;
}

template <class T>
bool GraphEdgeList<T>::nodeExistence(const Node<T> &value) const {
    for (auto &e : edgeList) {
        if ((e.src)->value == value.value || (e.dest)->value == value.value)
            return true;
    }
    return false;
}

template <class T>
std::list<Edge<T>> &
GraphEdgeList<T>::getAllEdges(std::list<Edge<T>> &edges) const {

    edges.clear();
    for (auto &e : this->edgeList) {
        edges.push_back(e);
    }
    return edges;
}

template <class T>
std::list<Edge<T>> &
GraphEdgeList<T>::getIncidentEdges(const T &value, std::list<Edge<T>> &edges) {
    // posso ritornare direttamente una lista degli archi che stanno in edgeList
    for (auto &e : edgeList) {
        if ((e.dest)->value == value || (e.src)->value == value)
            edges.push_back(e);
    }
    return edges;
}

template <class T>
std::list<Edge<T>> &
GraphEdgeList<T>::getOutgoingEdges(const T &value, std::list<Edge<T>> &edges) {
    for (auto &e : edgeList) {
        if ((e.src)->value == value) {
            edges.push_back(e);
        }
    }
    return edges;
}

template <class T>
std::list<Edge<T>> &
GraphEdgeList<T>::getIncomingEdges(const T &value, std::list<Edge<T>> &edges) {
    for (auto &e : edgeList) {
        if ((e.dest)->value == value) {
            edges.push_back(e);
        }
    }
    return edges;
}

template <class T>
bool GraphEdgeList<T>::isAdjacent(const T &srcValue, const T &destValue) {
    return false;
}

#endif