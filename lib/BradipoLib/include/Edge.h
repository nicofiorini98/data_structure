#ifndef EDGE_H
#define EDGE_H
#include "Node.h"
#include <iostream>
#include <sstream>
#include <string>

namespace slothLib{

    template<class T>
    class Edge
    {

    private:
        Node<T>* src;
        Node<T>* dest;
        double weight;
        char delimiter = ',';
        std::string mark;
        Edge(Node<T>* src, Node<T>* dest, int weight=0, const std::string mark="");
        
    public:
        Edge():src(nullptr),dest(nullptr), weight(0),mark(""){}
        /// public costructor
        Edge(const T *src, const T *dest, int weight=0, const std::string &mark="");
        
        ///copy costructor
        Edge(const Edge<T>& x);
        
        /// Destructor
        ~Edge(){
            delete src;
            delete dest;
        }

        /// Return the source value of the Edge
        T getSourceValue() const {return (src->value);}
        
        ///Return the destination Value of the Edge
        T getDestinationValue() const {return (dest->value);}
        
        /// Return the weight of the Edge
        double getWeight() const {return this->weight;}
        
        /// Set the weight of the Edge
        void setWeight(double weight){this->weight = weight;}

        friend std::ostream& operator<<(std::ostream &os,const Edge<T>& edge){
            os << edge.getSourceValue() << edge.delimiter << edge.getDestinationValue();
            return os;
        }
        
        friend std::istream& operator>>(std::istream &is,Edge<T>& edge){

            if((edge.src)){
                delete (edge.src);
            }

            if((edge.dest)){
                delete (edge.dest);
            }
            
            edge.src  = new Node<T>();
            edge.dest = new Node<T>();
            
            std::string line;
            std::getline(is,line,',');
            std::stringstream str(line);
            str>>(*edge.src);

            std::getline(is,line);
            std::stringstream str2(line);
            str2>>(*edge.dest);

            return is;
        }

        template<class U>
        friend class Graph;

        template<class U>
        friend class GraphEdgeList;

        template<class U>
        friend class GraphIncList;
        
    };
}

#include "../sources/Edge.cpp"

#endif