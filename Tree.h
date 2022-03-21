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
        int num_nodes;
    public: 
        ///Costructor
        Tree(){ num_nodes=0;}
        ///virtual destructor
        virtual ~Tree(){}

        /// set Delimiter for the input and output of tree
        void setDelimiter(const char _delimiter){delimiter = _delimiter;}

        ///return the number of nodes of the Tree
        int numNodes(){return num_nodes;}

        ///return the number of sons for the node x
        virtual int getDegree(const T &x)=0;

        ///return the father of the node x
        virtual void getParent(const T &_x,T& _parent)=0;

        ///return a vector with the children of the node x 
        virtual void getChildren(const T &_x, std::list<T>& _list)=0;

        ///add a Node in the Tree 
        virtual void addNode(const T *_x,const T *_parent)=0;

        ///add childrens to node
        virtual void addChildren(const T* _x, const std::list<T*> &_children)=0;

        virtual void depthSearch(const T* _root)=0;

        virtual void breadthSearch(const T* _root)=0;

        virtual void updateParent(const T& _x, const T& _new_parent)=0;

        //aggiungi sotto albero
        //rimuovi sotto albero


        
    };

}



#endif