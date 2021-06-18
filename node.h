#pragma once
#include <iostream>
#include <list>

//todo togliere il pos nella classe node 
namespace datalib
{
    template<class T>
    class node
    {
    private:
        //only implementation of data structure 
        //can define the parent of a node 
        
        //list of outgoing nodes  
        std::list<node<T>*> node_list;

        // //parameter only for the Tree
        node<T>* parent; 

        T value;
        int pos;
        int num_children;
        // int max_children;

        //private constructor 
        node(T _value,node<T>* _parent);
        void addChildren(std::list<node<T>*>&& _children);

    public:
        ///\param _value is for initialize the value 

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
        friend class tree_general;
        template<class W> 
        friend class tree_pos_vector;


    };

}

#include "node.cpp"



















    
    // class node2
    // {
    // private:
    //     //only implementation of data structure 
    //     //can define the parent of a node 
        
    //     //list of outgoing nodes  
    //     std::list<node2*> node_list;
    
    //     //parameter only for the Tree
    //     node2* parent; 

    //     int value;
    //     int pos;

    //     void addChildren(std::list<node2*>&& _children);

    // public:

    //     ///\param _value is for initialize the value 
    //     ///\param _type define the type of the node
    //     node2(int _value,node2* _parent=nullptr);
    //     ///copy costructor
    //     node2(const node2& x);
    //     //getter  
    //     int getValue()const {return value;}
    //     ///setter
    //     void setValue(int _value) {value=_value;}

    //     void operator=(const node2& x);
    //     ///overloading operator ==
    //     bool operator==(const node2& x) const;    
    //     ///overloading operator <
    //     bool operator<(const node2& x) const;
    //     ///overloading operator <=
    //     bool operator<=(const node2& x) const;
    //     ///overloading operator > 
    //     bool operator>(const node2& x) const;
    //     ///overloading operator >=
    //     bool operator>=(const node2& x) const;
    //     ///overloading operator !=
    //     bool operator!=(const node2& x) const;

    //     ///overloading operator >> 
    //     friend std::istream& operator>>(std::istream &is, node2 &_node)
    //     {
    //         //make ist throw if it goes bad or fail
    //         //is.exceptions(is.exceptions()|std::ios_base::badbit);
    //         //is.exceptions(is.exceptions()|std::ios_base::failbit);
    //         is >> _node.value;
    //         return is;
    //     }

    //     //todo controllare questa funzione
    //     ///overloading operator <<
    //     friend std::ostream &operator<<(std::ostream &os,const node2 &_node)
    //     {
    //         os << _node.value;
    //         return os;
    //     }

    //     //class that can access to private member of the node
    //     friend class graph_adj_list;
    //     friend class tree_pos_vector;
    //     friend class tree_parent_vector;
    //     friend class tree_general;
    // };
//}



