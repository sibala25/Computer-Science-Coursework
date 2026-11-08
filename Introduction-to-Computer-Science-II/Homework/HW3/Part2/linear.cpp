bool allFalse(const string a[], int n);
int countFalse(const string a[], int n);
int firstFalse(const string a[], int n);
int indexOfMax(const string a[], int n);
bool has(const string a1[], int n1, const string a2[], int n2);

// Return false if the somePredicate function returns true for at least one of the array elements; return true otherwise.
bool allFalse(const string a[], int n) {
    if (n == 0) {
        return true;
    }
    return (!somePredicate(a[n-1]) && allFalse(a, n-1));
}

// Return the number of elements in the array for which the somePredicate function returns false.
int countFalse(const string a[], int n) {
    if (n == 0) {
        return 0;
    }
    return (!somePredicate(a[n-1]) + countFalse(a, n-1));
}

// Return the subscript of the first element in the array for which the somePredicate function returns false.
// If there is no such element, return -1.
int firstFalse(const string a[], int n) {
    if (n == 0) {
        return -1;
    }
    if (!somePredicate(a[0])) {
        return 0;
    }
    
    int store = firstFalse(a+1, n-1);
    if (store == -1) {
        return -1;
    } else {
        store++;
    }
    return store;
}

// Return the subscript of the greatest string in the array (i.e., return the smallest subscript m such that a[m] >= a[k] for all
// k from 0 to n-1).  If the function is told that no strings are to be considered to be in the array, return -1.
int indexOfMax(const string a[], int n) {
    if (n <= 0) {
        return -1;
    }
    if (n == 1) {
        return 0;
    }
    int max = indexOfMax(a+1, n-1)+1;
    if (a[0] >= a[max]) {
        return 0;
    }
    return max;
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then return true

// otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.

// a2 is empty/n2 is 0, return true.

// For example, if a1 is the 7 element array
//    "john" "amy" "ketanji" "sonia" "amy" "ketanji" "elena"
// then the function should return true if a2 is
//    "amy" "sonia" "elena"
// or
//    "amy" "ketanji" "ketanji"
// and it should return false if a2 is
//    "amy" "elena" "sonia"
// or
//    "john" "sonia" "sonia"
bool has(const string a1[], int n1, const string a2[], int n2) {
    // if n2 0, return true
    if (n2 == 0) {
        return true;
    }
    // if a1 is empty, but a2 is not, return false
    // if more a2 elem tham a1, return false
    if ((n1 == 0 && n2 != 0) || (n2 > n1)) {
        return false;
    }
    // if there is a match remove from second array
    if (a1[0] == a2[0]) {
        return has(a1+1, n1-1, a2+1, n2-1);
    }
    // if no match, do not remove from second array
    return has(a1+1, n1-1, a2, n2);
}
