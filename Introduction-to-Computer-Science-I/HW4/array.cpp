//  Aashna Sibal
//  UID: [student ID redacted]
//  HW4
//
//  Created by Aashna Sibal on 2/19/24.
//

#include <iostream>
#include <string>
#include <cassert>

using namespace std;

int locateMaximum(const string array[], int n);
int countFloatingPointValues(const string array[], int n);
bool hasNoCapitals(const string array[], int n);
int shiftLeft(string array[], int n, int amount, string placeholder);


int main() {
    string data[5] = { "mamaBbcca", "mamaBbcca", "12,", "98.76", "tyrion" };
    string datatwo[6] = { "mamaBbcca", "mamaBbcca", "12,", "98.76", "tyrion", "tyrion"};
    string datathree[6] = { "mamaBbcca", "mamaBbcca", "12,", "+98.76", "tyrion", "98.76," };
    string folks[8] = { "samwell", "jon", "margaery", "daenerys", "tyrion", "sansa", "magdalena", "jon"};

    // locateMaximum test cases
    assert( locateMaximum(data, 0) == -1 );
    assert( locateMaximum(data, 5) == 4 );
    assert( locateMaximum(datatwo, 6) == 4 );

    // countFloatingPointValues test cases
    assert( countFloatingPointValues(data, 0) == -1 );
    assert( countFloatingPointValues(data, 5) == 1 );
    assert( countFloatingPointValues(datathree, 6) == 0 );
    assert( countFloatingPointValues(datathree, 6) == 0 );

    // hasNoCapitals test cases
    assert( hasNoCapitals(data, 0) == true );
    assert( hasNoCapitals(data, 5) == false );
    assert( hasNoCapitals(folks, 8) == true );

    // shiftLeft test cases
    assert( shiftLeft(data, -5, 10, "foobar") == -1 );
    assert( shiftLeft(data, 5, -5, "foobar") == -1 );
    assert( shiftLeft(data, 5, 2, "foo") == 2 );
    assert( shiftLeft(data, 5, 10, "bar") == 5 );

    cout << "All test cases passed." << endl;
    
    return 0;
}

int locateMaximum(const string array[], int n) {
    if (n <= 0) { // if the length is <= 0, there is nothing to check so return -1
        return -1;
    }
    string maximum = array[0];  // initializing the max as the first array element, to then compare each element to it
    int max_index = 0;          // storing max index to return, starting at 0
    for (int k = 0; k < n; k++) {
        if (array[k] > maximum) { // if this element is bigger than the current maximum, replace maximum and max index
            maximum = array[k];
            max_index = k;
        }
    }
    return max_index; // after looping through, return the index of the max element
}

int countFloatingPointValues(const string array[], int n) {
    int float_count = 0; // start float count at 0
    if (n <= 0) { // if the length is <= 0, there is nothing to check so return -1
        return -1;
    }
    for (int k = 0; k < n; k++) {
        bool decimalFound = false; // to check that no float has >1 decimal
        bool validFloat = true;
        for (int i = 0; i < array[k].size(); i++) { // looping through characters of the array elements
            if (!isdigit(array[k][i])) {
                if (array[k][i] == '.' && !decimalFound) { // if a decimal is found for the first time, mark it
                    decimalFound = true;
                }
                else if (array[k][i] == '.' && decimalFound) { // if a second decimal is found - invalid float
                    validFloat = false;
                    break;
                }
                else {                  // if anything that is not a digit is not a decimal either -
                    validFloat = false; // invalid float bc there is a special character or letter
                    break;
                }
            }
        }
            if (validFloat) { // for each valid float increment counter by 1
                float_count++;
            }
    }

    return float_count; // return total float count
}

bool hasNoCapitals(const string array[], int n) {
    if (n <= 0) { // if n is <= 0, there are no capitals
        return true;
    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < array[k].size(); i++) { // looping through characters of elements in the array
            if (isupper(array[k][i])) { // if a capital is found
                return false; // return false
            }
        }
    }
    return true; // no capitals found - return true
}

int shiftLeft(string array[], int n, int amount, string placeholder) {
    if (n <= 0 || amount < 0) { // if the n <= 0 or the amount to shift is < 0, return -1
        return -1;
    }
    
    int placeholder_counter = 0; // to count # times placeholder is used
    
    if (amount > n) { // if the amount to shift is greater than the length of the array, you can only shift by n (shift whole array)
        amount = n;
    }
    for (int k = 0; k < n; k++) {
        
        if (k >= amount) { // only values at indices greater than the amount to shift will stay in the array, and be shifted back

            array[k - amount] = array[k]; // shift array[k] back by amount
        }
        
        if ( k >= (n - amount) ) { // any array[k] that was not replaced in the shift but is still in the array (n-amount)
            array[k] = placeholder; // is replaced with placeholder
            placeholder_counter++; // increment placeholder counter
        }
    }
    return placeholder_counter;
}
