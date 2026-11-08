#include "Set.h"
#include <iostream>
#include <cassert>
using namespace std;

// Test Cases:
 using ItemType = std::string;
// 1. default constructor
// 2. contains/insert/empty/size function
// 3. erase/contains/size function
// 4. get function
// 5. swap function
// 6. copy constructor
// 7. assignment operator
// 8. unite function
// 9. inonlyone function
// 0. memory leak test case
// 25. implementation test case

#ifndef TESTNUM
#define TESTNUM 1 // CHANGE TEST CASE HERE
#endif

#if TESTNUM == 1
// default constructor

    int main() {
        Set t1;                         // call default constructor
        assert(t1.size() == 0);         // should be size 0
        assert(t1.empty());             // should be empty
        ItemType value = "hi";
        assert(!t1.get(0, value));      // return false bc nothing to get

        cout << "Test case 1 passed!" << endl;
    }

#elif TESTNUM == 2
// contains/insert/empty/size

    int main() {
        Set t2;
        assert(t2.empty());             // should be empty
        assert(!t2.contains("hello"));  // nothing was inserted
        assert(t2.insert("hello"));     // insert hello
        assert(t2.size() == 1);         // now size 1
        assert(!t2.insert("hello"));    // should not let it be inserted 2x
        assert(t2.size() == 1);         // so size till 1
        assert(t2.insert("bye"));       // insert bye
        assert(t2.size() == 2);         // size is 2 now
        assert(!t2.empty());            // not empty
        assert(t2.insert(""));          // insert empty string
        string x = "hello";
        assert(!t2.insert(x));          // cannot insert hello again
        assert(t2.size() == 3);         // bye, hello, ""

        assert(t2.contains("hello") && t2.contains("bye") && t2.contains(""));

        cout << "Test case 2 passed!" << endl;
    }


#elif TESTNUM == 3
// erase/contains/size function

    int main() {
        
        Set t3;
        assert(t3.empty());                 // start empty
        assert(t3.insert("hello"));
        assert(t3.insert("test"));
        assert(t3.insert("bye"));
        assert(t3.insert(""));
        assert(t3.size() == 4);             // now contains hello, test, bye, ""
        
        assert(!t3.erase("no"));            // cannot erase what is not in it
        assert(t3.erase(""));
        assert(t3.size() == 3);             // erased one value
        assert(!t3.erase(""));              // cannot erase again
        assert(t3.erase("bye"));
        assert(t3.erase("test"));
        assert(t3.erase("hello"));
        assert(t3.size() == 0);             // erased everything, so size 0
        assert(t3.empty());                 // and it is empty
                    
        assert(!t3.contains("hello") && !t3.contains("test") && !t3.contains("bye") && !t3.contains("")); // nothing is left in it

        cout << "Test Case 3 passed!" << endl;
    }


#elif TESTNUM == 4
// get function

    int main() {
        Set t4;
        assert(t4.insert("bb"));
        assert(t4.insert("cc"));
        assert(t4.insert(""));
        assert(t4.insert("aa"));
        assert(t4.insert("dd"));
        assert(t4.size() == 5);                          // ensure all 5 elements added

        ItemType value = "hi";
        assert(!t4.get(5, value) && value == "hi");     // the index only goes till 5, so nothing is less than 5 items
        assert(t4.get(0, value) && value == "dd");      // dd is greatest, less than 0 items
        assert(t4.get(1, value) && value == "cc");      // cc is less than 1 item
        assert(t4.get(2, value) && value == "bb");      // bb is less than 2 items
        assert(t4.get(3, value) && value == "aa");      // aa is less than 3 items
        assert(t4.get(4, value) && value == "");        // "" is less than 4 items
        assert(!t4.get(5, value) && value == "");       // no value less than 5 items since only 5 items, so value stays as what it was
        assert(t4.size() == 5);                         // nothing should have changed the set

        ItemType x = "hey";
        assert(t4.insert("jello"));
        assert(t4.get(0, x) && x == "jello");           // jello was correctly inserted at front of list, less than 0 items in the test
        assert(t4.size() == 6);                         // 6 items in it now
        
        assert(t4.contains("aa") &&                     // making sure everything was there still
               t4.contains("bb") &&
               t4.contains("cc") &&
               t4.contains("dd") &&
               t4.contains("") &&
               t4.contains("jello"));

        cout << "Test case 4 passed!" << endl;
    }

#elif TESTNUM == 5
// swap function

    int main() {
        
        Set ss1;                            // create a 4 elem set
        ss1.insert("red");
        ss1.insert("orange");
        ss1.insert("yellow");
        ss1.insert("green");
        assert(ss1.size() == 4);

        Set ss2;                            // create a 2 elem set
        ss2.insert("blue");
        ss2.insert("purple");
        assert(ss2.size() == 2);
        
        ss1.swap(ss2);                      // swap 4 elem and 2 elem set, should contain each other's values now
        assert(ss1.size() == 2 && ss1.contains("blue") && ss1.contains("purple")  &&
                ss2.size() == 4 && ss2.contains("red") && ss2.contains("orange") && ss2.contains("yellow") && ss2.contains("green"));
        
        Set ss3;
        ss2.swap(ss3);                      // swap with an empty set, so ss2 should be empty now
        assert(ss2.size() == 0 && ss3.size() == 4);
        assert(!(ss2.contains("red")) && ss3.contains("red") && ss3.contains("orange") && ss3.contains("yellow") && ss3.contains("green"));
        
        Set ss4;                            // swap two empty sets
        ss4.swap(ss2);
        assert(ss2.size() == 0 && ss4.size() == 0); // both should be empty now
    
        cout << "Test case 5 passed!" << endl;
    }

#elif TESTNUM == 6
// copy constructor

    int main() {
        Set ss1;                        // create 3 elem set
        ss1.insert("red");
        ss1.insert("orange");
        ss1.insert("yellow");
        assert(ss1.size() == 3);

        Set ss2(ss1);                   // call CC
        assert(ss2.size() == 3 && ss1.size() == 3);                                             // ss1 and ss2 should be same size
        assert(ss2.contains("red") && ss2.contains("orange") && ss2.contains("yellow"));        // should contain same elements
        assert(ss1.contains("red") && ss1.contains("orange") && ss1.contains("yellow"));

        Set ss3;                        // create empty set
        Set ss4(ss3);                   // call CC on empty set
        
        assert(ss3.size() == 0 && ss4.size() == 0);     // both should be empty

        ss3.insert("green");                            // should only insert in ss3
        assert(ss3.size() == 1 && ss4.size() == 0);
        
        ss3.erase("green");                             // should only erase in ss3
        assert(ss3.size() == 0 && ss4.size() == 0);

        cout << "Test case 6 passed!" << endl;
    }

#elif TESTNUM == 7
// assignment operator

    int main() {
        Set ss1;                // creating 3 elem set
        ss1.insert("red");
        ss1.insert("orange");
        ss1.insert("yellow");
        assert(ss1.size() == 3);

        Set ss2;
        ss2 = ss1;              // reassing ss2 to be ss1
        assert(ss2.size() == 3 && ss1.size() == 3);     // ss2 and ss1 should be same size and contain same value
        assert(ss2.contains("red") && ss2.contains("orange") && ss2.contains("yellow"));
        assert(ss1.contains("red") && ss1.contains("orange") && ss1.contains("yellow"));

        Set ss3;
        Set ss4;
        ss3 = ss4;             // both should be empty set
        assert(ss3.size() == 0 && ss4.size() == 0);

        ss2 = ss4;             // reassigning ss2, nonempty set, to be empty set
        assert(ss2.size() == 0);        // ss2 should be empty and not contain any of its previous values now
        assert(!ss2.contains("red") && !ss2.contains("orange") && !ss2.contains("yellow"));
        
        cout << "Test case 7 passed!" << endl;
    }

#elif TESTNUM == 8
// unite function


    int main() {
        Set ss1;
        ss1.insert("red");
        ss1.insert("orange");
        ss1.insert("yellow");
        ss1.insert("green");
        assert(ss1.size() == 4);                // create a 4 elem set

        Set ss2;
        ss2.insert("green");
        ss2.insert("blue");
        ss2.insert("purple");
        assert(ss2.size() == 3);                // create a 3 elem set
        
        Set ss3;                                // to be a result set
        
        unite(ss1, ss2, ss3);                   // since green is in both, it should only be added once, 4 + 2 = 6
        assert(ss1.size() == 4 && ss2.size() == 3 && ss3.size() == 6);
        assert(ss3.contains("red") &&
               ss3.contains("orange") &&
               ss3.contains("yellow") &&
               ss3.contains("green") &&
               ss3.contains("blue") &&
               ss3.contains("purple"));
        
        // unite with an empty string
        Set ss4;
        Set ss5;
        unite(ss3,ss4,ss5);             // should just put 6 values from ss3 in ss5 since ss4 is empty
        assert(ss3.size() == 6 && ss4.size() == 0 && ss5.size() == 6);
        assert(ss5.contains("red") &&
               ss5.contains("orange") &&
               ss5.contains("yellow") &&
               ss5.contains("green") &&
               ss5.contains("blue") &&
               ss5.contains("purple"));
        
        // set 1 and result are the same set
        Set ss6;
        Set ss7;
        ss7.insert("apple");
        ss7.insert("banana");
        unite(ss6, ss7, ss6);
        assert(ss6.size() == 2 && ss6.contains("apple") && ss6.contains("banana"));

        // set 2 and result are the same set
        Set ss8;
        ss8.insert("chocolate");
        ss8.insert("orange");
        unite(ss8, ss7, ss7);
        assert(ss7.size() == 4 && ss7.contains("apple") && ss7.contains("banana") && ss7.contains("chocolate") && ss7.contains("orange"));
        
        cout << "Test case 8 passed!" << endl;
    }

#elif TESTNUM == 9
// inonlyone function

    int main() {
        Set ss1;
        ss1.insert("red");
        ss1.insert("orange");
        ss1.insert("yellow");
        ss1.insert("green");
        assert(ss1.size() == 4);                // create a 4 elem set

        Set ss2;
        ss2.insert("yellow");
        ss2.insert("green");
        ss2.insert("blue");
        assert(ss2.size() == 3);                // create a 3 elem set
        
        Set ss3;                                // to be a result set
        
        inOnlyOne(ss1, ss2, ss3);               // only red, orange, blue are in only one so ss3 should have 3 values
        assert(ss1.size() == 4 && ss2.size() == 3 && ss3.size() == 3);
        assert(ss3.contains("red") &&
               ss3.contains("orange") &&
               !ss3.contains("yellow") &&
               !ss3.contains("green") &&
               ss3.contains("blue") &&
               !ss3.contains("purple"));
        
        // inOnlyOne with an empty string
        Set ss4;
        Set ss5;
        inOnlyOne(ss3,ss4,ss5);             // should just put 3 values from ss3 in ss5 since ss4 is empty
        assert(ss3.size() == 3 && ss4.size() == 0 && ss5.size() == 3);
        assert(ss5.contains("red") &&
               ss5.contains("orange") &&
               !ss5.contains("yellow") &&
               !ss5.contains("green") &&
               ss5.contains("blue") &&
               !ss5.contains("purple"));
        
        // set 1 and result are the same set
        Set ss6;
        Set ss7;
        ss7.insert("apple");
        ss7.insert("banana");
        ss7.insert("mango");
        inOnlyOne(ss6, ss7, ss6);
        assert(ss6.size() == 3 && ss6.contains("apple") && ss6.contains("banana") && ss6.contains("mango"));

        // set 2 and result are the same set
        Set ss8;
        ss8.insert("mango");
        ss8.insert("chocolate");
        ss8.insert("orange");
        inOnlyOne(ss8, ss7, ss7);   // apple banana chocolate orange NOT mango
        assert(ss7.size() == 4 && ss7.contains("apple") && ss7.contains("banana") && ss7.contains("chocolate") && ss7.contains("orange") && !ss7.contains("mango"));
        
        cout << "Test case 9 passed!" << endl;
    }

#elif TESTNUM == 0
// memory leak test case from FAQ
void test()
{
      cerr << "test A" << endl;
    Set s;
      cerr << "test B" << endl;
    s.insert(IntWrapper(10));
      cerr << "test C" << endl;
    s.insert(IntWrapper(20));
      cerr << "test D" << endl;
    Set s2;
      cerr << "test E" << endl;
    s2.insert(IntWrapper(30));
      cerr << "test F" << endl;
    s2 = s;
      cerr << "test G" << endl;
    s2.insert(IntWrapper(40));
      cerr << "test H" << endl;
}

int main()
{
    test();
    cerr << "DONE" << endl;
    cout << "Test case 0 passed!" << endl;

}

#elif TESTNUM == 25
// implementation test case from spec
#include <type_traits>

        #define CHECKTYPE(c, f, r, a)  \
        {  \
         static_assert(std::is_same<decltype(&c::f), r (c::*)a>::value, \
             "You did not declare " #c "::" #f " as the Project 2 spec does");  \
         auto p = static_cast<r (c::*)a>(&c::f);  \
         (void) p;  \
        }
        #define CHECKTYPENONMEMBER(f, t)  \
        {  \
         static_assert(std::is_same<decltype(f), t>::value, \
             "You did not declare " #f " as the Project 2 spec does");  \
         auto p = static_cast<std::add_pointer<t>::type>(f);  \
         (void) p;  \
        }

        static_assert(std::is_default_constructible<Set>::value,
                "Set must be default-constructible.");
        static_assert(std::is_copy_constructible<Set>::value,
                "Set must be copy-constructible.");
        static_assert(std::is_copy_assignable<Set>::value,
                "Set must be assignable.");
        static_assert(std::is_same<decltype(*(Set*)(0) = Set()), Set&>::value,
                "Set::operator= return type should be Set&");

        void thisFunctionWillNeverBeCalled()
        {
            CHECKTYPE(Set, empty,    bool, () const);
            CHECKTYPE(Set, size,     int,  () const);
            CHECKTYPE(Set, insert,   bool, (const ItemType&));
            CHECKTYPE(Set, erase,    bool, (const ItemType&));
            CHECKTYPE(Set, contains, bool, (const ItemType&) const);
            CHECKTYPE(Set, get,      bool, (int, ItemType&) const);
            CHECKTYPE(Set, swap,     void, (Set&));
            CHECKTYPENONMEMBER(unite,     void(const Set&, const Set&, Set&));
            CHECKTYPENONMEMBER(inOnlyOne, void(const Set&, const Set&, Set&));
        }

        int main()
        {}
#endif
