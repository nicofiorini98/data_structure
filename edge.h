#ifndef EDGE_H
#define EDGE_H
#include "node.h"


namespace datalib{

    template<class T>
    class edge
    {

    private:
        node<T>* src;
        node<T>* dest;
        int weight;
        std::string mark;
        edge(node<T>* _src,node<T>* _dest,int _weight=0,const std::string _mark="");
    public: 
        ///costructor
        edge(const T *_src,const T *_dest,int _weight=0,const std::string &_mark=""); 
        ///copy costructor
        edge(const edge<T>& _x);
        ~edge(){}

        T getSourceValue() const {return (src->value);}
        T getDestinationValue() const {return (dest->value);}

        friend std::ostream& operator<<(std::ostream &os,const edge<T>& _edge){
            os <<_edge.getSourceValue()<<","<< _edge.getDestinationValue()<<"\n";
            return os;
        }

        template<class U>
        friend class graph_edge_list;
        
        // friend class graph_adj_list;
        // friend class tree_parent_vector;
    };
}

#include "edge.cpp"

#endif