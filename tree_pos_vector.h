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
        int max_num_nodes;
        int height;
        ///maximum grade of a Node  
        int degree;
        int getNumChildren(node<T>* _x){return _x->num_children;}
        int getPos(node<T>* _x){return _x->pos;}

        // void addChildrens(node<T>* _x,const std::list<T*> &_childrens);

    public: 

        /**
         * Default costructor
         * \param _max_degree is the maximum grade of the nodes
         */
        
        tree_pos_vector(int degree, int _height);

        //TreePosVector(int _max_grade,int _num_nodes);
        virtual ~tree_pos_vector(){}

        int getDegree(const T &x){}
        T getParent(const T &x){}
        std::list<T>& getChildren(const T &x){} 
        //void addNode2(const node<T> *_x,const node<T> *_parent=nullptr);

        void addNode(const T *_x,const T* _parent=nullptr); //da togliere se non serve il const 

        void addChild(const T* _x,const T* _child);
        void addChildren(const T* _x, const std::list<T*> &_children);
        // void addChildrens(node<T>* _x, const std::list<node<T>*> &_childrens);
        // void addChildrens2(node<T>* _x, const std::list<node<T>*> &_childrens);

        //only for debug 
        void showTree();
        void showTree2();

        friend std::istream &operator>>(std::istream &is, tree_pos_vector<T> &t){

        }
        friend std::ostream &operator<<(std::ostream &os, tree_pos_vector<T> &t){
            //pre-conditions
            //format for input of a node: node parent list_children
            //Example: ( l a )
            //Example: (a b) (l a)

            // os<<"\n\n Stampa di Tree_pos_vector: \n";
            for(auto &n: t.vec_node){
                //don't consider nullptr as node
                if(!n) 
                    continue;

                for(int i = 0; i < t.getNumChildren(n); i++){
                    if(i!=0)
                        os<<" ";
                    os<<"( "<< *n <<" "<< *(t.vec_node[(t.getPos(n)*(t.degree))+i]) <<" )";
                }
                os<<"\n";
            }
            return os;
        }
    };
}

#include "tree_pos_vector.cpp"