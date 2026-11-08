//#include "Set.h"
//#include <iostream>
//#include <string>
//#include <cassert>
//using namespace std;
//
//  int main()
//  {
//      Set s;
//      
//      // constructor test cases
//      assert(s.size() == 0);
//      
//      // empty test cases
//      assert(s.empty());
//
//      // insert + size test cases
//      s.insert(100);
//      s.insert(34542);
//      s.insert(0);
//      s.insert(7);
//      assert(s.contains(0));
//      assert(s.size() == 4);
//      assert(!s.empty());
//      assert(s.insert(0) == false);
//      assert(s.insert(7) == false);
//      assert(s.insert(2));
//      assert(s.size() == 5);
//      
//      // 0 7 100 34542
//
//      // erase test cases
//      assert(s.erase(30) == false);
//      assert(s.erase(2));
//      assert(s.size() == 4);
//
//      // contains test cases
//      assert(s.contains(3) == false);
//      assert(s.contains(7));
//
//      // get test cases
//      Set ss;
//      ss.insert(123456789);
//      ss.insert(987654321);
//      ss.insert(2000);
//      
//      //2000 123456789 987654321
//      
//      ItemType x = 100;
//      assert(ss.get(7,x) == false);
//      assert(!ss.get(42, x)  &&  x == 100); // x unchanged by get failure
//      
//      ss.get(0, x);
//      assert(x == 987654321);  // 987654321 is less than exactly 0 items in ss
//      ss.get(1, x);
//      assert(x == 123456789);  // 123456789 is less than exactly 4 items in ss
//      ss.get(2, x);
//      assert(x == 2000);       // 2000 is less than exactly 2 items in ss
//      
//      // swap test cases
//      Set test1;
//      test1.insert(556677);
//      Set test2;
//      test2.insert(112234);
//      test2.insert(101010);
//      assert(test1.size() == 1  &&  test1.contains(556677)  &&
//             test2.size() == 2  &&  test2.contains(112234)  &&  test2.contains(101010));
//      
//      test1.swap(test2);
//       assert(test1.size() == 2  &&  test1.contains(112234)  &&  test1.contains(112234)  &&
//              test2.size() == 1  &&  test2.contains(556677));
//    
//      cout << "Passed all test cases!" << endl;
//      return 0;
//}
