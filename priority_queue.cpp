//
// Created by hp on 11/23/2024.
//

#include "priority_queue.h"
#include "HuffmanTree.h"
#include "HuffmanNode.h"
using namespace std;

priority_queue::priority_queue() {}

priority_queue::~priority_queue() {
    for (auto node : heap) {
        delete node;
    }
}

int priority_queue::parent(int i) {
  return (i - 1) / 2;
}

int priority_queue::left(int i) {
  return 2 * i + 1;
}

int priority_queue::right(int i) {
  return 2 * i + 2;
}

void priority_queue::heapifyUp(int i) {
    while (i > 0 && heap[i]->freq < heap[parent(i)]->freq) {
        swap(heap[i], heap[parent(i)]);
        i = parent(i);
    }
}

void priority_queue::heapifyDown(int i) {
    int l = left(i), r = right(i);
    int smallest = i;

    if (l < heap.size() && heap[l]->freq < heap[smallest]->freq) {
        smallest = l;
    }

    if (r < heap.size() && heap[r]->freq < heap[smallest]->freq) {
        smallest = r;
    }

    if (smallest != i) {
        swap(heap[i], heap[smallest]);
        heapifyDown(smallest);
    }
}


void priority_queue::insert(HuffmanNode* n) {
    heap.push_back(n);
    heapifyUp(heap.size() - 1);
}


HuffmanNode* priority_queue::removeMin() {
    if (heap.empty())
        return nullptr;

    HuffmanNode* min = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    heapifyDown(0);
    return min;
}


HuffmanNode* priority_queue::getMin() const {
    if(heap.empty())
        return nullptr;
    else
        return heap[0];
}

int priority_queue::getSize() const {
    return heap.size();
}

bool priority_queue::isEmpty() const {
    return heap.empty();
}

void priority_queue::buildHeap(const vector<HuffmanNode*>& nodes) {
    heap = nodes;
    for (int i = heap.size() / 2 - 1; i >= 0; --i) {
        heapifyDown(i);
    }
}