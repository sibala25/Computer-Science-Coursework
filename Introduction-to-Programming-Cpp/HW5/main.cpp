#include <iostream>
#include "Fracs.hpp"
#include "ComplexFracs.hpp"
using namespace std;

int main() {

//    for (int den1=1; den1<10; ++den1) {
//        for (int num1=0; num1<den1; ++num1) {
//            for (int den2=1; den2<10; ++den2) {
//                for (int num2=1; num2<den2; ++num2) {
//                    const Frac f1(num1,den1);
//                    const Frac f2(num2,den2);
//
//                    f1.print();            cout << " / ";
//                    f2.print();            cout << " = ";
//                    f1.divide(f2).print(); cout <<  endl;
//                }
//            }
//        }
//    }
//    cout << endl;

    // a
    cout << "1/2: ";
    Frac f1 (3,6);
    ComplexFrac a (f1);
    a.print(); cout << endl;
    
    // b
    cout << "1/2 + 1/3*i: ";
    Frac f2 (1,2);
    Frac f3 (2,6);
    ComplexFrac b (f2, f3);
    b.print(); cout << endl;
             
    // c
    cout << "2: ";
    ComplexFrac c (2);
    c.print(); cout << endl;
    
    // d
    cout << "1/2 + 3/4*i: ";
    ComplexFrac d (1,2,3,4);
    d.print(); cout << endl;
    
    cout << "1 and 0: " << endl;
    cout << f1.isEqual(f2) << endl;
    cout << f2.isEqual(f3) << endl;
    
    cout << "add+subtract" << endl;
    ComplexFrac e (1,2,3,4);
    ComplexFrac f (5,6,7,8);
    
    cout << "4/3 + 13/8*i: " ;
    (e.add(f)).print();
    cout << endl;

    cout << "-1/3 - 1/8*i: ";
    (e.subtract(f)).print();
    cout << endl;
    
    cout<< "multiply+divide" << endl;
    cout << "-23/96 + 17/16*i: " ;
    (e.multiply(f)).print();
    cout << endl;
    
    cout << "618/841 + 108/841*i: " ;
    (e.divide(f)).print();
    cout << endl;
    
    const ComplexFrac z;
    z.print(); cout << endl;
    
    return 0;
}
