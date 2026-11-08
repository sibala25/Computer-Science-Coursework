//#include "newSet.h"
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//  int main()
//  {
//      Set a(1000);   // a can hold at most 1000 distinct items
//      Set b(5);      // b can hold at most 5 distinct items
//      Set c;         // c can hold at most DEFAULT_MAX_ITEMS distinct items
//      ItemType v[6] = {1,2,3,4,5,6};
//
//        // No failures inserting 5 distinct items into b
//      for (int k = 0; k < 5; k++)
//          assert(b.insert(v[k]));
//
//        // Failure if we try to insert a sixth distinct item into b
//      assert(!b.insert(v[5]));
//
//        // When two Sets' contents are swapped, their capacities are swapped as well:
//      a.swap(b);
//      assert(!a.insert(v[5])  &&  b.insert(v[5]));
//      
//      Set d(b); // copy constructor
//      
//      c = d; // assignment operator
//      
//      cout << "Passed all test cases!" << endl;
//      return 0;
//}

#include "newSet.h"
#include <iostream>
#include <cassert>
using namespace std;

  int main()
  {
      Set s;
      
      // constructor test cases
      assert(s.size() == 0);
      cerr << "step 1" << 
      // empty test cases
      assert(s.empty());
      s.insert(" ");
      assert(s.empty() == false);

      // size test cases
      assert(s.size() == 1);

      // insert test cases
      s.insert("lavash");
      s.insert("roti");
      s.insert("chapati");
      s.insert("injera");
      assert(s.contains("roti"));
      assert(s.size() == 5);
      assert(s.insert("roti") == false);
      assert(s.insert("injera") == false);
      assert(s.insert("arepa"));
      assert(s.size() == 6);

      // erase test cases
      assert(s.erase("hello") == false);
      assert(s.erase("arepa"));
      assert(s.size() == 5);

      // contains test cases
      assert(s.contains("hello") == false);
      assert(s.contains("roti"));

      // get test cases
      Set ss;
      ss.insert("lavash");
      ss.insert("roti");
      ss.insert("chapati");
      ss.insert("injera");
      ss.insert("matzo");
      
      ItemType x = "roti";
      assert(ss.get(7,x) == false);
      assert(!ss.get(42, x)  &&  x == "roti"); // x unchanged by get failure
      ss.get(0, x);
      assert(x == "roti");  // "roti" is less than exactly 0 items in ss
      ss.get(4, x);
      assert(x == "chapati");  // "chapati" is less than exactly 4 items in ss
      ss.get(2, x);
      assert(x == "lavash");  // "lavash" is less than exactly 2 items in ss
      
      // swap test cases
      Set test1;
      test1.insert("tortilla");
      Set test2;
      test2.insert("matzo");
      test2.insert("pita");
      assert(test1.size() == 1  &&  test1.contains("tortilla")  &&
             test2.size() == 2  &&  test2.contains("matzo")  &&  test2.contains("pita"));
      
      test1.swap(test2);
       assert(test1.size() == 2  &&  test1.contains("matzo")  &&  test1.contains("pita")  &&
              test2.size() == 1  &&  test2.contains("tortilla"));
    
      cout << "Passed all test cases!" << endl;
      return 0;
}

