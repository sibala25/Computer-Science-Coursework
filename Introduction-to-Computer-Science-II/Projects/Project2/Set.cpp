#include "Set.h"
#include <iostream>

// default constructor: empty set with just dummy node
Set::Set() : m_size(0) {
    dummy = new Node;
    dummy->prev = dummy;
    dummy->next = dummy;
}

// copy constructor
Set::Set(const Set& other) {
    // first create empty Set with just dummy node
    dummy = new Node;
    dummy->prev = dummy;
    dummy->next = dummy;
    
    // starting at other's first NON dummy node
    Node* startFrom = other.dummy->next;
    
    // insert other's node values until you reach dummy, meaning you went through whole Set
    while(startFrom != other.dummy) {
        insert(startFrom->node_value);
        startFrom = startFrom->next;
    }
    m_size = other.m_size;
}

// assignment operator
Set& Set::operator=(const Set& other) {

    // check if sets are equal (if they are, just return this)
    if (this != &other) {
        // delete all nodes in this/LHS
        Node* p = dummy->next;
        while (p != dummy) {
            Node* nextP = p->next;
            delete p;
            p = nextP;
        }
        delete dummy;
        
        // construct LHS again
        dummy = new Node;
        dummy->prev = dummy;
        dummy->next = dummy;
        
        // insert all values from other/RHS into LHS
        Node* startFrom = other.dummy->next;
        while(startFrom != other.dummy) {
            insert(startFrom->node_value);
            startFrom = startFrom->next;
        }
        m_size = other.m_size;
    }
    return *this;

}

bool Set::empty() const {
    return size() == 0;
}

int Set::size() const {
    return m_size;
}
    
bool Set::insert(const ItemType& value) {
    
    // if value is already in the set, do not let it insert it again
    if (contains(value)) {
        return false;
    }
    // starting at first non-Dummy node, loop through all values
    Node* p = dummy->next;
     while (p != dummy) {
         if (p->node_value <= value) {   // break at the first value found that is LESS than value
             break;
         }
         p = p->next;
     }
    
    Node* insertAfter;
    insertAfter = p->prev; // new value should go before p since it is greater than it (and after the node currently before p)

    // create new node for new value, assign its previous and next
    Node* newGuy = new Node;
    newGuy->prev = insertAfter;
    newGuy->next = insertAfter->next;
    
    // adjust next of what should be before newGuy and prev of what should be after newGuy
    insertAfter->next->prev = newGuy;
    insertAfter->next = newGuy;
    
    // add value to node
    newGuy->node_value = value;
    m_size++;
    return true;
}

bool Set::erase(const ItemType& value) {
    
    // if the value is not in the Set or the set is empty, nothing to erase
    if (!contains(value) || empty()) {
        return false;
    }
    // starting at first non-Dummy node, loop through all values
    Node* p = dummy->next;
     while (p != dummy) {
         if (p->node_value == value) {
             break;                         // break once correct node to remove is found
         }
         p = p->next;
     }
    p->prev->next = p->next;                // node before p's next should be p's next
    p->next->prev = p->prev;                // node after p's prev should be p's prev
    delete p;                               // erasing node
    m_size--;
    
    return true;
}

bool Set::contains(const ItemType& value) const {
    // loop through all non-Dummy node's values  and find value
    for (Node* p = dummy->next; p != dummy; p = p->next) {
        if (p->node_value == value) {
            return true;
        }
    }
    return false;
}

bool Set::get(int i, ItemType& value) const {
    // since list is sorted greatest to least, store ith node's value in value
    if (0 <= i && i < size()) {
        int track = 0;
        // loop through non-Dummy node's value
        for (Node* p = dummy->next; p != dummy; p = p->next) {
            // once correct index is reached, store that node's value in value
            if (track == i) {
                value = p->node_value;
                return true;
            }
            track++;                    // if i is not reached, keep going
        }
    }
    return false;
}
    
void Set::swap(Set& other) {
    // swap both dummy nodes using a temp
    Node* temp = dummy;
    dummy = other.dummy;
    other.dummy = temp;
    
    // swap both sizes using a temp
    int tempSize = m_size;
    m_size = other.m_size;
    other.m_size = tempSize;
}

Set::~Set() {
    // loop through nodes starting at first non-Dummy node
    Node* p = dummy->next;
    while (p != dummy) {
        Node* nextP = p->next;            // store the next node so you can refer to it after
        delete p;                         // delete current node
        p = nextP;                        // move to next node (stored earlier)
    }
    
    delete dummy;                         // remove dummy once rest of nodes are deleted
}

void unite(const Set& s1, const Set& s2, Set& result) {
    // insert everything from s1 into temp set, using copy constructor
    Set temp(s1);
    // insert everything from s2 into temp using get with i values from 0 to s2.size - 1
    for(int i = 0; i < s2.size(); i++) {
        ItemType value;
        if (s2.get(i,value)) {
            temp.insert(value);
        }
    }
    // swap results and temp
    result.swap(temp);
}

void inOnlyOne(const Set& s1, const Set& s2, Set& result) {
    // create a temporary set to insert values into
    Set temp;
    
    //insert values from s1 into temp using get with i values from 0 to s1.size - 1
    for(int i = 0; i < s1.size(); i++) {
        ItemType value;
        if (s1.get(i,value)) {
            if (!s2.contains(value)) {      // only if s2 does NOT have it (only in one)
                temp.insert(value);
            }
        }
    }
    //insert values from s2 into temp using get with i values from 0 to s2.size - 1
    for(int i = 0; i < s2.size(); i++) {
        ItemType value;
        if (s2.get(i,value)) {
            if (!s1.contains(value)) {      // only if s1 does NOT have it (only in one)
                temp.insert(value);
            }
        }
    }
    // swap results and temp
    result.swap(temp);
}
