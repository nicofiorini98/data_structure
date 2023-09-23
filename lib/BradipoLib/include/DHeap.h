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

		// move the node upper if possible
		void moveHigh(int posNode);

		//move the node down if possible
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
		
		/// destroy a value and return a copy of destroyed value
		T popMaxValue();

		/// return the max Value of the Heap
		T getMaxValue();

		/// delete a value from the heap
		void deleteValue(const T& nodeValue);

		bool isEmpty();
		 
		// TODO implementare change value
		// void increase(){}


		void showTree(){
			(this->treePosVector)->showTree();
		}
		
		void showStructure(){
			(this->treePosVector)->showStructure();
		}

        ///Destructor
        ~DHeap();

    };
}

#include "../sources/DHeap.cpp"


#endif /* DHEAP_H */
