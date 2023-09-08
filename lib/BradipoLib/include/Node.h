#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
// #include "city.h"

// #include "edge.h"

//todo togliere il pos nella classe node
namespace datalib
{
    enum marking {unexplored,open,closed};

    template<class T>
    class Edge;

    template<class T>
    class TreePosVector;

    template<class T>
    class Node{
    private:
        //only implementation of data structure
        //can define the parent of a node

        marking mark = unexplored;

        //list of outgoing nodes, used for treePtrList
        std::list<Node<T>*> node_list;

        //vector for inc_list
        std::list<Edge<T>*> connected_edges;
        Node<T>* parent;

        T value;

        //attribute for tree_pos_vector
        int pos;
        int num_children;

        //private constructor
        Node(T _value, Node<T>* _parent);

        //utility function for TreePtrList
        void addChildren(const std::list<Node<T>*>& _children);

    public:
        ///\param _value is for initialize the value

        Node(){}

        Node(T _value);

        ~Node();
        ///copy costructor
        Node(const Node<T>& x);

        ///getter
        T getValue()const {return value;}
        ///setter
        void setValue(T _value) {value=_value;}

        //todo controllare
        Node<T>& operator=(const Node<T>& x);
        ///overloading operator ==
        bool operator==(const Node<T>& x) const;

        ///overloading operator <
        bool operator<(const Node<T>& x) const;
        ///overloading operator <=
        bool operator<=(const Node<T>& x) const;
        ///overloading operator >
        bool operator>(const Node<T>& x) const;
        ///overloading operator >=
        bool operator>=(const Node<T>& x) const;
        ///overloading operator !=
        bool operator!=(const Node<T>& x) const;

        ///overloading operator >>
        friend std::istream& operator>>(std::istream &is, Node<T>& _node)
        {
            //make ist throw if it goes bad or fail
            //is.exceptions(is.exceptions()|std::ios_base::badbit);
            //is.exceptions(is.exceptions()|std::ios_base::failbit);
            is >> _node.value;
            return is;
        }

        //TODO Controllare questa funzione
        ///overloading operator <<
        friend std::ostream &operator<<(std::ostream &os,const Node<T>& _node)
        {
            os << _node.value;
            return os;
        }

        //class that can access to private member of the node
        // friend class GraphAdjList;
        // friend class tree_pos_vector;
        // friend class tree_parent_vector;

        template<class U>
        friend class TreePtrList;

        //todo ripristinare

        template<class U>
        friend class TreePosVector;

        template<class U>
        friend class GraphAdjList;

        template<class U>
        friend class Edge;

        template<class U>
        friend class GraphEdgeList;

        template<class U>
        friend class GraphIncList;

        template<class U>
        friend class DHeap;
        // template<class S>
        // std::ostream &operator<<(std::ostream &os, tree_pos_vector<S> &t);

    };

    //utility function
    //l'ho fatta perchè io devo vedere se i puntatori sono uguali
    // template<class T>
    // typename std::vector<Node<T>*>::iterator trova(typename std::vector<Node<T>*>::iterator begin,
    //                                                typename std::vector<Node<T>*>::iterator end, const T* value)
    // {
    //     int i=0;
    //     typename std::vector<Node<T>*>::iterator appo;
    //     for(appo = begin ; appo != end; ++appo){

    //         //if appo is nullptr, don't check equality, it is certainly different
    //         if(*appo==nullptr)
    //             continue;

    //         if(**appo==*value){
    //             return appo;
    //         }
    //     }
    //     return end;
    // }
}
#include "../sources/Node.cpp"

#endif
