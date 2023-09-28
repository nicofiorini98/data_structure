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
		bool isMin;

  		void fixHeap(int pos);

		/// move the node upper if possible
		void moveHigh(int posNode);

		/// move the node down if possible
		void moveLow(int posNode);

  		/// insert node to leaf and return the position of the leaf
		int insertToLeaf(const T& nodeValue);

		// insert 
		void insertFromArray(const std::vector<T>& values);

		void heapify(int posNode);

		int getLeaf(); 

		bool isLeaf(const T& nodeValue);


    public:

        ///Costructor for the Heap
        DHeap(int degree, int size,bool isMin, const std::vector<T>& values);

		/// Insert a value in the heap
		void insert(const T& nodeValue);
		
		/// destroy a value and return a copy of destroyed value
		T popValue();

		/// return the max Value of the Heap
		T getFirstValue();

		/// delete a value from the heap
		void deleteValue(const T& nodeValue);
		
		/// change Value
		void setValue(const T& oldValue,const T& newValue);

		/// return true if the Heap is empty
		bool isEmpty();
		 

		/// show the tree of the heap
		void showTree(){
			(this->treePosVector)->showTree();
		}
		
		/// show the structure behind the treePosVector
		void showStructure(){
			(this->treePosVector)->showStructure();
		}

        ///Destructor
        ~DHeap();

    };
}

#include "../sources/DHeap.cpp"


#endif /* DHEAP_H */
