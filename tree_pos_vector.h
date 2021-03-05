#include "tree.h"

/*
 * Sia T=(N,A), un albero d-ario con n nodi, 
 * un bettore posizionale è un array P di dimensione n 
 * tale che P[v] contiene l'informazione associata al nodo v,
 * e tale che l'informazione associata all'i-esimo di v è in posizione P[d*v+i]  
 * per 0<i<d-1     
 */
/**
 * \class TreePosVector
 * \brief Is a Tree data structure implemented with vector positions
 * 
 * \author Nico Fiorini
 * \date 02/03/2021
 */
namespace datalib{

    class tree_pos_vector: public tree{
    private: 

        ///vector of suitably positioned Nodes
        std::vector<node*> vec_node;

        ///maximum grade of a Node  
        int max_degree;

    public: 

        /**
         * Default costructor 
         * \param _max_degree is the maximum grade of the nodes
         */
        
        tree_pos_vector(int _max_degree,int _num_nodes);

        //TreePosVector(int _max_grade,int _num_nodes);
        virtual ~tree_pos_vector(){}

        int getDegree(const node &x){}
        node* getParent(const node &x){}
        std::vector<node*> getChildren(){} 
        void addNode(const node *_node,const node *_parent);

    };


}