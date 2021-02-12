#include <vector>
#include "utility.h"

class Tree{
protected:
    int num_nodes;
public: 
    Tree(){num_nodes=0;}
    virtual ~Tree(){}

    virtual int numNodi(){return num_nodes;}
    virtual int grado(const Node &x)=0;
    virtual Node* father(const Node &x)=0;
    virtual std::vector<Node*> getSons()=0;                     
    virtual void addNode(const Node *_node,const Node *_father)=0;


    //TODO 
    //aggiungi sotto albero
    //rimuovi sotto albero
    
};

