#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
// #include "edge.h"

//todo togliere il pos nella classe node 
namespace datalib
{

    template<class T>
    class edge;

    template<class T>
    class tree_pos_vector;

    template<class T>
    class node{
    private:
        //only implementation of data structure 
        //can define the parent of a node 
        
        //list of outgoing nodes  
        std::list<node<T>*> node_list;

        //vector for inc_list
        std::vector<edge<T>*> edge_list;

        node<T>* parent; 

        T value;

        //attribute for tree_pos_vector
        int pos;
        int num_children;

        //private constructor 
        node(T _value,node<T>* _parent);

        //utility function for tree_ptr_list
        void addChildren(const std::list<node<T>*>& _children);

    public:
        ///\param _value is for initialize the value 

        node(){}

        node(T _value);

        ~node();
        ///copy costructor
        node(const node<T>& x);

        ///getter  
        T getValue()const {return value;}
        ///setter
        void setValue(T _value) {value=_value;}

        void operator=(const node<T>& x);
        ///overloading operator ==
        bool operator==(const node<T>& x) const;    
        
        ///overloading operator <
        bool operator<(const node<T>& x) const;
        ///overloading operator <=
        bool operator<=(const node<T>& x) const;
        ///overloading operator > 
        bool operator>(const node<T>& x) const;
        ///overloading operator >=
        bool operator>=(const node<T>& x) const;
        ///overloading operator !=
        bool operator!=(const node<T>& x) const;

        ///overloading operator >> 
        friend std::istream& operator>>(std::istream &is, node<T>& _node)
        {
            //make ist throw if it goes bad or fail
            //is.exceptions(is.exceptions()|std::ios_base::badbit);
            //is.exceptions(is.exceptions()|std::ios_base::failbit);
            is >> _node.value;
            return is;
        }

        //TODO Controllare questa funzione
        ///overloading operator <<
        friend std::ostream &operator<<(std::ostream &os,const node<T>& _node)
        {
            os << _node.value;
            return os;
        }

        //class that can access to private member of the node
        // friend class graph_adj_list;
        // friend class tree_pos_vector;
        // friend class tree_parent_vector;

        template<class U> 
        friend class tree_ptr_list;

        template<class U> 
        friend class tree_pos_vector;

        template<class U> 
        friend class graph_adj_list;

        template<class U> 
        friend class edge;
        
        template<class U>
        friend class graph_edge_list;

        template<class U>
        friend class graph_inc_list;

        // template<class S>
        // std::ostream &operator<<(std::ostream &os, tree_pos_vector<S> &t);

    };

    //utility function
    //l'ho fatta perchè io devo vedere se i puntatori sono uguali, 
    template<class T>
    typename std::vector<node<T>*>::iterator trova(typename std::vector<node<T>*>::iterator begin, 
                                                typename std::vector<node<T>*>::iterator end,const T* value)
    {
        int i=0;
        typename std::vector<node<T>*>::iterator appo;
        for(appo = begin ; appo != end; ++appo){

            //if appo is nullptr, don't check equality, it is certainly different
            if(*appo==nullptr)
                continue;

            if(**appo==*value){
                return appo;
            }
        }    
        return end;
    }
}
#include "node.cpp"

#endif