#include "MyString.hpp"
size_t MyString::find(char c,size_t pos) const {
    for(size_t i=pos;i<s.size();i++) if(s[i]==c)return i;
    return -1;
}
size_t MyString::rfind(char c,size_t pos) const {
    if(pos!=-1) {
        if(pos<s.size()) {
            for(size_t i=pos;i>0;--i){if(s.size()==0)return -1;if(s[i]==c)return i;}
            return -1;
        } else {
            for(size_t i=s.size()-1;i>0;--i){if(s.size()==0)return -1;if(s[i]==c)return i;}
        }
    } else {
        for(size_t i=s.size()-1;i>0;--i){if(s.size()==0)return -1;if(s[i]==c)return i;}
        return -1;
    }
    return -1;
}
MyString MyString::substr(size_t pos,size_t len) const {
    MyString subs="";
    if(len==-1){for(size_t i=pos;i<s.size();i++)subs.push_back(s[i]);}
    if(len!=-1){size_t compare=0;for(size_t i=pos;len>compare&&i<s.size();++compare&&i++)subs.push_back(s[i]);}
    return subs;
}
size_t MyString::find(const MyString& str,size_t pos) const {
    if(pos<s.size()) {
        for(size_t i=pos;i<s.size();i++){
            bool allMatch=true;
            for(size_t j=0;j<str.s.size();j++){
                if(i+j>=s.size())allMatch=false;
                else if(s[i+j]!=str.s[j])allMatch=false;
            }
            if(allMatch==true)return i;
        }
        return -1;
    } else if(pos==s.size()){
        if(str.s.size()==0)return s.size();
        else return -1;
        return s.size();
    } else if(pos>s.size())return -1;
    return -1;
}
size_t MyString::rfind(const MyString& str,size_t pos) const {
    if(pos<s.size()&&pos!=-1&&str.s.size()!=0){
        if(s.size()==0)return -1;
        else {
            for(size_t i=pos;i!=-1;i--){
                bool allMatch=true;
                for(size_t j=0;j<str.s.size();j++){
                    if(i+j>=s.size())allMatch=false;
                    else if(s[i+j]!=str.s[j])allMatch=false;
                }
                if(allMatch==true)return i;
            }
            return -1;
        }
    } else if((pos>=s.size()||pos==-1)&&str.s.size()!=0){
        if(s.size()==0)return -1;
        else {
            for(size_t i=s.size()-1;i!=-1;i--){
                bool allMatch=true;
                for(size_t j=0;j<str.s.size();j++){
                    if(i+j>=s.size())allMatch=false;
                    else if(s[i+j]!=str.s[j])allMatch=false;
                }
                if(allMatch==true)return i;
            }
            return -1;
        }
    } else if(str.s.size()==0&&(pos==-1||pos>=s.size()))return s.size();
    else if(str.s.size()==0&&pos<s.size())return pos;
    return -1;
}
#include "students-ignore3.h"
