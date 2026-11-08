// Set.cpp

//#include "Set.h"

//Set::Set()
//{
//    createEmpty();
//}

//bool Set::insert(const ItemType& value)
//{
//      // Fail if value already present
//
//    Node* p = findFirstAtMost(value);
//    if (p != m_head  &&  p->m_value == value)
//        return false;
//
//      // Insert new Node preserving ascending order and incrementing m_size
//
//    insertBefore(p, value);
//    return true;
//}
//
//bool Set::erase(const ItemType& value)
//{
//      // Find the Node with the value, failing if there is none.
//
//    Node* p = findFirstAtMost(value);
//    if (p == m_head  ||  p->m_value != value)
//        return false;
//
//      // Erase the Node, decrementing m_size
//    doErase(p);
//    return true;
//}
//     
//bool Set::get(int i, ItemType& value) const
//{
//    if (i < 0  ||  i >= m_size)
//        return false;
//
//      // Return the value at position i.  Since the values are stored in
//      // descending order, the value at position i will be less than
//      // exactly i items in the set, meeting get's specification.
//
//      // If i is closer to the head of the list, go forward to reach that
//      // position; otherwise, start from tail and go backward.
//
//    Node* p;
//    if (i < m_size / 2)  // closer to head
//    {
//        p = m_head->m_next;
//        for (int k = 0; k != i; k++)
//            p = p->m_next;
//    }
//    else  // closer to tail
//    {
//        p = m_head->m_prev;
//        for (int k = m_size-1; k != i; k--)
//            p = p->m_prev;
//    }
//
//    value = p->m_value;
//    return true;
//}
//
//void Set::swap(Set& other)
//{
//      // Swap head pointers
//
//    Node* p = other.m_head;
//    other.m_head = m_head;
//    m_head = p;
//
//      // Swap sizes
//
//    int s = other.m_size;
//    other.m_size = m_size;
//    m_size = s;
//}
//
//Set::~Set()
//{
//      // Delete all Nodes from last non-dummy down to but not including
//      // the dummy
//
//    while (m_head->m_prev != m_head)
//        doErase(m_head->m_prev);
//
//      // delete the dummy
//
//    delete m_head;
//}
//
//Set::Set(const Set& other)
//{
//    createEmpty();
//
//      // Copy all non-dummy other Nodes.  (This will set m_size.)
//      // Inserting each new node before the dummy node that m_head points to
//      // puts the new node at the end of the list.
//
//    for (Node* p = other.m_head->m_next; p != other.m_head; p = p->m_next)
//        insertBefore(m_head, p->m_value);
//}
//
//Set& Set::operator=(const Set& rhs)
//{
//    if (this != &rhs)
//    {
//          // Copy and swap idiom
//
//        Set temp(rhs);
//        swap(temp);
//    }
//    return *this;
//}
//
//void Set::createEmpty()
//{
//    m_size = 0;
//
//      // Create dummy node
//
//    m_head = new Node;
//    m_head->m_next = m_head;
//    m_head->m_prev = m_head;
//}
//
//void Set::insertBefore(Node* p, const ItemType& value)
//{
//      // Create a new node
//
//    Node* newp = new Node;
//    newp->m_value = value;
//
//      // Insert new item before p
//
//    newp->m_prev = p->m_prev;
//    newp->m_next = p;
//    newp->m_prev->m_next = newp;
//    newp->m_next->m_prev = newp;
//
//    m_size++;
//}
//
//void Set::doErase(Node* p)
//{
//      // Unlink p from the list and destroy it
//
//    p->m_prev->m_next = p->m_next;
//    p->m_next->m_prev = p->m_prev;
//    delete p;
//
//    m_size--;
//}
//
//Set::Node* Set::findFirstAtMost(const ItemType& value) const
//{
//      // Walk through the list looking for a match
//
//    Node* p = m_head->m_next;
//    for ( ; p != m_head  &&  p->m_value > value; p = p->m_next)
//        ;
//    return p;
//}
//
//void unite(const Set& s1, const Set& s2, Set& result)
//{
//      // Check for aliasing to get correct behavior or better performance:
//      // If result is s1 and s2, result already is the union.
//      // If result is s1, insert s2's elements into result.
//      // If result is s2, insert s1's elements into result.
//      // If result is a distinct set, assign it s1's contents, then
//      //   insert s2's elements in result, unless s2 is s1, in which
//      //   case result now already is the union.
//
//    const Set* sp = &s2;
//    if (&result == &s1)
//    {
//        if (&result == &s2)
//            return;
//    }
//    else if (&result == &s2)
//        sp = &s1;
//    else
//    {
//        result = s1;
//        if (&s1 == &s2)
//            return;
//    }
//    for (int k = 0; k < sp->size(); k++)
//    {
//        ItemType v;
//        sp->get(k, v);
//        result.insert(v);
//    }
//}
//
//void inOnlyOne(const Set& s1, const Set& s2, Set& result)
//{
//      // Guard against the case that result is an alias for s2 by copying
//      // s2 to a local variable.  This implementation needs no precaution
//      // against result being an alias for s1.
//
//    Set s2copy(s2);
//    result = s1;
//    for (int k = 0; k < s2copy.size(); k++)
//    {
//        ItemType v;
//        s2copy.get(k, v);
//        if (!result.erase(v))
//            result.insert(v);
//    }
//}

#include "Set.h"
    #include <iostream>
    #include <string>
    #include <cassert>
    using namespace std;

    void test()
    {
        Set<int> si;
        Set<string> ss;
        assert(si.empty());
        assert(ss.empty());
        assert(si.size() == 0);
        assert(ss.size() == 0);
        assert(si.insert(10));
        assert(ss.insert("hello"));
        assert(si.contains(10));
        assert(ss.contains("hello"));
        int i;
        assert(si.get(0, i)  &&  i == 10);
        string s;
        assert(ss.get(0, s)  &&  s == "hello");
        assert(si.erase(10));
        assert(ss.erase("hello"));
        Set<int> si2(si);
        Set<string> ss2(ss);
        si.swap(si2);
        ss.swap(ss2);
        si = si2;
        ss = ss2;
        unite(si,si2,si);
        unite(ss,ss2,ss);
        inOnlyOne(si,si2,si);
        inOnlyOne(ss,ss2,ss);
    }

    int main()
    {
        test();
        cout << "Passed all tests" << endl;
    }


//#include "Set.h"  // class template from problem 2
//    #include <string>
//    using namespace std;
//
//    class Coord
//    {
//      public:
//        Coord(int rr, int cc) : m_row(rr), m_col(cc) {}
//        Coord() : m_row(0), m_col(0) {}
//        double r() const { return m_row; }
//        double c() const { return m_col; }
//      private:
//        double m_row;
//        double m_col;
//    };
//
//    int main()
//    {
//        Set<int> si;
//        si.insert(21);              // OK
//        Set<string> ss;
//        ss.insert("21 Savage");     // OK
//        Set<Coord> sc;
//        sc.insert(Coord(21, -21));  // error!
//    }
