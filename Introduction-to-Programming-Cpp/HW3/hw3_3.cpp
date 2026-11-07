#include <iostream>
#include <string>
#include <cmath>
using namespace std;
int main() {
    char response='y';
    while(response=='y') {
        cout << "Enter a list of integers: " << endl;
        int max=pow(-2,31);
        int min=(pow(2,31)-1);
        while(true) {
            int i; cin >> i;
            while(cin.peek()==' ') cin.ignore();
            if(i>max) max=i;
            if(i<min) min=i;
            if(cin.peek()=='\n') break;
        }
        cout << "The max of the integers you entered is " << max << endl;
        cout << "The min of the integers you entered is " << min << endl << endl;
        cout << "Continue? (y/n)" << endl;
        cin >> response;
        if(response=='y') cout << endl;
    }
    return 0;
}
