#ifndef TREE_POS_VECTOR_H
#define TREE_POS_VECTOR_H
#include "Tree.h"
#include <sstream>
/*
 * Sia T=(N,A), un albero d-ario con n nodi,
 * un vettore posizionale è un array P di dimensione n
 * tale che P[v] contiene l'informazione associata al nodo v,
 * e tale che l'informazione associata all'i-esimo figlio di v è in posizione P[d*v+i]
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
namespace datalib {
template <class T> class TreePosVector : public Tree<T> {
  private:
    /// vector of suitably positioned Nodes
    std::vector<Node<T> *> vecNode;
    Node<T> *root;
    int maxNumNodes;
    int height;

    /// maximum degree of a Node
    int degree;

    // int getNumChildren(Node<T> *value) { return value->num_children; }

    int getPos(Node<T> *value) { return value->pos; }

	//todo controllare parametro passato
    int getMaxChildPos(int posNode,bool isMin);
    
    int getParentPos(int posChild);

    void addChild(const T *value, const T *child);

    void swapPositionValue(int posNode1, int posNode2);

    void addValuesFromVector(const std::vector<T>& values);

    // void addChildren(node<T>* _x,const std::list<T*> &_childrens);

  public:
    /**
     * Default costructor
     * \param _max_degree is the maximum grade of the nodes
     *
     */

    TreePosVector(int maxDegree, int height);

    // TreePosVector(int _max_grade,int _num_nodes);
    virtual ~TreePosVector() {}

    // TODO cambiare degree, al momento non fa la cosa giusta
    /// get Degree of the graph
    int getDegree(const T &value) override;


    /// return a list of Edges of the Tree
    std::list<Edge<T>>& getAllEdges(std::list<Edge<T>>& edges) override;

	int getNumChildren(const T& value);

    T getParent(const T& childValue) override;

    std::list<T> getChildren(const T &parentValue) override; 

    /// addRoot of the Tree
    void addRoot(const T &rootValue) override;

    /// addNode in the Tree
    void addNode(const T &value,const T &parent) override;

    // void addChild(const)
    void addChildren(const T &value, const std::list<T> &children) override;

    // only for debug
    // void showTree() const;

    // void showStructure() const;

    // todo da implementare
    void breadthSearch(const T &startValue) override {}

    // todo da implementare
    void depthSearch(const T &startValue) override {}

    void updateParent(const T &childValue, const T &newParent) override;

    template<class U,class W>
    friend class DHeap;

};

template <class T>
typename std::vector<Node<T>*>::iterator
trova(typename std::vector<Node<T> *>::iterator begin,
      typename std::vector<Node<T> *>::iterator end, const T &value) {

    int i = 0;
    typename std::vector<Node<T> *>::iterator appo;
    for (appo = begin; appo != end; ++appo) {

        // if appo is nullptr, don't check equality, it is certainly
        // different
        if (*appo == nullptr)
            continue;

        if (**appo == value) {
            return appo;
        }
    }
    return end;
}
} // namespace datalib

#include "../sources/TreePosVector.cpp"
#endif