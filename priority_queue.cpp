//
// Created by hp on 11/17/2024.
//
#include "priority_queue.h"
#include <iostream>
using namespace std;

template <typename  T>
priority_queue<T>::priority_queue(int size) {                     //Constructor for initializing elements
    maxSize = size;
    array = new T[maxSize + 1];
    lastIndex = 0;
    minItem = INT_MIN; // Minimum Heap
    array[0] = minItem ;
}

template<typename T>
void priority_queue<T>::insert(const T &item) {         //inserting a new element at the end of the heap and upheaping
    if (lastIndex == maxSize) {
        maxSize += 1;
        array = realloc(array, maxSize * sizeof(T));
    }
    array[++lastIndex] = item;
    upheap(lastIndex);
}

template<typename T>
T priority_queue<T>::remove() {                         //removing the top element of the heap and downheaping
    T temp = array[1];
    array[1] = array[lastIndex--];
    downheap(1);
    return temp;
}

template<typename T>
void priority_queue<T>::upheap(int index) {
    T temp = array[index] ;
    while ( array[index/2] >= temp) {
        array[index] = array[index/2] ;
        index = index/2 ;
    }
    array[index] = temp ;
}

template<typename T>
void priority_queue<T>::downheap(int index) {
    T temp = array[index] ;

    int i = 2 * index;
    for ( ; i <= lastIndex; i *= 2) {
        if ((i < lastIndex) && (array[i] > array[i+1]))
            i++ ;
        if ( temp <= array[i] )
            break;
        array[i/2] = array[i] ;
    }
    array[i/2] = temp ;
}



