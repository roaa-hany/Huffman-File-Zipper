//
// Created by hp on 11/23/2024.
//

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "HuffmanNode.h"
#include <vector>

using namespace std;

// priority queue class to implement min-heap
class priority_queue {
private:
    vector<HuffmanNode*> heap;

    int parent(int i);
    int left(int i);
    int right(int i);

    void heapifyUp(int i);
    void heapifyDown(int i);

public:
    priority_queue();
    ~priority_queue();

    void insert(HuffmanNode* node);
    HuffmanNode* removeMin();
    HuffmanNode* getMin();
    int getSize();
    bool isEmpty();
    void buildHeap(const vector<HuffmanNode*>& nodes);
};

#endif //PRIORITY_QUEUE_H
