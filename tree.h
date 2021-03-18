#pragma once
#include <vector>
#include <list>
#include "utility.h"


/**
 * \class Tree
 * \brief This class is a base class for various tree implementations
 * 
 * 
 * \author Nico Fiorini
 * \date 03/03/2021
 */

namespace datalib{ 

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
        virtual int getDegree(const node &x)=0;
        ///return the father of the node x
        virtual node getParent(const node &x)=0;
        ///return a vector with the children of the node x 
        virtual std::list<node*> getChildren(const node &x)=0;                     
        ///add a Node in the Tree 
        virtual void addNode(const node *_node,const node *_parent,const std::list<node*> _children)=0;

        //aggiungi sotto albero
        //rimuovi sotto albero
        
    };

}
