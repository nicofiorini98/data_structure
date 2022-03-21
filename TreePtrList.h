#ifndef TREE_PTR_LIST_H
#define TREE_PTR_LIST_H
#include <iostream>
//#include <fstream>
#include <sstream>
#include "Tree.h"
#include "Node.h"
#include <map>
#include <stack>

/**
 * \class Tree
 * \brief This class is a base class for various tree implementations
 * 
 * 
 * \author Nico Fiorini
 * \date 03/03/2021
 * 
 * manage the nullptr for the root and the leafs
*/
namespace datalib{
    template<class T>
    class TreePtrList: public Tree<T>
    {
    private:
        int degree;
        Node<T> *root;

        std::map<T,Node<T>*> nodes_map;
        std::list<Node<T>*>& getNodeList(Node<T>* _x); //todo vedere se serve
        
        int getNumChildren(Node<T>* _x){return _x->node_list.size();}
        Node<T>* getNode(const T _x);

        //get node by value
        // void getNode(T _value);

    public:


        /// \param _degree Costructor with default parameter,
        /// if degree is not specified, Tree doesn't have a particular degree
        TreePtrList(int _degree=4);

        ///virtual destructor
        ~TreePtrList();

        //friend std::ostream &operator<<(std::ostream &is, TreePtrList<T> &t);
        ///return the number of sons for the node x
        int getDegree(const T &_x) override;

        ///return the parent of the node x
        void getParent(const T& _x, T& _parent) override;

        ///return a vector of the node x
        void getChildren(const T &_x,std::list<T>& _list);

        ///add a node in the Tree
        ///\param _node is the node to add in the Tree
        ///\param _father is the parent of the node to be inserted,
        ///if not specified the node is the root of the Tree
        void addNode(const T *_x,const T *_parent = nullptr) override;

        //add children to node _x
        void addChildren(const T *_x, const std::list<T*> &_children) override;

        //void removeChild(const T& _x);

        ///print the node following a DFS visit
        void depthSearch(const T* _root) override;

        ///print the node following BFS visit
        void breadthSearch(const T* _root) override;

        void updateParent(const T& _x,const  T& _new_parent);

        void showTree();

        void showTreePtr();

        void showStructure();

        void showTree2();
        //aggiungi sotto albero
        //rimuovi sotto albero

        ///overloading operator >>
        friend std::istream &operator>>(std::istream &is, TreePtrList<T> &t)
        {
            //pre-conditions
            //the input work with csv format --> node2add, parent
            //example with string:
            //a
            //a,l

            //se il padre non è fornito, il nodo è la radice
            std::string line,x_string,parent_string;

            //read line-by-line
            while (std::getline(is, line)) {

                auto *x = new T;
                auto *parent = new T;

                std::stringstream str(line);                           //converte la riga in uno stream
                std::getline(str, x_string, t.delimiter);              //leggo lo stream della riga fino al carattere delimitatore
                std::stringstream str1(x_string);                      // converte il primo campo in uno stream
                str1 >> *x;                                            //viene utilizzata la funzione >> per l'input del primo campo

                std::getline(str, parent_string, t.delimiter);         //continuo a leggere per trovare il secondo campo
                if (parent_string.empty()){
                    t.addNode(x, nullptr);
                    continue;
                }

                std::stringstream str2(parent_string);
                str2 >> *parent;
                t.addNode(x,parent);
            }
            return is;
        }

        friend std::ostream& operator<<(std::ostream& os, TreePtrList<T> t) {

            for(auto &n: t.nodes_map){
                for(auto &child: t.getNodeList(n.second)){
                    os<<"( "<< *(n.second) << " " << *child <<" )"<<"\n";
                }
                // for(int i=0; i < t.getNumChildren(n.second);i++ )
            }
            return os;
        }
    };
}

#include "TreePtrList.cpp"
#endif