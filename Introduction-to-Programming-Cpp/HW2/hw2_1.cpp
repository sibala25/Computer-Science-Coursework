#include <iostream>
#include <string>
using namespace std;
int main() {
    cout << "Please enter the money in the European convention (commas): ";
    string s; cin >> s;
    s.at(s.find(",")) = '.';
    cout << "The money in the English-speaking convention (period) is: " << s << endl;
    return 0;
}
