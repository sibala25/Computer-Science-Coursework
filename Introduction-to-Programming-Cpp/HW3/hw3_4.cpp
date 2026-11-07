#include <iostream>
using namespace std;
int main() {
    cout << "Type an integer bigger than or equal to 0: " << endl;
    int N; cin >> N;
    cout << "The first " << N << " Fibonacci numbers are: " << endl;
    int one=0,two=1,next,i;
    for(i=0;i<N;++i) {
        next=one+two;
        cout << two << " ";
        one=two;
        two=next;
    }
    cout << endl;
    return 0;
}
