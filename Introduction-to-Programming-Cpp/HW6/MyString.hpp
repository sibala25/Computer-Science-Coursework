#ifndef MyString_hpp
#define MyString_hpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
class MyString {
public:
    MyString():s(0){}
    MyString(char c):s(1,c){}
    MyString substr(size_t pos,size_t len=-1) const;
    size_t find(char c,size_t pos=0) const;
    size_t rfind(char c,size_t pos=-1) const;
    size_t find(const MyString& str,size_t pos=0) const;
    size_t rfind(const MyString& str,size_t pos=-1) const;
    MyString(size_t n,char c):s(n,c){}
    size_t size(const MyString&) const {return(s.size());}
    size_t length(const MyString&) const {return(s.size());}
    bool empty(const MyString&) const {return(s.size()==0);}
    void push_back(char x){s.push_back(x);};
    void pop_back(){s.pop_back();};
    void resize(size_t n){s.resize(n,'0');};
    void resize(size_t n,char c){s.resize(n,c);};
private:
    std::vector<char> s;
#include "students-ignore1.h"
};
#include "students-ignore2.h"
#endif
