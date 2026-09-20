#pragma once
#include <exception>
#include <string>
using namespace std;

class ZooException : public exception {
public:
    ZooException(const string& message) : message{ message } {}
    const char* what() const noexcept override {
        return message.c_str();
    }
private:
    string message;
};
class AnimalAgeException : public ZooException {
public:
    AnimalAgeException(const string& message) : ZooException(message) {}
};
class FoodAmountException : public ZooException {
public:
    FoodAmountException(const string& message) : ZooException(message) {}
};
class ZooFullException : public ZooException {
public:
    ZooFullException(const string& message) : ZooException(message) {}
};
