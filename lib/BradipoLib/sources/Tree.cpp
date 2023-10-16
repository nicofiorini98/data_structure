#ifndef TREE_CPP
#define TREE_CPP
#pragma once
#include "Tree.h"

template <class T>
std::list<T> &Tree<T>::breadthSearch(std::list<T> &values) const {

    values.clear();
    // initialize queque
    std::queue<Node<T> *> queue;

    queue.push(this->root);
    while (!queue.empty()) {
        Node<T> *u = queue.front();
		
		// pop don't return the value
        queue.pop(); 

        // push the node in the values to return
        values.push_back(u->value);

        if (true) {
            // visit u
            std::list<T> lista_childrens;
            lista_childrens = this->getChildren(u->value);

            typename std::list<T>::iterator itr;
            // se la lista è vuota non devo aggiungere niente allo stack
            if (lista_childrens.empty())
                u = nullptr;
            else {

                for (auto child_itr = (lista_childrens.begin());
                     child_itr != lista_childrens.end(); ++child_itr) {
                    Node<T> *appo = new Node<T>(*child_itr);
                    queue.push(appo);
                }
            }
        }
    }
    return values;
}

template <class T>
std::list<T> &Tree<T>::depthSearch(std::list<T> &values) const {
    values.clear();

    // initialize for stack
    std::stack<Node<T> *> stack;

    stack.push(this->root); // 2 s.push(root)
    while (!stack.empty()) {
        Node<T> *u = stack.top();
        // pop don't return the value
        stack.pop();

        // push the node in the values to return
        values.push_back(u->value);

        if (true) {
            // visit u
            std::list<T> lista_childrens;
            lista_childrens = this->getChildren(u->value);

            typename std::list<T *>::iterator itr;
            // se la lista è vuota non devo aggiungere niente allo stack
            if (lista_childrens.empty())
                u = nullptr;
            else {

                for (auto child_itr = (lista_childrens.rbegin());
                     child_itr != lista_childrens.rend(); ++child_itr) {
                    Node<T> *appo = new Node<T>((*child_itr));
                    stack.push(appo);
                }
            }
        }
    }
    return values;
}

template<class T>
std::ostream &Tree<T>::outputDotFile(std::ostream &dotFile)const {
	dotFile<<"digraph Tree {";
	std::list<Edge<T>> edges;
	for(auto& e: this->getAllEdges(edges)){
		dotFile<<e.getSourceValue()<<"->"<<e.getDestinationValue()<<"\n";
	}
	dotFile<<"}";
	return dotFile;
}

#endif