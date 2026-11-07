#include <iostream>
using namespace std;
int main() {
    int x; cout << "Please enter the first time: "; cin >> x;
    int y; cout << "Please enter the second time: "; cin >> y;
    x = (x/100)*60 + (x%100);
    y = (y/100)*60 + (y%100);
    cout << ((y + 1440 - x)%1440)/60 << " hours " << abs(((y + 1440 - x)%1440)%60) << " minutes" << endl;
    return 0;
}
