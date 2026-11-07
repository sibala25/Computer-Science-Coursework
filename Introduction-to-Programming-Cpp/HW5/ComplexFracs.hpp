#ifndef ComplexFracs_hpp
#define ComplexFracs_hpp
#include "Fracs.hpp"
class ComplexFrac {
public:
    ComplexFrac():real(0),imag(0){}
    ComplexFrac(Frac n):real(n),imag(0){}
    ComplexFrac(Frac _real,Frac _imag):real(_real),imag(_imag){}
    ComplexFrac(int n):real(n),imag(0){}
    ComplexFrac(int _renum,int _reden,int _imnum,int _imden):real(_renum,_reden),imag(_imnum,_imden){};
    bool isEqual(const ComplexFrac& other) const {return(real.isEqual(other.real))&&(imag.isEqual(other.imag));}
    ComplexFrac add(const ComplexFrac& other) const;
    ComplexFrac subtract(const ComplexFrac& other) const;
    ComplexFrac multiply(const ComplexFrac& other) const;
    ComplexFrac divide(const ComplexFrac& other) const;
    void print() const;
private:
    Frac real,imag;
};
#endif
