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

    int getNumChildren(Node<T> *value) { return value->num_children; }

    int getPos(Node<T> *value) { return value->pos; }

	//todo controllare parametro passato
    int getMaxChildPos(Node<T>* value);
    
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

    int getDegree(const T &value) override;

    //TODO vedere se conviene metterlo al posto di getDegree
	int getNumChildren(const T& value);

    T getParent(const T& childValue) override;

    std::list<T> getChildren(const T &parentValue) override; 
    // void addNode2(const node<T> *_x,const node<T> *_parent=nullptr);

    /// addRoot of the Tree
    void addRoot(const T &rootValue) override;

    void addNode(const T &value,
                 const T &parent) override; // da togliere se non serve il const

    // void addChild(const)
    void addChildren(const T &value, const std::list<T> &children) override;
    // void addChildrens(node<T>* _x, const std::list<node<T>*> &_childrens);
    // void addChildrens2(node<T>* _x, const std::list<node<T>*> &_childrens);

    // only for debug
    void showTree() const;

    void showStructure() const;

    // todo da implementare
    void breadthSearch(const T &startValue) override {}

    // todo da implementare
    void depthSearch(const T &startValue) override {}

    void updateParent(const T &childValue, const T &newParent) override;

    template<class U>
    friend class DHeap;


    /// overloading operator >>
    friend std::istream &operator>>(std::istream &is, TreePosVector<T> &tree) {
        // pre-conditions
        // the input work with csv format --> node2add, parent
        // example with string:
        // a
        // a,l
        // se il padre non è fornito, il nodo è la radice
        std::string line, x_string, parent_string;

        // read line-by-line
        while (std::getline(is, line)) {

            auto *x = new T;
            auto *parent = new T;

            std::stringstream str(line); // converte la riga in uno stream

            // leggo lo stream della riga fino al carattere delimitatore
            std::getline(str, x_string,tree.delimiter); 

            std::stringstream str1(x_string); 
            // converte il primo campo in uno stream

            str1 >> *x; // viene utilizzata la funzione >> per l'input del primo
                        // campo
            std::getline(str, parent_string,
                         tree.delimiter); // continuo a leggere per trovare il
                                          // secondo campo

            if (parent_string.empty()) {
                tree.addRoot(*x);
                continue;
            }

            std::stringstream str2(parent_string);
            str2 >> *parent;
            tree.addNode(*x, *parent);

            // deallocate x and parent to avoid memory leak
            delete x;
            delete parent;
        }
        return is;
    }

    friend std::ostream &operator<<(std::ostream &os, TreePosVector<T> &t) {
        // pre-conditions
        // format for input of a node: node parent list_children
        // Example: ( l a )
        // Example: (a b) (l a)

        // os<<"\n\n Stampa di Tree_pos_vector: \n";
        for (auto &n : t.vec_node) {
            // don't consider nullptr as node
            if (!n)
                continue;

            for (int i = 0; i < t.getNumChildren(n); i++) {
                if (i != 0)
                    os << " ";
                os << "( " << *n << " "
                   << *(t.vec_node[(t.getPos(n) * (t.degree)) + i]) << " )";
            }
            os << "\n";
        }
        return os;
    }
};

template <class T>
typename std::vector<Node<T> *>::iterator
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