#include "Tree.h"

class TreeVectorFather: public Tree
{
private: 
    Node* root;
    std::vector<std::pair<Node*,int>> nodes;
    int getPos(const Node &x);

public: 

    TreeVectorFather():Tree(){root=nullptr;}
    ~TreeVectorFather(){}

    int grado(const Node &x){}
    virtual Node* father(const Node &x){}
    std::vector<Node*> getSons(){}                     
    void addNode(const Node *_node, const Node *_father=nullptr);
    void showTree();

    
};
