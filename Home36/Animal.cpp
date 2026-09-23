#include "Animal.h"
#include <iostream>
#include <fstream>
#include <format>
using namespace std;

Animal::Animal(string name, string sort, double food, string foodType, int age)
    : name(name), sort(sort), foodType(foodType), isHealthy(true) {
    if (age < 0 || age > 150) {
        throw AnimalAgeException("Invalid animal age!");
    }
    if (food <= 0) {
        throw FoodAmountException("Daily food amount must be positive!");
    }
    this->age = age;
    this->dailyFood = food;
}
void Animal::setDailyFood(double food) {
    if (food <= 0) {
        throw FoodAmountException("Food amount must be greater than zero!");
    }
    dailyFood = food;
}
void Animal::setAge(int newAge) {
    if (newAge <= age) {
        throw AnimalAgeException("New age must be greater than current age!");
    }
    age = newAge;
}
string Animal::getInfo() const {
    string status = isHealthy ? "Healthy" : "Needs Doctor";
    return format("{} ({}, {} y.o.) - Status: {}", name, sort, age, status);
}
Tiger::Tiger(string name, int age, int stripes)
    : Animal(name, "Tiger", 9.0, "Meat", age), stripeCount(stripes) {
}
void Tiger::makeSound() const { cout << "Rooaar!"; }
void Tiger::writeSpecificData(ofstream& fout) const {
    fout << stripeCount << endl;
}
void Tiger::readSpecificData(ifstream& fin) {
    fin >> stripeCount;
}
string Tiger::getInfo() const {
    return Animal::getInfo() + format(" Stripes: {}", stripeCount);
}
Crocodile::Crocodile(string name, int age, double length)
    : Animal(name, "Crocodile", 4.0, "Fish", age), bodyLength(length) {
}
void Crocodile::makeSound() const { cout << "Snap!"; }
void Crocodile::writeSpecificData(ofstream& fout) const {
    fout << bodyLength << endl;
}
void Crocodile::readSpecificData(ifstream& fin) {
    fin >> bodyLength;
}
string Crocodile::getInfo() const {
    return Animal::getInfo() + format(" Length: {} m", bodyLength);
}
Kangaroo::Kangaroo(string name, int age, double jump)
    : Animal(name, "Kangaroo", 3.0, "Grass", age), jumpHeight(jump) {
}
void Kangaroo::makeSound() const { cout << "Hop-Hop!"; }
void Kangaroo::writeSpecificData(ofstream& fout) const {
    fout << jumpHeight << endl;
}
void Kangaroo::readSpecificData(ifstream& fin) {
    fin >> jumpHeight;
}
string Kangaroo::getInfo() const {
    return Animal::getInfo() + format(" Jump: {} m", jumpHeight);
}
