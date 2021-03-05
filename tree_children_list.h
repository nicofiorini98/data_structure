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
namespace datalib
{
    class tree_children_list: public tree
    {
    private:

        int degree;

        std::map<int,node*> nodes_map;
        
    public: 

        /// \param _degree Costructor with default parameter, 
        /// if degree is not specified, Tree doesn't have a particular degree 
        tree_children_list(int _degree=-1);
        
        ///virtual destructor
        ~tree_children_list (){}

        ///return the number of sons for the node x
        virtual int getDegree(const node &x){};
        ///return the parent of the node x
        virtual node* getParent(const node &x){};
        ///return a vector of the node x 
        virtual std::vector<node*> getChildren(const node &x){}

        ///add a node in the Tree 
        ///\param _node is the node to add in the Tree
        ///\param _father is the parent of the node to be inserted, 
        ///if not specified the node is the root of the Tree
        virtual void addNode(const node *x,const node *_parent=nullptr);

        //aggiungi sotto albero
        //rimuovi sotto albero
    };
}