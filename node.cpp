#include "node.h"
#include <algorithm>

using namespace datalib;


node::node(int _value,node* _parent)
{
            value=_value;
            pos=-1;
            parent=_parent;
            node_list={};
} 

node::node(const node& x)
{
    value = x.value;
    node_list = x.node_list;
    pos = x.pos;
    parent = x.parent;
}


bool node::operator==(const node& x) const{
    std::cout<<"operatore ==\n";
    if(x.value==value){
        return true;
    }
    return false;
}
void node::operator=(const node& x) 
{
    value = x.value;
    node_list = x.node_list;
    pos = x.pos;
    parent = x.parent;   
}

bool node::operator<(const node& x) const{

    if(x.value<value){
        return true;
    }
    return false;
}

bool node::operator<=(const node& x) const{

    if(x.value<=value){
        return true;
    }
    return false;
}

bool node::operator>(const node& x) const{

    if(x.value>value){
        return true;
    }
    return false;
}

bool node::operator>=(const node& x) const{

    if(x.value>=value){
        return true;
    }
    return false;
}

bool node::operator!=(const node& x) const{
    if(x.value==value)
        return false;
    return true;
}

void node::addChildren(std::list<node*>&& _children){
    std::list<node*>::iterator itr;
    for(auto& child: _children)
    {
        if(child==nullptr)
            continue;

        itr = std::find(node_list.begin(),node_list.end(),child);

        if(itr==node_list.end()){
            node_list.push_back(child); //complessità costante
        }
    }
    

}
