#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
int main() {
    cout << fixed << setprecision(2);
    double(x);
    cout << "Amount due: $"; cin >> x;
    double(y);
    cout << "Amount received: $"; cin >> y;
    cout << endl << "Change given: " << endl;
    int a = rint(x*100);
    int b = rint(y*100);
    int c = abs((a - b)%100);
    int d = c%25;
    int e = d%10;
    int f = e%5;
    cout << "dollars -> " << abs((a - b)/100) << endl;
    cout << "quarters -> " << c/25 << endl;
    cout << "dimes -> " << d/10 << endl;
    cout << "nickels -> " << e/5 << endl;
    cout << "pennies -> " << f << endl;
    return 0;
}
