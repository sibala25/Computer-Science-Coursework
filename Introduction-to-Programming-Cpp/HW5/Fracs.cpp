#include "Fracs.hpp"
Frac Frac::add(const Frac& other) const {return Frac(num*other.den+other.num*den,den*other.den);}
Frac Frac::subtract(const Frac& other) const {return Frac(num*other.den-other.num*den,den*other.den);}
Frac Frac::multiply(const Frac& other) const {return Frac(num*other.num,den*other.den);}
Frac Frac::divide(const Frac& other) const {return Frac(num*other.den,den*other.num);}
void Frac::simplify() {
    makeZeroNice();
    for(int d=std::min(abs(num),den);d>1;--d){
        if((num%d==0)&&(den%d==0)){num/=d;den/=d;break;}
    }
}
void Frac::Esimplify() {
    int a=abs(num),b=den;
    while(b!=0){int r=a%b;a=b;b=r;}
    num/=a;den/=a;
}
