#ifndef DHEAP_H 
#define DHEAP_H

#include "TreePosVector.h"
#include <vector>

namespace datalib{


	/**
	 * \class GraphAdjList
	 * \brief This class is a data structure for a d-heap,
	 * is implemented with the TreePosVector.
	 * 
	 * \author Nico Fiorini
	*/

    template<class T>
    class DHeap {
    private: 

		//this is the data structure
		// TODO aggiungere struttura dati TreePosVector
		TreePosVector<T>* treePosVector;

		int degree;

  		void fixHeap(int pos);


  		//return the position of the last leaf
		// int getLeaf();

		void moveHigh(int posNode);

  		// insert node to leaf and return the position of the leaf
		int insertToLeaf(const T& nodeValue);
		void muoviBasso(){}



    public:
        ///Costructor for the GraphAdjList
        DHeap(int degree, int size, const std::vector<T>& values = {});

		int getLeaf(); //todo to add to private, only for testing here

		void insert(const T& nodeValue);

		bool isLeaf(const T& nodeValue);

		T findMax(){return this->treePosVector->vecNode[1]->value;}

		void deleteMax();

		void increase(){}

		void decrease(){}

		void showStructure(){
			(this->treePosVector)->showStructure();
		}

        ///Destructor
        ~DHeap();

        
    };
}

#include "../sources/DHeap.cpp"


#endif /* DHEAP_H */
