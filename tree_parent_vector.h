#include "tree.h"

namespace datalib{

    class tree_parent_vector: public tree
    {
    private: 
        node* root;
        std::vector<std::pair<node*,int>> vec_node;
        int getPos(const node &x);

    public: 

        tree_parent_vector():tree(){root=nullptr;}

        ~tree_parent_vector(){}

        int getDegree(const node &x){}
        virtual node getParent(const node &x){}
        std::list<node*> getChildren(const node &x){}                     
        //to update 
        //void addNode(const node *_node, const node *_parent=nullptr);
        void addNode(const node *_node,const node *_parent,const std::list<node*> _children)=0;
        void showTree();

    };
}