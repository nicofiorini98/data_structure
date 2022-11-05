#ifndef TREE_POS_VECTOR_H
#define TREE_POS_VECTOR_H
#include "Tree.h"

/*
 * Sia T=(N,A), un albero d-ario con n nodi, 
 * un vettore posizionale è un array P di dimensione n
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
    class TreePosVector: public Tree<T>
    {
    private: 
        ///vector of suitably positioned Nodes
        std::vector<Node<T>*> vec_node;  //todo si può trasformare in un array visto che le dimensione sono fisse
        Node<T>* root;
        int max_num_nodes;
        int height;
        ///maximum grade of a Node  
        int degree;
        int getNumChildren(Node<T>* _x){return _x->num_children;}
        int getPos(Node<T>* _x){return _x->pos;}

        void addChild(const T* _x,const T* _child);

        // void addChildrens(node<T>* _x,const std::list<T*> &_childrens);

    public: 

        /**
         * Default costructor
         * \param _max_degree is the maximum grade of the nodes
         *
         */
        
        TreePosVector(int degree, int _height);

        //TreePosVector(int _max_grade,int _num_nodes);
        virtual ~TreePosVector(){}

        int getDegree(const T& _x) override { return 0; }
        void getParent(const T &_x,T& _parent) override{}
        
       void getChildren(const T &x, std::list<T>& _list)override{}
        //void addNode2(const node<T> *_x,const node<T> *_parent=nullptr);

        void addNode(const T *_x,const T* _parent=nullptr) override; //da togliere se non serve il const 

        //void addChild(const)
        void addChildren(const T& _x, const std::list<T>& _children) override;
        // void addChildrens(node<T>* _x, const std::list<node<T>*> &_childrens);
        // void addChildrens2(node<T>* _x, const std::list<node<T>*> &_childrens);

        //only for debug 
        void showTree();
        void showTree2();

        void breadthSearch(const T* _root)override{}
        void depthSearch(const T* _root)override{}

        void updateParent(const T& _x, const T& _new_parent)override{}
        friend std::istream &operator>>(std::istream &is, TreePosVector<T> &t){
            return is;
        }

        friend std::ostream &operator<<(std::ostream &os, TreePosVector<T> &t){
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

#include "TreePosVector.cpp"
#endif