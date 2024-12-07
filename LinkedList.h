//
// Created by hp on 11/23/2024.
//

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>
using namespace std;


class Node {
public:
    char key;            // The character
    string value;        // The associated value (frequency as string or Huffman code)
    Node* next;

    Node(char k, const string& v){
        key = k;
        value = v;
        next = nullptr;
    }
};


class LinkedList {
private:
    Node* head;

public:
    LinkedList();
    ~LinkedList();

    void insert(char key, const string& value);
    Node* getHead() const;
    string find(char key);
    void clear();
};

#endif // LINKEDLIST_H
