#ifndef TREE_H
#define TREE_H

#include <vector>
#include <list>
#include "Node.h"
#include "Edge.h"

/**
 * \class Tree
 * \brief This class is a base class for various tree implementations
 * 
 * 
 * \author Nico Fiorini
 * \date 03/03/2021
 */

namespace datalib{ 

    template<class T>
    class Tree {
    protected:
        char delimiter = ',';
        int numNodes;
    public: 

        ///Costructor
        Tree(){ numNodes = 0;}


        ///virtual destructor
        virtual ~Tree(){}

        /// set Delimiter for the input and output of tree
        void setDelimiter(const char delimiter){this->delimiter = delimiter;}

        ///return the number of nodes of the Tree
        int getNumNodes() const {return numNodes;}

        ///return the number of sons for the node x
        virtual int getDegree (const T &value) = 0;

        ///return the father of the node childValue
        virtual T getParent(const T& childValue)=0;

        ///return a list with the children of the node parentValue
        virtual std::list<T> getChildren(const T& parentValue)=0;

		/// add root in the Tree
        virtual void addRoot(const T& rootValue)=0;

        ///add a Node in the Tree 
        virtual void addNode(const T& value,const T& parent)=0;

        ///add childrens to node value
        virtual void addChildren(const T& value, const std::list<T>& children)=0;

		//TODO implementare in un esempio
        virtual void depthSearch(const T& startValue)=0;

		//TODO implementare in un esempio
        virtual void breadthSearch(const T& startValue)=0;

		//fondamentale per la ricerca
        
        virtual void updateParent(const T& childValue, const T& newParent)=0;


    };
}

#endif