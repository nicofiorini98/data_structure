#ifndef TREE_PTR_LIST_TPP
#define TREE_PTR_LIST_TPP

#include "../include/TreePtrList.h"
// #include <stack>
// #include <queue>

using namespace datalib;    

template<class T>
TreePtrList<T>::TreePtrList(int _degree): Tree<T>()
{
    //initalization parameter
    degree=_degree;
    root=nullptr;

}

template<class T>
TreePtrList<T>::~TreePtrList(){

    int j=0;
    //TODO 
    //questo mi genera un segmentation fault, quindi vado ad accedere ad un'area 
    for(typename std::map<T,Node<T>*>::iterator i=nodes_map.begin(); i != nodes_map.end(); ++i)
    {
        // TODO controllare questo pezzo
        delete i->second;
        // nodes_map.erase(i); //this bring to segmentation fault 
        j++;
    }
}

template<class T>
void TreePtrList<T>::addNode(const T* _x, const T *_parent)
{

    Node<T>* x_ptr;

    //x_itr and parent_itr are dependent names
    typename std::map<T,Node<T>*>::iterator x_itr;
    typename std::map<T,Node<T>*>::iterator parent_itr;

    //pre-conditions:
    //1. the node x to add must be different from nullptr
    //2. the node parent must exists if different from nullptr
    //3. the parent nullptr means that x is the root 
    //4. x will be the root if parent is nullptr and even the root is nullptr

    /* Validation of input parameter*/
    if(_x)
        x_itr=nodes_map.find(*_x);
    else{
        std::string error("you cannot add a null node\n");
        throw error;
    }

    if(_parent){
        parent_itr=nodes_map.find(*_parent);

        //il parent non esiste??
        if(parent_itr == nodes_map.end()){
            std::string error("errore, parent non esiste");
            throw error;
        }

        //todo da togliere
        //check the degree of the parent
        if(((parent_itr->second)->node_list.size())>= degree){
            std::string error("the node is reached max degree\n");
            throw error;
        }
    }
    
    //check if x already exists
    // x_itr = nodes_map.find(*_x);
    if(x_itr == nodes_map.end()){
        x_ptr = new Node<T>(*_x);
        nodes_map.insert(std::pair<T,Node<T>*>(x_ptr->value, x_ptr));
    }
    else{
        std::string error("the node is already inserted\n");
        throw error;
    }

    if(!root)
        root=x_ptr;

    if(_parent){
        // parent_itr = nodes_map.find(*_parent);
        if(parent_itr == nodes_map.end()){
            std::string error("the father entered doesn't exist");
            throw error;
        }
        
        //questo porta a dei cicli che non sono permessi nell'albero, devo fare un controllo 
        x_ptr->parent = (parent_itr->second);

        //update children of the parent
        (x_ptr->parent)->addChildren({x_ptr});
    }
    else
    {
        if(x_ptr==root)
            x_ptr->parent=nullptr;
        else //TODO qua io lancierei un errore, meglio non dare troppa libertà 
            x_ptr->parent=root;
    }
    this->num_nodes++;
}

template<class T>
void TreePtrList<T>::addChildren(const T& _x, const std::list<T> &_children) {

    try{
        for(auto& child: _children)
            addNode(&child,&_x);
    }
    catch(std::string error){
        std::cout<<error<<"\n";
    }
}

//return the number of sons for the node x 
//O(log n)
template<class T>
int TreePtrList<T>::getDegree(const T &_x)
{
    return nodes_map.find(_x)->second->node_list.size();
}

//return by referece the parent node of _x
template<class T>
void TreePtrList<T>::getParent(const T &_x, T& _parent){
    _parent = (nodes_map.find(_x))->second->parent->value;
}


//append the children node to the list
template<class T>
void TreePtrList<T>::getChildren(const T& _x,std::list<T>& _list){

    //find the itr of the target
    typename std::map<T,Node<T>*>::iterator x_itr;
    x_itr = nodes_map.find(_x);

    //manage a possible error
    if(x_itr == nodes_map.end()){
        std::string error("TreePtrList::getChildren il nodo inserito non esiste");
        throw error;
    }

    //copy the children node into the list
    for(auto& nodo: x_itr->second->node_list){
        _list.push_back(nodo->value);
    }
}

template<class T>
void TreePtrList<T>::updateParent(const T& _x, const T& _new_parent) {

    //preconditions: can't update the roots

    //devo aggiornare parent, togliendo il figlio
    //devo aggiornare new_parent aggiungendo il figlio
    //devo aggiornare il puntatore interno al parent di _x
    Node<T>* x = getNode(_x);
    Node<T>* parent= x->parent;
    Node<T>* new_parent = getNode(_new_parent);

    parent->node_list.remove(x);
    new_parent->addChildren({x});
    x->parent = new_parent;

}

template<class T>
void TreePtrList<T>::depthSearch(const T* _root){ //todo da finire


   std::cout << "Inizio ricerca in profondita partendo da: " << *_root << "\n";

	//initialize for stack
   std::stack<Node<T>*> stack;
   typename std::map<T,Node<T>*>::iterator nodes_map_itr;

  ///pre-conditions: if the node isn't in the tree, return error
  nodes_map_itr = nodes_map.find(*_root);

  if(nodes_map_itr==nodes_map.end()){
      throw " the node entered for start the visit doesn't exists\n";
  }

  stack.push((*nodes_map_itr).second); //2 s.push(root)
  while (!stack.empty())
  {
      Node<T>* u = stack.top();
      stack.pop();                //pop don't return the value
      std::cout << u->value << "-->";

      //todo vedere se è corretto, non mi fido
      if (true)
      {
          //visit u
          std::list<T> lista_childrens;
          getChildren(u->value, lista_childrens);

          typename std::list<T>::iterator itr;
          //se la lista è vuota non devo aggiungere niente allo stack
          if (lista_childrens.empty())
              u = nullptr;
          else {

              for (auto child_itr = (lista_childrens.rbegin()); child_itr != lista_childrens.rend(); ++child_itr)
              {
                  Node<T>* appo = new Node<T>(*child_itr);
                  stack.push(appo);
              }
          }
      }
  }
  std::cout<<std::endl;
}


template<class T>
void TreePtrList<T>::breadthSearch(const T *_root) {
    //todo implementare

    //initialize for stack
    std::queue<Node<T>*> queue;
    typename std::map<T, Node<T>*>::iterator nodes_map_itr;

    ///pre-conditions: if the node isn't in the tree, return error
    nodes_map_itr = nodes_map.find(*_root);

    if (nodes_map_itr == nodes_map.end()) {
        throw " the node entered for start the visit doesn't exists\n";
    }

    std::cout << "inizio visita in ampiezza\n";

    queue.push((*nodes_map_itr).second); //2 s.push(root)
    while (!queue.empty())
    {
        Node<T>* u = queue.front();
        queue.pop();                //pop don't return the value
        //std::cout << u->value << "-->";
		std::cout << u->value << "-->";

        //todo vedere se è corretto, non mi fido
        if (true)
        {
            //visit u
            std::list<T> lista_childrens;
            getChildren(u->value, lista_childrens);

            typename std::list<T>::iterator itr;
            //se la lista è vuota non devo aggiungere niente allo stack
            if (lista_childrens.empty())
                u = nullptr;
            else {

                for (auto child_itr = (lista_childrens.begin()); child_itr != lista_childrens.end(); ++child_itr)
                {
                    Node<T>* appo = new Node<T>(*child_itr);
                    queue.push(appo);
                }
            }
        }
    }
}


template<class T>
void TreePtrList<T>::showTree()
{
    std::cout<<std::endl;
    for(auto& n: nodes_map)
    {
        if(n.second->parent!=nullptr){
            std::cout<<((n.second)->parent)->value<<"<---";
        }
        else 
            std::cout<<"null"<<"<---";
    
        std::cout<<n.first<<" --->  ";
        //print the sons if the list isn't empty
        if(!n.second->node_list.empty()){
            for(auto& child: n.second->node_list){
                std::cout<<child->value<<" ";
            }
        }
        else 
            std::cout<<"null";
        std::cout<<std::endl;
    }
}

template<class T>
void TreePtrList<T>::showStructure(){

    for(auto &n: nodes_map){
        if(n.second->parent)
            std::cout<<*((n.second)->parent)<<"<--";
        else
            std::cout<<"// <--";

        std::cout<<*(n.second)<<"--> ";

        for(auto& child: n.second->node_list)
            std::cout<<*child<<" ";
        std::cout<<"\n";
    }
}

template<class T>
void TreePtrList<T>::showTreePtr()
{
    std::cout<<std::endl;
    for(auto& n: nodes_map)
    {
        if(n.second->parent!=nullptr){
            std::cout<<((n.second)->parent)<<"<---";
        }
        else 
            std::cout<<"null"<<"<---";
    
        std::cout<<(n.second)<<" --->  ";
        //print the sons if the list isn't empty
        for(auto& child: n.second->node_list)
            std::cout<<child<<" ";

        std::cout<<std::endl;
    }
}

//private function
template <class T>
std::list<Node<T>*>& TreePtrList<T>::getNodeList(Node<T>* _x){

            typename std::map<T,Node<T>*>::iterator x_itr;
            x_itr = nodes_map.find(_x->value);
            if(x_itr != nodes_map.end()){
                return (x_itr->second)->node_list;
            }
            
            std::string error("Error TreePtrList::getNodeList");
            throw error;
           
};


template<class T>
void TreePtrList<T>::showTree2(){}


template<class T>
Node<T>* TreePtrList<T>::getNode(const T _x) {

    for(auto& n: nodes_map){
        if((n.second)->value == _x)
            return n.second;
    }
    std::string error("non esiste il nodo che cerchi\n");
    throw error;
}


#endif