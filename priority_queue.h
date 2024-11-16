//
// Created by hp on 11/17/2024.
//

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

using namespace std;

template <typename T>
class priority_queue {

public:
    priority_queue(int maxSize);
    ~priority_queue();
    void insert(const T& item);
    T remove();

private:
    T* array;
    int maxSize;
    int lastIndex;
    T minItem;
    void upheap(int index);
    void downheap(int index);
    void heapify();
};

#endif //PRIORITY_QUEUE_H
