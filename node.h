#pragma once 

#include <iostream>
#include <list>

//todo togliere il pos nella classe node 
namespace datalib
{
    class node
    {
    private:
        //only implementation of data structure 
        //can define the parent of a node 
        
        //list of outgoing nodes  
        std::list<node*> node_list;

        //parameter only for the Tree
        node* parent; 

        int value;
        int pos;
        void addChildren(std::list<node*>&& _children);

    public:

        ///\param _value is for initialize the value 
        ///\param _type define the type of the node
        node(int _value,node* _parent=nullptr);
        ///copy costructor
        node(const node& x);
        //getter  
        int getValue()const {return value;}
        ///setter
        void setValue(int _value) {value=_value;}

        ///overloading operator ==
        bool operator==(const node& x) const;    
        ///overloading operator <
        bool operator<(const node& x) const;
        ///overloading operator <=
        bool operator<=(const node& x) const;
        ///overloading operator > 
        bool operator>(const node& x) const;
        ///overloading operator >=
        bool operator>=(const node& x) const;
        ///overloading operator !=
        bool operator!=(const node& x) const;

        ///overloading operator >> 
        friend std::istream& operator>>(std::istream &is, node &_node)
        {
            //make ist throw if it goes bad or fail
            //is.exceptions(is.exceptions()|std::ios_base::badbit);
            //is.exceptions(is.exceptions()|std::ios_base::failbit);
            is >> _node.value;
            return is;
        }

        //todo controllare questa funzione
        ///overloading operator <<
        friend std::ostream &operator<<(std::ostream &os, node &_node)
        {
            os << _node.value;
            return os;
        }


        //class that can access to private member of the node
        friend class graph_adj_list;
        friend class tree_pos_vector;
        friend class tree_parent_vector;
        friend class tree_general;
    };
}


