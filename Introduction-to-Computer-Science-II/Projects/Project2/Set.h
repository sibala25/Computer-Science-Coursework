#ifndef Set_h
#define Set_h
#include <string>
//#include "IntWrapper.h"      // TODO: remove this line after testing
//using ItemType = IntWrapper; // TODO: replace this line after testing

using ItemType = std::string; // TODO: uncomment this line after testing
class Set
{
  public:
    Set();
    bool empty() const;
    int size() const;
    bool insert(const ItemType& value);
    bool erase(const ItemType& value);
    bool contains(const ItemType& value) const;
    Set(const Set& other);              // copy construtor
    Set& operator=(const Set& other);   // assignment operator
    ~Set();                             // destructor

    bool get(int i, ItemType& value) const;
    void swap(Set& other);

  private:
    struct Node {
        ItemType node_value;             // value stored at node
        Node* prev;                      // pointing to node's previous
        Node* next;                      // pointing to node's next
    };
    int m_size;                          // number of nodes in the set (not incl dummy)
    Node* dummy;
    
};

void unite(const Set& s1, const Set& s2, Set& result);
void inOnlyOne(const Set& s1, const Set& s2, Set& result);

#endif /* Set_h */
