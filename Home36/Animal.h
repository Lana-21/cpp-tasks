#pragma once
#include <string>
#include <iostream>
#include <format>
#include "Exceptions.h"
using namespace std;

class Animal {
public:
    Animal(string name, string sort, double food, string foodType, int age);
    virtual ~Animal() {}
    virtual void makeSound() const = 0;
    virtual void writeSpecificData(ofstream& fout) const = 0;
    virtual void readSpecificData(ifstream& fin) = 0;
    string getName() const { return name; }
    string getSort() const { return sort; }
    double getDailyFood() const { return dailyFood; }
    string getFoodType() const { return foodType; }
    int getAge() const { return age; }
    bool getIsHealthy() const { return isHealthy; }
    void setDailyFood(double food);
    void setAge(int newAge);
    void setHealthStatus(bool status) { isHealthy = status; }
    virtual string getInfo() const;
protected:
    string name;
    string sort;
    double dailyFood;
    string foodType;
    int age;
    bool isHealthy;
};
class Tiger : public Animal {
public:
    Tiger(string name, int age, int stripes);
    int getStripeCount() const { return stripeCount; }
    void makeSound() const;
    void writeSpecificData(ofstream& fout) const;
    void readSpecificData(ifstream& fin);
    string getInfo() const;
private:
    int stripeCount;
};
class Crocodile : public Animal {
public:
    Crocodile(string name, int age, double length);
    double getBodyLength() const { return bodyLength; }
    void makeSound() const;
    void writeSpecificData(ofstream& fout) const;
    void readSpecificData(ifstream& fin);
    string getInfo() const;
private:
    double bodyLength;
};
class Kangaroo : public Animal {
public:
    Kangaroo(string name, int age, double jump);
    double getJumpHeight() const { return jumpHeight; }
    void makeSound() const;
    void writeSpecificData(ofstream& fout) const;
    void readSpecificData(ifstream& fin);
    string getInfo() const;
private:
    double jumpHeight;
};