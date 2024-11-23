//
// Created by hp on 11/23/2024.
//

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>
using namespace std;

// Node structure
class Node {
public:
    char key;            // The character
    string value;        // The associated value (frequency as string or Huffman code)
    Node* next;

    Node(char k, const string& v) : key(k), value(v), next(nullptr) {}
};

// Linked List class
class LinkedList {
private:
    Node* head;

public:
    LinkedList();
    ~LinkedList();

    void insert(char key, const string& value);
    Node* getHead() const;
    string find(char key) const;
    void clear();
    void print() const;
};

#endif // LINKEDLIST_H
