#pragma once
#include "tree.h"

/*
 * Sia T=(N,A), un albero d-ario con n nodi, 
 * un bettore posizionale è un array P di dimensione n 
 * tale che P[v] contiene l'informazione associata al nodo v,
 * e tale che l'informazione associata all'i-esimo di v è in posizione P[d*v+i]  
 * per 0<i<d-1     
 * 
 * Per comodità l'indice 0 lo posso lascia perde. 
 */
/**
 * \class TreePosVector
 * \brief Is a Tree data structure implemented with vector positions
 * 
 * \author Nico Fiorini
 * \date 02/03/2021
 */
namespace datalib
{
    template<class T>
    class tree_pos_vector: public tree<T>
    {
    private: 
        ///vector of suitably positioned Nodes
        std::vector<node<T>*> vec_node;
        node<T>* root;
        ///maximum grade of a Node  
        int degree;


    public: 

        /**
         * Default costructor
         * \param _max_degree is the maximum grade of the nodes
         */
        
        tree_pos_vector(int _max_degree, int _num_nodes);

        //TreePosVector(int _max_grade,int _num_nodes);
        virtual ~tree_pos_vector(){}

        int getDegree(const node<T> &x){}
        node<T> getParent(const node<T> &x){}
        std::list<node<T>*> getChildren(const node<T> &x){} 
        void addNode(const node<T> *_x,const node<T> *_parent=nullptr);
        void addChildrens(const node<T>* _x, const std::list<node<T>*> &_childrens);
        void showTree();

    };
}

#include "tree_pos_vector.cpp"