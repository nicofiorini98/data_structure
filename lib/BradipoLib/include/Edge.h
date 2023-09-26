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
        Edge(Node<T>* src, Node<T>* dest, int weight=0, const std::string mark="");
        
    public:
        /// public costructor
        Edge(const T *_src, const T *_dest, int _weight=0, const std::string &_mark="");
        
        ///copy costructor
        Edge(const Edge<T>& _x);
        
        // Destructor
        ~Edge(){}

        /// get the src Value
        T getSourceValue() const {return (src->value);}
        
        //get dest Value
        T getDestinationValue() const {return (dest->value);}

        friend std::ostream& operator<<(std::ostream &os,const Edge<T>& edge){
            os <<edge.getSourceValue()<<","<< edge.getDestinationValue()<<"\n";
            return os;
        }

        template<class U>
        friend class GraphEdgeList;

        template<class U>
        friend class GraphIncList;
        
    };
}

#include "../sources/Edge.cpp"

#endif