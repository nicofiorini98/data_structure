#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>


//todo togliere il pos nella classe node
namespace slothLib
{
    /// utility for searches
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
        
        /// The node's values goes in here
        T value;

        /// utility for breadthSearch and depthSearch
        marking mark = unexplored;

        ///list of outgoing nodes, used for treePtrList
        std::list<Node<T>*> node_list;

        /// vector for inc_list
        std::list<Edge<T>*> connected_edges;
        Node<T>* parent;


        /// attribute utility for TreePosVector
        int pos;
        
        int num_children;

        //private constructor
        Node(T value, Node<T>* parent);

        //utility function for TreePtrList
        void addChildren(const std::list<Node<T>*>& _children);

    public:

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
            is >> node.value;
            return is;
        }

        ///overloading operator <<
        friend std::ostream &operator<<(std::ostream &os,const Node<T>& node)
        {
            os << node.value;
            return os;
        }

        template<class U>
        friend class BasicGraph;

        template<class U>
        friend class Graph;

        template<class U>
        friend class Tree;

        template<class U>
        friend class TreePtrList;

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

        template<class U,class W>
        friend class DHeap;

    };
}
#include "../sources/Node.cpp"

#endif
