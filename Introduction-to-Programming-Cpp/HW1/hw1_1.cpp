#include <iostream>
#include <cmath>
using namespace std;
int main() {
    int x; cout << "Enter the first integer: "; cin >> x;
    int y; cout << "Enter the second integer: "; cin >> y;
    int sum = x + y; cout << "their sum is " << sum << endl;
    int difference = x - y; cout << "their difference is " << difference << endl;
    int product = x * y; cout << "their product is " << product << endl;
    double average = (x + y)/2.0; cout << "their average is " << average << endl;
    cout << "their distance is " << abs(x-y) << endl;
    cout << "their maximum is " << max(x,y) << endl;
    cout << "their minimum is " << min(x,y) << endl;
    cout << "the power of the first integer to the second integer is " << pow(x,y) << endl;
    return 0;
}
