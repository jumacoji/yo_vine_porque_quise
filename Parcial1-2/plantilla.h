#ifndef PLANTILLA_H
#define PLANTILLA_H
#include <iostream>
#include <iomanip>
using namespace std;


template<typename T> void printElement(T t, const int& width){
    cout << left << setw(width) << setfill(' ') << t;
}

#endif // PLANTILLA_H
