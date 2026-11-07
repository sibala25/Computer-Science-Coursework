#include <iostream>
#include <string>
using namespace std;
int main() {
    cout << "Give me a cubic polynomial in the form" << endl << "f(x)=[a]*x^3+[b]*x^2+[c]*x+[d]" << endl << "and I'll return the derivative evaluated at x=2." << endl << endl;
    string s; cin >> s;
    const string xCubed="*x^3";
    const string xSquared="*x^2";
    size_t firstS=s.find("*");
    size_t secondS=s.rfind("*",2);
    size_t firstP=s.find("x^3");
    size_t secondP=s.find("x^2");
    size_t lastS=s.rfind("*");
    string firstCo=s.substr(5,firstS);
    string secondCo=s.substr(firstP+xCubed.length(),secondS);
    string thirdCo=s.substr(secondP+xSquared.length(),lastS);
    const size_t ADD=3;
    size_t firstX=s.find("x^3");
    size_t secondX=s.find("x^2");
    char sign1=s.at(firstX+ADD);
    char sign2=s.at(secondX+ADD);
    string y(1,sign1);
    string z(1,sign2);
    string d=y+secondCo;
    string e=z+thirdCo;
    double a=stod(firstCo);
    double b=stod(d);
    double c=stod(e);
    double g=a*12;
    double h=b*4;
    double i=g+h+c;
    cout << "The derivative evaluated at x=2 is " << i << endl;
    return 0;
}
