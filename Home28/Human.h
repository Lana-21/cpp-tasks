#pragma once
#include <iostream>
#include <cstring>
using namespace std;

class Human {
public:
    Human();
    Human(const char*, int);
    Human(const Human&);
    Human& operator=(const Human&);
    Human(Human&&);
    Human& operator=(Human&&);
    ~Human();

    inline const char* getName() const;
    inline int getAge() const;
    inline void setName(const char*);
    inline void setAge(int);

    friend ostream& operator<<(ostream& os, const Human& h) {
        os << "Name: " << h.getName() << ", Age: " << h.getAge();
        return os;
    }

    friend istream& operator>>(istream& is, Human& h) {
        char buffer[256];
        cout << "Enter name: ";
        is.getline(buffer, 256);
        h.setName(buffer);
        cout << "Enter age: ";
        is >> h.age;
        is.ignore();
        return is;
    }
private:
    char* name{ nullptr };
    int age{ 0 };
};

inline Human::Human() {
    cout << "Constructor Human(default): " << this << endl;
}
inline Human::Human(const char* fullName, int age) : age{ age } {
    setName(fullName);
    cout << "Constructor Human(parameter): " << this << endl;
}

inline Human::Human(const Human& h) : age{ h.age } {
    if (h.name != nullptr) {
        name = new char[strlen(h.name) + 1];
        strcpy_s(name, strlen(h.name) + 1, h.name);
    }
    cout << "Constructor Human(copy): " << this << endl;
}
inline Human& Human::operator=(const Human& h) {
    delete[] name;
    name = nullptr;
    age = h.age;
    if (h.name != nullptr) {
        name = new char[strlen(h.name) + 1];
        strcpy_s(name, strlen(h.name) + 1, h.name);
    }
    return *this;
}

inline Human::Human(Human&& h) : name{ h.name }, age{ h.age } {
    h.name = nullptr;
    h.age = 0;
    cout << "Constructor Human(move): " << this << endl;
}
inline Human& Human::operator=(Human&& h) {
    delete[] name;
    name = h.name;
    age = h.age;
    h.name = nullptr;
    h.age = 0;
    return *this;
}

inline Human::~Human() {
    if (name != nullptr) {
        delete[] name;
    }
    cout << "Delete Human object: " << this << endl;
}

inline const char* Human::getName() const { return (name != nullptr) ? name : "NoName"; }
inline int Human::getAge() const { return age; }

void Human::setName(const char* fullName) {
    if (fullName != nullptr && strlen(fullName) != 0) {
        delete[] name;
        name = new char[strlen(fullName) + 1];
        strcpy_s(name, strlen(fullName) + 1, fullName);
    }
}
inline void Human::setAge(int a) { age = a; }
