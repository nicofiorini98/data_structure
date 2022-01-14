#ifndef TREE_PTR_LIST_H
#define TREE_PTR_LIST_H
#include <iostream>
#include <fstream>
#include <sstream>
#include "tree.h"
#include "node.h"
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
    class tree_ptr_list: tree<T>
    {
    private:
        int degree;
        node<T> *root;

        std::map<T,node<T>*> nodes_map;
        std::list<node<T>*>& getNodeList(node<T>* _x); //todo vedere se serve
        
        int getNumChildren(node<T>* _x){return _x->node_list.size();}

        //get node by value
        // void getNode(T _value);

    public:


        /// \param _degree Costructor with default parameter,
        /// if degree is not specified, Tree doesn't have a particular degree
        tree_ptr_list(int _degree=4);

        ///virtual destructor
        ~tree_ptr_list();

        ///overloading operator >>
        //TODO decidere un carattere per il nullo per l'input da file
        friend std::istream &operator>>(std::istream &is, tree_ptr_list<T> &t)
        {
            //pre-conditions
            //the input work with csv format --> node2add, parent
            //example with string:
            //
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
                //todo vedere se conviene utilizzare un carattere delimitatore
                if (parent_string.empty())                
                {
                    t.addNode(x, nullptr);
                    continue;
                }

				std::stringstream str2(parent_string);                 //
                str2 >> *parent;
            	t.addNode(x,parent);
            }

            return is;
        }

       //friend std::ostream &operator<<(std::ostream &is, tree_ptr_list<T> &t);

        ///return the number of sons for the node x
        int getDegree(const T &_x);
        ///return the parent of the node x
        T getParent(const T &_x);

        ///return a vector of the node x
        std::list<T>& getChildren(const T &_x);

        ///add a node in the Tree
        ///\param _node is the node to add in the Tree
        ///\param _father is the parent of the node to be inserted,
        ///if not specified the node is the root of the Tree
        //void addNode2(const node<T> *_x, const node<T> *_parent = nullptr, const std::list<node<T>> _children = {}); //TODO
        void addNode(const T *_x,const T *_parent = nullptr);
        virtual void addChildren(const T *_x, const std::list<T*> &_children) {}

        void addChild(const T *_x, const T* _child);
        ///print the node following a DFS visit
        void visitDFS(const T* _root);
        ///print the node following BFS visit
        void visitBFS(const T* _root);  // todo da fare
        void showTree();
        void showTreePtr();
        void showStructure();
        void showTree2();
        //aggiungi sotto albero
        //rimuovi sotto albero
        friend std::ostream& operator<<(std::ostream& os,tree_ptr_list<T> t) {

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

#include "tree_ptr_list.cpp"
#endif