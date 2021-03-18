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
        node(int _value, node* _parent){
            value=_value;
            pos=-1;
            parent=_parent;
            node_list={};
        } 
        //list of outgoing nodes  
        std::list<node*> node_list;

        //parameter only for the Tree
        node* parent; 

        int value;
        int pos;

    public:

        ///\param _value is for initialize the value 
        ///\param _type define the type of the node
        node(int _value){
            value=_value;
            parent=nullptr;
            node_list={};
            pos=-1;
        }

        ///copy costructor
        node(const node& x)
        {
            value = x.value;
            node_list = x.node_list;
            pos = x.pos;
            parent = x.parent;
        }

        //getter  
        int getValue()const {return value;}

        ///setter
        int setValue(int _value) {value=_value;}

        //overloading operator ==
        bool operator==(const node& x) const{
            std::cout<<"operatore ==\n";
            if(x.value==value){
                return true;
            }
            return false;
        }

        //overloading operator !=
        bool operator!=(const node& x) const{
            if(x.value==value)
                return false;
            return true;
        }

        //class that can access to private member of the node
        friend class graph_adj_list;
        friend class tree_pos_vector;
        friend class tree_parent_vector;
        friend class tree_general;
    };

    //TODO here I should define the template
    //class for the Edge of the graph, this edge is oriented

    class Edge{

    private: 
        node* src;
        node* dest;
    public: 
    //costructor 
        Edge(node *_src,node *_dest,int _weight=0,const std::string _mark=""): 
            src{_src},dest{_dest}, weight{_weight},mark{_mark} {}

        int weight;
        std::string mark;

        friend class graph_adj_list;
        friend class tree_pos_vector;
        friend class tree_parent_vector;
    };


} 
