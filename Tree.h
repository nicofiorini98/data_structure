#include <vector>
#include "utility.h"

class Tree{
private: 
    int num_Nodi;
     


public: 

    virtual int numNodi();
    virtual int grado();
    virtual Node* getFather(const Node &x);
    virtual std::vector<Node*> getSons();                     
    virtual void addNode();

    //TODO 
    //aggiungi sotto albero
    //rimuovi sotto albero
    
    
    
    
    
    
    
    
    
    
    

    //virtual 

};

