#include "ComplexFracs.hpp"
void ComplexFrac::print() const {
    if(!real.isZero()){real.print();if(imag.isPositive())std::cout<<"+";}
    if(!imag.isZero()){imag.print();std::cout<<"*i";}
    if(real.isZero()&&imag.isZero())std::cout<<0;
}
ComplexFrac ComplexFrac::add(const ComplexFrac& other) const {
    return ComplexFrac((real.add(other.real)),(imag.add(other.imag)));
}
ComplexFrac ComplexFrac::subtract(const ComplexFrac& other) const {
    return ComplexFrac((real.subtract(other.real)),(imag.subtract(other.imag)));
}
ComplexFrac ComplexFrac::multiply(const ComplexFrac& other) const {
    Frac aC(real.multiply(other.real));
    Frac bD(imag.multiply(other.imag));
    Frac aD(real.multiply(other.imag));
    Frac bC(imag.multiply(other.real));
    Frac firstMultiply(aC.subtract(bD));
    Frac secondMultiply(aD.add(bC));
    return ComplexFrac(firstMultiply,secondMultiply);
}
ComplexFrac ComplexFrac::divide(const ComplexFrac& other) const {
    ComplexFrac aAndB(real,imag);
    Frac cSquared(other.real.multiply(other.real));
    Frac dSquared(other.imag.multiply(other.imag));
    Frac denom(cSquared.add(dSquared));
    Frac first(other.real.divide(denom));
    Frac zero(0);
    Frac second(other.imag.divide(denom));
    Frac negativeSecond(zero.subtract(second));
    ComplexFrac total(first,negativeSecond);
    ComplexFrac answer(aAndB.multiply(total));
    return answer;
}
