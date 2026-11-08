#include "PayerSet.h"
#include <iostream>

PayerSet::PayerSet() {
    
}

bool PayerSet::add(unsigned long accountNum) {
    return accounts.insert(accountNum);
}
  // If specified account number is not currently in this payer set
  // and there is room in the payer set, add that account number to
  // the payer set and return true.  Otherwise, make no change to
  // this payer set and return false.

int PayerSet::size() const {
    return accounts.size();
}
  // Return the number of account numbers in the PayerSet.

void PayerSet::print() const {
    for (int i = 0; i < size(); i++) {
        ItemType value;
        if (accounts.get(i,value)) {
            std::cout << value << std::endl;
        }
    }
}

//PayerSet::~PayerSet() {
//}
