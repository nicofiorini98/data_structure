#ifndef EDGE_H
#define EDGE_H
#include "Node.h"


namespace datalib{

    template<class T>
    class Edge
    {

    private:
        Node<T>* src;
        Node<T>* dest;
        int weight;
        std::string mark;
        Edge(Node<T>* _src, Node<T>* _dest, int _weight=0, const std::string _mark="");
        
    public:
        ///costructor
        Edge(const T *_src, const T *_dest, int _weight=0, const std::string &_mark="");
        ///copy costructor
        Edge(const Edge<T>& _x);
        ~Edge(){}

        T getSourceValue() const {return (src->value);}
        T getDestinationValue() const {return (dest->value);}

        friend std::ostream& operator<<(std::ostream &os,const Edge<T>& _edge){
            os <<_edge.getSourceValue()<<","<< _edge.getDestinationValue()<<"\n";
            return os;
        }

        //todo ripristinare
        template<class U>
        friend class GraphEdgeList;

        //todo ripristinare
        template<class W>
        friend class GraphIncList;
        
        // friend class GraphAdjList;
        // friend class tree_parent_vector;
    };
}

#include "../sources/Edge.cpp"

#endif