#ifndef DHEAP_H
#define DHEAP_H

#include "TreePosVector.h"
#include <vector>

namespace slothLib {

/**
 * \class DHeap
 * \brief This class is a data structure implementation based with d-heap
 * tecnique, it is based on TreePosVector container. The priority of the values
 * is based on the Key.
 *
 * \author Nico Fiorini
 */

template <class K, class T> class DHeap {
  private:
    // this is the data structure
    TreePosVector<std::pair<K, T>> *treePosVector;

    int degree;
    bool isMin;
    char delimiter = ',';

    void fixHeap(int pos);

    /// move the node upper if possible
    void moveHigh(int posNode);

    /// move the node down if possible
    void moveLow(int posNode);

    /// insert node to leaf and return the position of the leaf
    int insertToLeaf(const std::pair<K, T> &value);

    int insertToLeaf(const K &key, const T &value);

    // insert
    void insertFromArray(const std::vector<std::pair<K, T>> &values);

    void heapify(int posNode);

    int getLeaf();

    bool isLeaf(const K &keyValue);

    int findByKey(const K &keyValue);

    int findByValue(const T &value);

    void deleteByPos(int pos);

    int getChildPos(int posNode);

    bool isLeaf(const std::pair<K, T> &value);

  public:
    /**
     * @brief Constructor for the D-ary Heap.
     *
     * Initializes a D-ary heap with the specified parameters.
     *
     * @param degree The degree of the D-ary heap (D).
     * @param size The initial size of the heap.
     * @param isMin Indicates whether it's a min-heap (default) or max-heap.
     * @param values A vector of key-value pairs to initialize the heap.
     *
     * @note By default, a min-heap is created. To create a max-heap, set
     * `isMin` to `false`.
     */

    DHeap(int degree, int size, bool isMin = true,
          const std::vector<std::pair<K, T>> &values = {});

    /**
     * @brief Inserts a key-value pair into the D-ary heap.
     *
     * This function inserts the specified key-value pair into the D-ary heap.
     *
     * @param value The key-value pair to insert into the heap.
     *
     * @note The heap will be updated to maintain its heap property.
     */
    void insert(const std::pair<K, T> &value);

    /**
     * @brief Destroys a value and returns a copy of the destroyed value.
     *
     * This function destroys the top value in the D-ary heap, returning a
     * copy of the destroyed key-value pair.
     *
     * @return A copy of the key-value pair that was destroyed.
     *
     * @note The heap will be updated to maintain its heap property after the
     * value is removed.
     */
    std::pair<K, T> popValue();

    /**
     * @brief Get the First Value object
     *
     * @return std::pair<K, T>
     */
    std::pair<K, T> getFirstValue();

    /// delete a value from the heap

    /**
     * @brief Delete element by key
     *
     * @param keyValue The key to remove along with the element
     */
    void deleteByKey(const K &keyValue);

    /**
     * @brief Delete the element by Value
     *
     * @param value The value to remove along with the key associated
     */
    void deleteByValue(const T &value);

    /**
     * @brief Changes the value associated with a specific key.
     *
     * This function changes the value associated with the specified key in
     * the data structure.
     *
     * @param key The key whose associated value you want to change.
     * @param value The new value to associate with the key.
     *
     * @note If the key is not present in the data structure, a new key-value
     * pair will be added.
     */
    void changeValue(const K &key, const T &value);

    /**
     * @brief Changes the key associated with a specific element.
     *
     * This method changes the key associated with the specified element in
     * the D-ary heap.
     *
     * @param newKey The new key to associate with the element.
     * @param element The element whose key you want to change.
     */
    void changeKey(const K &newKey, const T &element);

    /**
     * @brief Gets the key associated with a specific value.
     *
     * This method retrieves the key associated with the specified value in
     * the D-ary heap.
     *
     * @param value The value for which you want to retrieve the associated
     * key.
     * @return The key associated with the specified value, or a default key
     * if the value is not found.
     */
    K getKeyByValue(const T &value);

    /**
     * @brief Checks if the heap is empty.
     *
     * This method checks whether the heap is empty and returns a
     * boolean value indicating its emptiness.
     *
     * @return True if the data structure is empty, false otherwise.
     */
    bool isEmpty();

    /**
     * @brief Stream insertion operator for the DHeap class.
     *
     * This operator allows you to stream the contents of a DHeap object to an
     * output stream.
     *
     * @param os The output stream to which the DHeap object is streamed.
     * @param heap The DHeap object to be streamed.
     * @return The same output stream (`os`) after streaming the DHeap object.
     */
    friend std::ostream &operator<<(std::ostream &os, DHeap<K, T> heap) {
        return os;
    }

    /**
     * @brief Overload for input stream extraction of a DHeap object.
     *
     * This operator allows you to read data from an input stream and populate a
     * DHeap object with it.
     *
     * @param is The input stream to read data from.
     * @param heap The DHeap object to populate with the read data.
     * @return The input stream `is` after the data has been read.
     */
    friend std::istream &operator>>(std::istream &is, DHeap<K, T> &heap) {

        while (!is.eof()) {
            std::string line;
            std::pair<K, T> pair;

            std::getline(is, line, heap.delimiter);
            std::stringstream str1(line);
            str1 >> pair.first;

            std::getline(is, line);
            std::stringstream str2(line);
            str2 >> pair.second;

            heap.insert(pair);
        }
        return is;
    }

    /// Destructor
    ~DHeap();
};

} // namespace slothLib

#include "../sources/DHeap.cpp"

#endif /* DHEAP_H */
