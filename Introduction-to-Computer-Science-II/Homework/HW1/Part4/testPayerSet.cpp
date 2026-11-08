#include "Set.h"
#include "PayerSet.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

  int main()
  {
      // add , size, print
      PayerSet accts;
      
      // constructor test cases
      assert(accts.size() == 0);

      // add + size test cases
      accts.add(100);
      accts.add(34542);
      accts.add(0);
      accts.add(7);
      assert(accts.size() == 4);
      assert(accts.add(0) == false);
      assert(accts.add(7) == false);
      assert(accts.add(2));
      assert(accts.size() == 5);
      
      // print test cases
      PayerSet pSet;
      pSet.add(5050);
      pSet.add(625);
      pSet.add(1105);
      pSet.print();
      cout << endl;
    
      // compiler-generated destructor
      
      // copy constructor test
      PayerSet pSet2(pSet);
      pSet2.print();
      cout << endl;

      // assignment operator test
      PayerSet pSet3;
      pSet3 = pSet;
      pSet3.print();
      cout << endl;
      
      cout << "Passed all test cases!" << endl;
      return 0;
}
