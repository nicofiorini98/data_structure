#include "tree.h"
#include <map>
/**
 * \class Tree
 * \brief This class is a base class for various tree implementations
 * 
 * 
 * \author Nico Fiorini
 * \date 03/03/2021
 */


/*
 * manage the nullptr for the root and the leafs
*/

namespace datalib
{
    class tree_general : public tree
    {
    private:

        int degree;

        std::map<int,node*> nodes_map;

        //get node by value
        void getNode(int _value);
        
    public: 

        /// \param _degree Costructor with default parameter, 
        /// if degree is not specified, Tree doesn't have a particular degree 
        tree_general(int _degree=-1);
        
        ///virtual destructor
        ~tree_general (){}

        ///return the number of sons for the node x
        int getDegree(const node &x);
        ///return the parent of the node x
        node getParent(const node &x);

        ///return a vector of the node x 
        std::list<node*> getChildren(const node &x);

        ///add a node in the Tree 
        ///\param _node is the node to add in the Tree
        ///\param _father is the parent of the node to be inserted, 
        ///if not specified the node is the root of the Tree
        void addNode(const node *x,const node *_parent=nullptr,const std::list<node*> _children={});

        ///visita DFS 
        void visitDFS(const node &root);
        
        void showTree();
        //aggiungi sotto albero
        //rimuovi sotto albero
    };
}