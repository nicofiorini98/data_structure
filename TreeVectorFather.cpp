#include "TreeVectorFather.h"

void TreeVectorFather::addNode(const Node *_node, const Node *_father) 
{
    Node* node= new Node(*_node);

    //if father is not defined,and even the root is not defined, then the _node is the root
    if(root==nullptr && _father==nullptr)
    {
        root=node;
        nodes.push_back(std::make_pair(root,0));
        num_nodes++;
        std::cout<<"aggiunto"<<node->value <<" come radice ";
        return;
    }
    //if the father is not specified and the root already exists, 
    //then make node the son of the root
    else if(_father==nullptr)
        nodes.push_back(std::make_pair(node,0));
    else
    {
        int father_pos=getPos(*_father); 
        if(father_pos==-1) // TODO gestire la non esistenza del padre nel vettore
            return;
        nodes.push_back(std::make_pair(node,father_pos));
    }

}


int TreeVectorFather::getPos(const Node &x)
{
    for(int i=0;nodes.size();i++)
        if(nodes[i].first->value==x.value)
            return i;

    return -1;
}

void TreeVectorFather::showTree(){
    int i=0;
    std::cout<<std::endl;
#if 0
    for(auto& node: nodes){
         std::cout<<"nodo in posizione: "<< i++ <<" e valore "<< node.first->value<<" con padre in pos: "<<node.second<<
             " e valore: "<< nodes[node.second].first->value<<std::endl;
    }
#endif
    
    for(auto& node: nodes){
        std::cout<<"( "<< node.first->value<<", "<<node.second<<" )\n";
    }


}

