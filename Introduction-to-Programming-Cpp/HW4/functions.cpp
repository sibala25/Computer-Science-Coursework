#include "functions.hpp"
bool leap_year(int year) {
    if ((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0))) return true;
    else return false;
}
void fib(int N) {
    assert(0 <= N && N <= 46);
    int one=0, two=1, next, i;
    for(i=0;i<N;++i){next=one+two;std::cout<<two<<" ";one=two;two=next;}
}
double get_double(std::string prompt) {
    std::cout<<prompt<<" ";
    double x; std::cin>>x;
    if(!std::cin.fail()) return x;
    else {std::cout<<"cin failed, so 0 was returned."<<std::endl;return 0.0;}
}
void printMyVector(const std::vector<int>& v) {
    for(size_t i=0,N=v.size();i<N;++i) std::cout<<v[i]<<' ';
    std::cout<<std::endl;
}
std::vector<int> concatenateMyVectors(const std::vector<int>& v,const std::vector<int>& w) {
    std::vector<int> x;
    for(size_t i=0,N=v.size();i<N;++i) x.push_back(v[i]);
    for(size_t i=0,N=w.size();i<N;++i) x.push_back(w[i]);
    return std::vector<int>(x);
}
void sort5(int& i1,int& i2,int& i3,int& i4,int& i5) {
    if(i1>i2) std::swap(i1,i2);
    if(i3>i4) std::swap(i3,i4);
    if(i1>i3) std::swap(i1,i3);
    if(i2>i4) std::swap(i2,i4);
    if(i2>i3) std::swap(i2,i3);
    if(i5>i1&&i5>i2&&i5>i3&&i5<i4) std::swap(i4,i5);
    if(i5>i1&&i5>i2&&i5<i3&&i5<i4){std::swap(i3,i5);std::swap(i4,i5);}
    if(i5>i1&&i5<i2&&i5<i3&&i5<i4){std::swap(i2,i5);std::swap(i3,i5);std::swap(i4,i5);}
    if(i5<i1&&i5<i2&&i5<i3&&i5<i4){std::swap(i1,i5);std::swap(i2,i5);std::swap(i3,i5);std::swap(i4,i5);}
}
void reverse(std::vector<int>& v) {
    size_t N=v.size();
    for(int i=0;i<N/2;i++) std::swap(v.at(i),v[N-1-i]);
}
void print(const std::vector<bool>& v) {
    for(bool i:v) std::cout<<i;
    std::cout<<std::endl;
}
void addZeros(std::vector<bool>& v,size_t numberToAdd) {
    for(size_t i=0,N=numberToAdd;i<N;++i) v.push_back(0);
}
std::vector<bool> addition(std::vector<bool> v,std::vector<bool> w) {
    size_t lengthv=v.size(),lengthw=w.size();
    if(lengthv<lengthw){for(int i=0;i<lengthw-lengthv;i++) addZeros(v,1);}
    else if(lengthw<lengthv){for(int i=0;i<lengthv-lengthw;i++) addZeros(w,1);}
    std::vector<bool> x;
    bool old_carry=0,new_carry=0;
    for(size_t i=0,N=v.size();i<N;++i) {
        if(old_carry==0&&v[i]==0&&w[i]==0){x.push_back(0);new_carry=0;}
        if((old_carry==0&&v[i]==0&&w[i]==1)||(old_carry==0&&v[i]==1&&w[i]==0)||(old_carry==1&&v[i]==0&&w[i]==0)){x.push_back(1);new_carry=0;}
        if((old_carry==0&&v[i]==1&&w[i]==1)||(old_carry==1&&v[i]==0&&w[i]==1)||(old_carry==1&&v[i]==1&&w[i]==0)){x.push_back(0);new_carry=1;}
        if(old_carry==1&&v[i]==1&&w[i]==1){x.push_back(1);new_carry=1;}
        old_carry=new_carry;
    }
    if(old_carry==1)x.push_back(1);
    return std::vector<bool>(x);
}
