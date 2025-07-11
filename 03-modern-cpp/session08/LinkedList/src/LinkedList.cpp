#include "LinkedList.hpp"

//–– Node ctor ––//
LinkedList::Node::Node(int v, Node* n)
    : value(v), next(n)
{}

//–– dtor ––//
LinkedList::~LinkedList() {
    clear();
}

//–– pushFront ––//
void LinkedList::pushFront(int v) {
    head = new Node(v, head);
    ++count;
}

//–– pushBack ––//
void LinkedList::pushBack(int v) {
    if (empty()) {
        head = new Node(v, nullptr);
    } else {
        Node* p = head;
        while (p->next) {
            p = p->next;
        }
        p->next = new Node(v, nullptr);
    }
    ++count;
}

//–– popFront ––//
int LinkedList::popFront() {
    if (empty()) {
        throw std::underflow_error("popFront() on empty list");
    }
    Node* tmp = head;
    int val = tmp->value;
    head = head->next;
    delete tmp;
    --count;
    return val;
}

//–– popBack ––//
int LinkedList::popBack() {
    if (empty()) {
        throw std::underflow_error("popBack() on empty list");
    }
    // single element?
    if (!head->next) {
        int val = head->value;
        delete head;
        head = nullptr;
        --count;
        return val;
    }
    // walk to second-last
    Node* p = head;
    while (p->next->next) {
        p = p->next;
    }
    // p->next is last
    int val = p->next->value;
    delete p->next;
    p->next = nullptr;
    --count;
    return val;
}

//–– front ––//
int LinkedList::front() const {
    if (empty()) {
        throw std::underflow_error("front() on empty list");
    }
    return head->value;
}

//–– back ––//
int LinkedList::back() const {
    if (empty()) {
        throw std::underflow_error("back() on empty list");
    }
    Node* p = head;
    while (p->next) {
        p = p->next;
    }
    return p->value;
}

//–– empty ––//
bool LinkedList::empty() const noexcept {
    return head == nullptr;
}

//–– size ––//
std::size_t LinkedList::size() const noexcept {
    return count;
}

//–– remove ––//
bool LinkedList::remove(int v) {
    Node** cur = &head;
    while (*cur) {
        if ((*cur)->value == v) {
            Node* toDelete = *cur;
            *cur = (*cur)->next;
            delete toDelete;
            --count;
            return true;
        }
        cur = &((*cur)->next);
    }
    return false;
}

//–– clear ––//
void LinkedList::clear() noexcept {
    Node* p = head;
    while (p) {
        Node* tmp = p->next;
        delete p;
        p = tmp;
    }
    head = nullptr;
    count = 0;
}

//–– print ––//
void LinkedList::print() const {
    for (Node* p = head; p; p = p->next) {
        std::cout << p->value << ' ';
    }
    std::cout << "\n";
}
