//
//  HW3
//  Aashna Sibal
//  UID: [student ID redacted]

#include <iostream>
#include <string>
#include <cassert>

using namespace std;

bool isValidQC(string results);
int passQC(string results);
int defectQC(string results);
int totalQC(string results);
int batches(string results);
int func(int n, double d);


int main() {
    
    // Valid Test Cases
    assert( isValidQC("Q1p1d0") == true );
    assert( isValidQC("Q2p1d1Q4p3d1") == true );
    assert( isValidQC("Q15p10d5") == true );
    
    // Invalid Test Cases
    assert( isValidQC("  ") == false );
    assert( isValidQC("") == false );
    assert( isValidQC("Q2p1d1q4p3d1") == false );
    assert( isValidQC("Q2p1Q4p3d1") == false );
    assert( isValidQC("Q2p1p1Q4p3d1") == false );
    assert( isValidQC("Q2pd1Q4p3d1") == false );
    assert( isValidQC("Q2p1dQ4p3d1") == false );
    assert( isValidQC("Q2p1d1Q04p3d1") == false );
    assert( isValidQC("Q2p1d1Q4p2d1") == false );
    assert( isValidQC("Q2p1d1Q0p0d0") == false );
    assert( isValidQC("Q2p1d1Q4p3d1   sdfsdf") == false );
    assert( isValidQC("Q0p0d0") == false );
    assert( isValidQC("Q2p1d1Q4P3d1") == false );
    assert( isValidQC("Q2pasd1Q4p3d1") == false );
    
    // Pass Test Cases, 3 valid 1 invalid
    assert( passQC("Q1p1d0") == 1 );
    assert( passQC("Q2p1d1Q4p3d1") == 4 );
    assert( passQC("Q15p10d5") == 10 );
    assert( passQC("Q2p1d1q4p3d1") == -1 );

    // Defect Test Cases, 3 valid 1 invalid
    assert( defectQC("Q1p1d0") == 0 );
    assert( defectQC("Q2p1d1Q4p3d1") == 2 );
    assert( defectQC("Q15p10d5") == 5 );
    assert( defectQC("Q2p1d1q4p3d1") == -1 );
    
    // Total Test Cases, 3 valid 1 invalid
    assert( totalQC("Q1p1q0") == 1 );
    assert( totalQC("Q2p1d1Q4p3d1") == 6 );
    assert( totalQC("Q15p10d5") == 15 );
    assert( totalQC("Q2p1d1q4p3d1") == -1 );

    // Batches Test Cases, 3 valid 1 invalid
    assert( batches("Q1p1q0") == 1 );
    assert( batches("Q2p1d1Q4p3d1") == 2 );
    assert( batches("Q15p10d5") == 1 );
    assert( batches("Q2p1d1q4p3d1") == -1 );
    
    cout << "All test cases succeeded" << endl;
    
    return 0;
}

int func(int n, double d) {
    int j = n;
    double sum = 0;
    while (j >= 0) {
        sum += d;
        -j;
        }
 return sum;
    }

bool isValidQC(string results){
    if (results.size() < 1) {              // empty string is invalid
        return false;
    }
    
    int i = 0;
    
    while (i < results.size()) {          // keeping index in bounds
        
        int pdCount = 0;
        int qCount = 0;
        
        string CurrentQ;                  // each batch count data is grabbed in string format
        
        if (results[i] != 'Q' || (results[i+1] == '0' || !isdigit(results[i+1])) ) { // first char in batch must be Q, followed by a non-zero digit
            return false;
            
        } else {                          // if prior requirements met
            i++;
            while (isdigit(results[i])) { // take all the numbers after Q until results[i] is not a digit
                CurrentQ += results[i];   // append to current batch number string
                i++;
            }
        }
        
        qCount = stoi(CurrentQ);        // convert Q count string to int

        if (results[i] != 'p' && results[i] != 'd') { // if the batch count is not followed by a p or d, string invalid
            return false;
        }
        
        int pCount = 0; // to keep track of the current batch's p and ds
        int dCount = 0;
        
        for (int j = 0; j <= 1; j++) { // loop twice - check once for d and once for p
            
            if ( (results[i] == 'p' && pCount > 0) || (results[i] == 'd' && dCount > 0) ) { // to make sure there is not more than 1 p or d in a batch
                return false;
            }
            
            if (results[i] == 'p') { // marking a p was present in this batch
                pCount++;
            }
            
            if (results[i] == 'd') { // marking a d was present in this batch
                dCount++;
            }
            
            i++;
            
            // if p/d not followed by a number, or has leading zeroes, invalid string
            if ( (!isdigit(results[i])) || (results[i] == '0' && isdigit(results[i+1])) ) {
                return false;
            }
            else {
                string pd;
                while (isdigit(results[i])) { // otherwise get digits after p or d
                    pd += results[i];
                    i++;
                }
                pdCount += stoi(pd); // convert p or d count to int
            }
        }
        
        if (pdCount != qCount) {  // if the p + d counts are not equal to the Q count, the string is invalid
            return false;
        }
    }
    return true; // if string valid return true
}

int passQC(string results) {
    if(isValidQC(results))
    {
        int pass1 = 0;                           // int to store number after p

        for (int i = 0; i < results.size(); i++)
        {
            if (results[i] == 'p')
            {
                i++;
                string pass2;
                while (isdigit(results[i])) {   // grab everything after p until it is not a number
                    pass2 += results[i];        // add string to variable
                    i++;
                }
                pass1 += stoi(pass2);          // convert string count to int
            }
        }
        return pass1;
    }
    else                                       // if the string is invalid, return -1
    {
        return -1;
    }
}

int defectQC(string results) {
    if(isValidQC(results))
    {
        int defect1 = 0;                      // int to store number after d

        for (int i = 0; i < results.size(); i++)
        {
            if (results[i] == 'd')
            {
                i++;
                string defect2;
                while (isdigit(results[i])) { // grab everything after d until it is not a number
                    defect2 += results[i];    // add string to variable
                    i++;
                }
                defect1 += stoi(defect2);     // convert string count to int
            }
        }
        return defect1;
    }
    else                                      // if the string is invalid, return -1
    {
        return -1;
    }
}


int totalQC (string results){
    if(isValidQC(results))
    {
        int test1 = 0;                         // int to store total tests

        for (int i = 0; i < results.size(); i++)
        {
            if (results[i] == 'Q')
            {
                i++;
                string test2;
                while (isdigit(results[i])) {  // grab everything after Q until it is not a number
                    test2 += results[i];       // add string to variable
                    i++;
                }
                test1 += stoi(test2);          // convert string count to int
            }
        }
        return test1;
    }
    else                                      // if the string is invalid, return -1
    {
        return -1;
    }
}
    
int batches (string results){
    if(isValidQC(results))
    {
        int batch_count = 0;                           // int to store batch count

        for (int i = 0; i < results.size(); i++)
        {
            if (results[i] == 'Q')                     // each time a Q is encountered, indicates another batch
            {
                batch_count++;
            }
        }
        return batch_count;
    }
    else
    {
        return -1;                                    // if the string is invalid, return -1
    }
}

