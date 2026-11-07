#include <iostream>
#include <string>
using namespace std;
int main() {
    cout << "Please enter an integer from 0 to 9: ";
    int s; cin >> s;
    string str1 = "zero  one   two   three four  five  six   seven eight nine";
    cout << str1.substr(6*s,5) << endl;
    return 0;
}
