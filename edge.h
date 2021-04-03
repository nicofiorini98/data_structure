#pragma once
#include "node.h"

namespace datalib{
    class Edge
    {

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
