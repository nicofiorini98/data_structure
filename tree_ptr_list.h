#pragma once
#include "tree.h"
#include "node.h"
#include <map>
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

        std::list<node<T>*>& getNodeList(node<T>* _x);
        
        int getNumChildren(node<T>* _x){return _x->node_list.size();}

        //get node by value
        // void getNode(T _value);

    public:


        /// \param _degree Costructor with default parameter,
        /// if degree is not specified, Tree doesn't have a particular degree
        tree_ptr_list(int _degree = -1);

        ///virtual destructor
        ~tree_ptr_list();

        ///overloading operator >>
        //TODO decidere un carattere per il nullo per l'input da file
        friend std::istream &operator>>(std::istream &is, tree_ptr_list<T> &t)
        {
            //pre-conditions
            //format for input of a node: node parent list_children
            //Example: {3 1}, { 1 2 }
            //Example: {a b} {l a}
            // node x{0};
            // node parent{0};

            node<T> *x = new node<T>;
            node<T> *parent = new node<T>;
            //get the value of x and parent
            char tmp;

            //TODO cambiare tipo di stringa per il valore null
            std::string parent_string{""};
            int i = 0;
            while (is >> tmp)
            {
                if (tmp != '{')
                {
                    std::cerr << "errore di lettura\n";
                    is.unget();
                    is.clear(std::ios_base::failbit);
                    return is;
                }

                is >> *x;
                is >> *parent;

                if (!is)
                {
                    is.clear(std::ios_base::goodbit);
                    is >> parent_string;
                    if (parent_string != "null")
                    {
                        is.unget();
                        is.clear(std::ios_base::failbit);
                        std::cerr << "errore lettura2\n";
                        return is;
                    }
                }

                is >> tmp;
                if (is && tmp != '}')
                {
                    std::cerr << "errore di lettura\n";
                    is.unget();
                    is.clear(std::ios_base::failbit);
                    return is;
                }

                if (parent_string == "null")
                {
                    t.addNode(x, nullptr);
                    parent_string = ' ';
                }
                else
                    t.addNode(x, parent);
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
        virtual void addChildren(const T *_x, const std::list<T*> &_children) {} //TODO da rendere virtuale puro
        virtual void addChild(const T *_x, const T* _child) {} //TODO da rendere virtuale puro

        ///print the node following a DFS visit
        void visitDFS(const T* _root);
        ///print the node following BFS visit
        void visitBFS(const T* _root);
        void showTree();
        void showTreePtr();
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
        }
    };
}

#include "tree_ptr_list.cpp"
