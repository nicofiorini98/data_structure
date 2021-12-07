#pragma once
#include <vector>
#include <list>
#include "node.h"
#include "edge.h"

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
    class tree {
    protected:
        int num_nodes;
    public: 
        ///Costructor
        tree(){num_nodes=0;}
        ///virtual destructor
        virtual ~tree(){}

        ///return the number of nodes of the Tree 
        virtual int numNodes(){return num_nodes;}
        ///return the number of sons for the node x
        // virtual int getDegree(const node<T> &x)=0;
        virtual int getDegree(const T &x)=0;
        ///return the father of the node x
        // virtual node<T> getParent(const node<T> &x)=0;
        virtual T getParent(const T &_x)=0;
        ///return a vector with the children of the node x 
        //TODO vedere se conviene restituire un reference
        virtual std::list<T>& getChildren(const T &_x)=0;                     
        ///add a Node in the Tree 
        virtual void addNode(const T *_x,const T *_parent)=0;
        ///add childrens to node
        virtual void addChildren(const T* _x, const std::list<T*> &_children)=0;
        virtual void addChild(const T* _x, const T* _children)=0;

        //aggiungi sotto albero
        //rimuovi sotto albero
        
    };

}
