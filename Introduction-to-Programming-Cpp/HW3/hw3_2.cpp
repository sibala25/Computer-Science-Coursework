#include <iostream>
#include <string>
using namespace std;
int main() {
    cout << "Enter a strictly positive integer: " << endl;
    unsigned int x; cin >> x;
    if(x==0) {cout << "This number is not STRICTLY positive" << endl; return 0;}
    int y; string a; string reverse="";
    const int two=2;
    const int conversion=48;
    cout << "The binary representation of " << x << " is given by ";
    do {
        y=x%two;
        x=x/two;
        char i=y+conversion;
        a=a+i;
    } while(x!=0);
    for(int length=static_cast<int>(a.length()-1); length>=0; length--) reverse+=a[length];
    cout << reverse << endl;
    return 0;
}
