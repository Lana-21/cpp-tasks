#include "Zoo.h"
using namespace std;

Zoo::Zoo(int capacity) : count(0), capacity(capacity) {
    if (capacity <= 0) {
        throw ZooException("Capacity must be greater than zero!");
    }
    animals = new Animal * [capacity];
}
Zoo::~Zoo() {
    for (int i = 0; i < count; ++i) {
        delete animals[i];
    }
    delete[] animals; 
}
void Zoo::addAnimal(Animal* animal) {
    if (count >= capacity) {
        delete animal; 
        throw ZooFullException("Cannot add animal: Zoo has maximum capacity!");
    }
    animals[count++] = animal;
}
void Zoo::makeRandomSick() {
    if (count == 0) return;
    int randomIndex = rand() % count;
    animals[randomIndex]->setHealthStatus(false);
    cout << format("\nAnimal {} ({}) got sick!",
        animals[randomIndex]->getName(),
        animals[randomIndex]->getSort()) << endl;
}
void Zoo::printSortCount() const {
    int tigerCount = 0, crocodileCount = 0, kangarooCount = 0;
    for (int i = 0; i < count; ++i) {
        if (animals[i]->getSort() == "Tiger") tigerCount++;
        else if (animals[i]->getSort() == "Crocodile") crocodileCount++;
        else if (animals[i]->getSort() == "Kangaroo") kangarooCount++;
    }
    cout << "\nSORT COUNT:" << endl;
    cout << format("Tigers: {}", tigerCount) << endl;
    cout << format("Crocodiles: {}", crocodileCount) << endl;
    cout << format("Kangaroos: {}", kangarooCount) << endl;
    cout << format("Total animals: {}", count) << endl;
}
void Zoo::printBudget() const {
    double totalMeat = 0, totalFish = 0, totalGrass = 0;
    for (int i = 0; i < count; ++i) {
        if (animals[i]->getFoodType() == "Meat") totalMeat += animals[i]->getDailyFood();
        else if (animals[i]->getFoodType() == "Fish") totalFish += animals[i]->getDailyFood();
        else if (animals[i]->getFoodType() == "Grass") totalGrass += animals[i]->getDailyFood();
    }
    double totalCost = (totalMeat * 250) + (totalFish * 220) + (totalGrass * 60);
    cout << "\nDAILY FOOD" << endl;
    cout << format("Meat: {} kg // Fish: {} kg // Grass: {} kg", totalMeat, totalFish, totalGrass) << endl;
    cout << format("Daily Budget: {} UAH", totalCost) << endl;
}
ostream& operator<<(ostream& os, const Zoo& zoo) {
    os << "ANIMALS:" << endl;
    for (int i = 0; i < zoo.count; ++i) {
        os << zoo.animals[i]->getInfo()
            << " Food: " << zoo.animals[i]->getDailyFood() << " kg " << zoo.animals[i]->getFoodType()
            << " Sound: ";
        zoo.animals[i]->makeSound();
        os << endl;
    }
    return os;
}
