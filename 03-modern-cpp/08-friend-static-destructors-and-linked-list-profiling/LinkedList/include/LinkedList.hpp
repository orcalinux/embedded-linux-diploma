#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <iostream>
#include <stdexcept>

class LinkedList {
public:
    LinkedList() = default;
    ~LinkedList();

    // push to front and back
    void push_front(int v);
    void push_back(int v);

    // pop from front and back; throw if empty
    int pop_front();
    int pop_back();

    // peek at front/back without removing; throw if empty
    int front() const;
    int back() const;

    // utilities
    bool empty() const noexcept;
    std::size_t size() const noexcept;
    void clear() noexcept;
    bool remove(int v);

    // print all elements
    void print() const;

private:
    class Node {
    public:
        int   value;
        Node* next;
        Node(int v, Node* n);
    };

    Node* head = nullptr;
    std::size_t count = 0;
};

#endif // LINKEDLIST_HPP
