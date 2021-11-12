#include <iostream>
using namespace std;

typedef string Elem; // list element type
class DNode
{ // doubly linked list node
private:
    Elem elem; // node element value
    DNode* prev; // previous node in list
    DNode* next; // next node in list
    friend class DLinkedList; // allow DLinkedList access
    // friend는 다른 클래스의 private와 protected 멤버에 접근할 수 있음
};

class DLinkedList { // doubly linked list
public:
    DLinkedList(); // constructor
    ~DLinkedList(); // destructor bool empty() const; // is list empty?
    const Elem& front() const; // get front element
    const Elem& back() const; // get back element
    void addFront(const Elem& e); // add to front of list
    void addBack(const Elem& e); // add to back of list
    void removeFront(); // remove from front
    void removeBack(); // remove from back
    void printForward();
    void printBackward();
    bool empty() const;

private: // local type definitions
    DNode* header; // list sentinels
    DNode* trailer;
protected: // local utilities
    void add(DNode* v, const Elem& e); // insert new node before v
    void remove(DNode* v); // remove node v
};

DLinkedList::DLinkedList() { // constructor
    header = new DNode; // create sentinels
    trailer = new DNode;
    header->next = trailer; // have them point to each other
    trailer->prev = header;
}
DLinkedList:: ~DLinkedList() { // destructor
    while (!empty())
        removeFront(); // remove all but sentinels
    delete header; // remove the sentinels
    delete trailer;
}
bool DLinkedList::empty() const // is list empty?
{
    return (header->next == trailer);
}
const Elem& DLinkedList::front() const // get front element
{
    return header->next->elem;
}
const Elem& DLinkedList::back() const // get back element
{
    return trailer->prev->elem;
}

// insert new node before v
void DLinkedList::add(DNode* v, const Elem& e) {
    DNode* u = new DNode;
    u->elem = e; // create a new node for e
    u->next = v; // link u in between v
    u->prev = v->prev; // ...and v->prev
    v->prev->next = u;
    v->prev = u;

    /*u->next = v->next;
    u->prev = v;
    v->next->prev = u;
    v->next = u;*/

}
void DLinkedList::addFront(const Elem& e) // add to front of list
{
    add(header->next, e);
    //add(header, e);
}
void DLinkedList::addBack(const Elem& e) // add to back of list
{
    add(trailer, e);
    //add(trailer->prev, e);
}

void DLinkedList::remove(DNode* v) { // remove node v
    DNode* u = v->prev; // predecessor
    DNode* w = v->next; // successor
    u->next = w; // unlink v from list
    w->prev = u;
    delete v;
}
void DLinkedList::removeFront() // remove from font
{
    remove(header->next);
}
void DLinkedList::removeBack() // remove from back
{
    remove(trailer->prev);
}

void DLinkedList::printForward() {
    DNode* v = header->next;
    while (v->next != NULL) {
        cout << v->elem << " ";
        v = v->next;
    }
}
void DLinkedList::printBackward() {
    DNode* v = trailer->prev;
    while (v->prev != NULL) {
        cout << v->elem << " ";
        v = v->prev;
    }
}

int main() {
    DLinkedList* dl = new DLinkedList();
    dl->addFront("10");
    dl->addFront("20");
    dl->addFront("30");
    dl->addFront("40");

    // 40 - 30 - 20 - 10
    cout << "printBackward : ";
    dl->printBackward();
    cout << endl;
    // 10 - 20 - 30 - 40
    cout << "printForward : ";
    dl->printForward();
    cout << endl;





    return 0;
}