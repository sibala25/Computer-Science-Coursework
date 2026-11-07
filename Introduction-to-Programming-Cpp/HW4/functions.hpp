#ifndef functions_hpp
#define functions_hpp
#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <utility>
bool leap_year(int year);
void fib(int N);
double get_double(std::string prompt);
void printMyVector(const std::vector<int>& v);
std::vector<int> concatenateMyVectors(const std::vector<int>& v, const std::vector<int>& w);
void sort5(int& i1, int& i2, int& i3, int& i4, int& i5);
void reverse(std::vector<int>& v);
void print(const std::vector<bool>& v);
void addZeros(std::vector<bool>& v, size_t numberToAdd);
std::vector<bool> addition(std::vector<bool> v, std::vector<bool> w);
#endif
