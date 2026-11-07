#include <iostream>
#include <string>
#include <utility>
using namespace std;
int main() {
    cout << "Enter four integers separated by spaces:" << endl;
    int i,j,x,y;
    cin >> i >> j >> x >> y;
    if(i>j) swap(i,j);
    if(x>y) swap(x,y);
    if(i>x) swap(i,x);
    if(j>y) swap(j,y);
    if(j>x) swap(j,x);
    cout << "I've arranged them in order:" << endl << i << ' ' << j << ' ' << x << ' ' << y << endl;
    return 0;
}
