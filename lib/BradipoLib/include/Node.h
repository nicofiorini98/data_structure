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
        //TODO change name in nodeList
        std::list<Node<T>*> node_list;

        //vector for inc_list
        //TODO change name in connectedEdges
        std::list<Edge<T>*> connected_edges;
        Node<T>* parent;

        T value;

        //attribute for tree_pos_vector
        int pos;
        
        //TODO vedere se si può togliere
        int num_children;

        //private constructor
        Node(T value, Node<T>* parent);

        //utility function for TreePtrList
        void addChildren(const std::list<Node<T>*>& _children);

    public:
        ///\param value is for initialize the value

        Node(){}

        Node(T value);

        ~Node();
        
        ///copy costructor
        Node(const Node<T>& x);

        ///getter
        T getValue()const {return value;}
        
        ///setter
        void setValue(T value) {this->value = value;}

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
        friend std::istream& operator>>(std::istream &is, Node<T>& node)
        {
            //make ist throw if it goes bad or fail
            //is.exceptions(is.exceptions()|std::ios_base::badbit);
            //is.exceptions(is.exceptions()|std::ios_base::failbit);
            is >> node.value;
            return is;
        }

        //TODO Controllare questa funzione
        ///overloading operator <<
        friend std::ostream &operator<<(std::ostream &os,const Node<T>& node)
        {
            os << node.value;
            return os;
        }

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

    };
}
#include "../sources/Node.cpp"

#endif
