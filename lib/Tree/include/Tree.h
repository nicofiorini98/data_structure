#ifndef TREE_H
#define TREE_H

#include <vector>
#include <list>
#include "Node.h"
#include "Edge.h"

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
    class Tree {
    protected:
        char delimiter = ',';
        int numNodes;
    public: 

        ///Costructor
        Tree(){ numNodes=0;}

        ///virtual destructor
        virtual ~Tree(){}

        /// set Delimiter for the input and output of tree
        void setDelimiter(const char delimiter){this->delimiter = delimiter;}

        ///return the number of nodes of the Tree
        int getNumNodes(){return numNodes;}

        ///return the number of sons for the node x
        virtual int getDegree(const T &value)=0;

        ///return the father of the node x
        virtual void getParent(const T &value,T& parent)=0;

        ///return a vector with the children of the node x 
        virtual void getChildren(const T &value, std::list<T>& children)=0;

        ///add a Node in the Tree 
        virtual void addNode(const T *value,const T *parent)=0;

        ///add childrens to node
        virtual void addChildren(const T& value, const std::list<T>& children)=0;

        virtual void depthSearch(const T* root)=0;

        virtual void breadthSearch(const T* root)=0;

        virtual void updateParent(const T& child, const T& newParent)=0;

        ///overloading operator >>
        /*friend std::istream &operator>>(std::istream &is, Tree<T> &t)
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
        */

        //aggiungi sotto albero
        //rimuovi sotto albero

    };

}

#endif