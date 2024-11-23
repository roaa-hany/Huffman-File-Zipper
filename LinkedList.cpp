//
// Created by hp on 11/23/2024.
//

#include "LinkedList.h"
#include <iostream>
using namespace std;

LinkedList::LinkedList() : head(nullptr) {}

LinkedList::~LinkedList() {
    clear();
}

void LinkedList::insert(char key, const string& value) {
    Node* newNode = new Node(key, value);

    if (!head) {
        head = newNode;
        return;
    }

    Node* current = head;
    while (current->next) {
        current = current->next;
    }
    current->next = newNode;
}

Node* LinkedList::getHead() const {
    return head;
}

string LinkedList::find(char key) const {
    Node* current = head;
    while (current) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    return ""; // Return empty string if key not found
}

void LinkedList::clear() {
    Node* current = head;
    while (current) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;
}

void LinkedList::print() const {
    Node* current = head;
    while (current) {
        cout << current->key << ": " << current->value << endl;
        current = current->next;
    }
}