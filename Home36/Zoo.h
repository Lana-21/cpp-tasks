#pragma once
#include <iostream>
#include <cstdlib>
#include <format>
#include "Animal.h"
#include "Exceptions.h"
using namespace std;

class Zoo {
public:
    Zoo();
    ~Zoo();
    void addAnimal(Animal* animal);
    void makeRandomSick();
    void printSortCount() const;
    void printBudget() const;
    void saveToTextFile(const string& filename) const;
    void loadFromTextFile(const string& filename);
    friend ostream& operator<<(ostream& os, const Zoo& zoo);
private:
    Animal** animals;
    int count;
    int capacity;
};
