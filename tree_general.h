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
        node* root;
        std::map<int,node*> nodes_map;

        //get node by value
        void getNode(int _value);
        
    public: 

        /// \param _degree Costructor with default parameter, 
        /// if degree is not specified, Tree doesn't have a particular degree 
        tree_general(int _degree=-1);
        
        ///virtual destructor
        ~tree_general(){}

        ///overloading operator >>
        //TODO decidere un carattere per il nullo per l'input da file
        friend std::istream &operator>>(std::istream &is, tree_general &t)
        {
            //pre-conditions
            //format for input of a node: node parent list_children
            //Example: 3 1
            node x{0};
            node parent{0};
            //get the value of x and parent
            char tmp;

            while (is>>tmp)
            {

                if (tmp != '{')
                {
                    std::cerr << "errore di lettura\n";
                    is.unget();
                    is.clear(std::ios_base::failbit);
                    return is;
                }
                std::cout<<tmp;

                is >> x >> parent;
                std::cout<<x<<" "<<parent;

                if (is>>tmp && tmp != '}')
                {
                    std::cerr << "errore di lettura\n";
                    is.unget();
                    is.clear(std::ios_base::failbit);
                    return is;
                }
                std::cout<<tmp<<"\n";
                // for(char tmp;is>>tmp;)
                // {
                //     is.unget();
                //     node boh{0};
                //     is>>boh;
                // }

                t.addNode(&x, &parent);
            }
            return is;
        }

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
        void addNode2(const node* _x,const node *_parent=nullptr,const std::list<node> _children={}); //TODO 
        void addNode(const node* _x,const node *_parent=nullptr);
        virtual void addChildrens(const node* _x, const std::list<node> _childrens){} //TODO da rendere virtuale puro

        ///print the node following a DFS visit
        void visitDFS(const node* root);
        ///print the node following BFS visit
        void visitBFS(const node* root);
        void showTree();
        void showTreePtr();
        void showTree2();
        //aggiungi sotto albero
        //rimuovi sotto albero
    };

   
}

