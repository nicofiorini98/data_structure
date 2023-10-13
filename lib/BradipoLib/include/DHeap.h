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

    template<class K,class T>
    class DHeap {
    private:

		//this is the data structure
		TreePosVector<std::pair<K,T>>* treePosVector;

		int degree;
		bool isMin;
		char delimiter = ',';

  		void fixHeap(int pos);

		/// move the node upper if possible
		void moveHigh(int posNode);

		/// move the node down if possible
		void moveLow(int posNode);

  		/// insert node to leaf and return the position of the leaf
		int insertToLeaf(const std::pair<K,T>& value);

		int insertToLeaf(const K& key, const T& value);

		// insert 
		void insertFromArray(const std::vector<std::pair<K,T>>& values);

		void heapify(int posNode);

		int getLeaf(); 

		bool isLeaf(const K& keyValue);
		
		int findByKey(const K& keyValue);

		int findByValue(const T& value);
		
		void deleteByPos(int pos);

		int getChildPos(int posNode);

		bool isLeaf(const std::pair<K,T>& value);

    public:

        ///Costructor for the Heap
        DHeap(int degree, int size,bool isMin = true, const std::vector<std::pair<K,T>>& values={});

		/// Insert a value in the heap
		void insert(const std::pair<K,T>& value);

		
		/// destroy a value and return a copy of destroyed value
		std::pair<K,T> popValue();

		/// return the max Value of the Heap
		std::pair<K,T> getFirstValue();

		/// delete a value from the heap
		void deleteByKey(const K& keyValue);

		void deleteByValue(const T& value);
		
		/// change Value based on the key
		void changeValue(const K& key,const T& value );
		
		/// decreaseKey 
		void changeKey(const K& newKey, const T& element);

		/// get Key by Value
		K getKeyByValue(const T& value);

		/// return true if the Heap is empty
		bool isEmpty();
		
		/// operator <<
		friend std::ostream& operator<<(std::ostream& os,DHeap<K,T> heap){
			return os;
		}

		// operator >>
		friend std::istream& operator>>(std::istream& is,DHeap<K,T>& heap){

			while(!is.eof()){
				std::string line;
				std::pair<K,T> pair;

				std::getline(is,line,heap.delimiter);
				std::stringstream str1(line);
				str1>>pair.first;

				std::getline(is,line);
				std::stringstream str2(line);
				str2>>pair.second;
				
				heap.insert(pair);
			}
        	return is;	
		}
		
        ///Destructor
        ~DHeap();

    };

}

#include "../sources/DHeap.cpp"


#endif /* DHEAP_H */
