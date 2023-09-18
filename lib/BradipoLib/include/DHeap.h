#ifndef DHEAP_H 
#define DHEAP_H

#include "TreePosVector.h"
#include <vector>

namespace datalib{


	/**
	 * \class DHeap 
	 * \brief This class is a data structure for a d-heap,
	 * is implemented with the TreePosVector.
	 * 
	 * \author Nico Fiorini
	*/

    template<class T>
    class DHeap {
    private: 

		//this is the data structure
		TreePosVector<T>* treePosVector;

		int degree;

  		void fixHeap(int pos);

  		//	todo cambiare nome parametri
		void moveHigh(int posNode);

		void moveLow(int posNode);

  		// insert node to leaf and return the position of the leaf
		int insertToLeaf(const T& nodeValue);

		void insertFromArray(const std::vector<T>& values);

		void heapify(int posNode);

		int getLeaf(); 

		bool isLeaf(const T& nodeValue);


    public:

        ///Costructor for the Heap
        DHeap(int degree, int size, const std::vector<T>& values);

		/// Insert a value in the heap
		void insert(const T& nodeValue);

		/// return the max Value of the Heap
		T findMax(){return this->treePosVector->vecNode[1]->value;}

		/// delete a value from the heap
		void deleteValue(const T& nodeValue); 
		 
		// void increase(){}

		// void decrease(){}

		void showStructure(){
			(this->treePosVector)->showStructure();
		}

        ///Destructor
        ~DHeap();

        
    };
}

#include "../sources/DHeap.cpp"


#endif /* DHEAP_H */
