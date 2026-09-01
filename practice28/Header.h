#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

class Array {

public:
    Array(int);
    Array(const Array&);
    Array& operator=(const Array&);
    ~Array();

    int getSize() const;
    int getElement(int idx) const;
    void setElement(int idx, int value);
    void setSize(int newSize);

    void randomize();
    void resize(int newSize);
    void sortArray();
    int getMin() const;
    int getMax() const;

    int operator[](int idx) const;
    int& operator[](int idx);
    void operator()(int val);

    explicit operator int() const;
    operator char* () const;

    bool operator>(const Array& ar) const;
    bool operator<(const Array& ar) const;
    friend ostream& operator<<(ostream& s, const Array& a);

private:
    int* arr;
    int size;
};

inline Array::Array(int s) {
    size = s;
    if (size > 0) {
        arr = new int[size] { 0 };
    }
    else {
        arr = nullptr;
    }
}

inline Array::Array(const Array& ar) {
    size = ar.size;
    if (size > 0) {
        arr = new int[size];
        for (int i = 0; i < size; i++) {
            arr[i] = ar.arr[i];
        }
    }
    else {
        arr = nullptr;
    }
}
inline Array& Array::operator=(const Array& ar) {
    size = ar.size;
    delete[] arr;
    arr = nullptr;
    if (ar.arr != nullptr && size > 0) {
        arr = new int[size];
        for (int i = 0; i < size; i++) {
            arr[i] = ar.arr[i];
        }
    }
    return *this;
}
inline Array::~Array() {
    delete[] arr;
    cout << "Delete array object: " << this << endl;
}

inline int Array::getSize() const {
    return size;
}
inline int Array::getElement(int idx) const {
    assert(idx >= 0 && idx < size && "Index is out of range!");
    return arr[idx];
}
inline void Array::setSize(int newSize) {
    resize(newSize);
}
inline void Array::setElement(int idx, int value) {
    assert(idx >= 0 && idx < size && "Index is out of range!");
    arr[idx] = value;
}

inline void Array::randomize() {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
    }
}

inline void Array::resize(int newSize) {
    if (newSize == size) return;
    int* newArr = new int[newSize] { 0 };
    int minSize = (size < newSize) ? size : newSize;
    for (int i = 0; i < minSize; i++) {
        newArr[i] = arr[i];
    }
    delete[] arr;
    arr = newArr;
    size = newSize;
}
inline void Array::sortArray() {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

inline int Array::getMin() const {
    if (size == 0) return 0;
    int minVal = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < minVal) minVal = arr[i];
    }
    return minVal;
}
inline int Array::getMax() const {
    if (size == 0) return 0;
    int maxVal = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > maxVal) maxVal = arr[i];
    }
    return maxVal;
}

inline int Array::operator[](int idx) const {
    assert(idx >= 0 && idx < size && "Index is out of range!");
    return arr[idx];
}
inline int& Array::operator[](int idx) {
    assert(idx >= 0 && idx < size && "Index is out of range!");
    return arr[idx];
}
inline void Array::operator()(int val) {
    for (int i = 0; i < size; i++) {
        arr[i] += val;
    }
}

inline Array::operator int() const {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}
inline Array::operator char* () const {
    char* str = new char[1024] {""};
    char buf[16];
    for (int i = 0; i < size; i++) {
        sprintf(buf, "%d", arr[i]);
        strcat(str, buf);
        if (i < size - 1) {
            strcat(str, " "); 
        }
    }
    return str;
}

inline bool Array::operator>(const Array& ar) const {
    int sum1 = 0;
    for (int i = 0; i < size; i++) {
        sum1 += arr[i];
    }
    int sum2 = 0;
    for (int i = 0; i < ar.size; i++) {
        sum2 += ar.arr[i];
    }

    return sum1 > sum2;
}
inline bool Array::operator<(const Array& ar) const {
    int count1 = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] > 31) ++count1;
    }
    int count2 = 0;
    for (int i = 0; i < ar.size; i++) {
        if (ar.arr[i] > 31) ++count2;
    }
    return count1 < count2;
}

inline ostream& operator<<(ostream& s, const Array& a) {
    for (int i = 0; i < a.size; i++) {
        s << a.arr[i] << " ";
    }
    return s;
}