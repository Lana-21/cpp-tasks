#include "Zoo.h"
#include <fstream>
#include <format>

Zoo::Zoo() : animals(nullptr), count(0) {}
Zoo::~Zoo() {
    for (int i = 0; i < count; ++i) {
        delete animals[i];
    }
    delete[] animals;
}
void Zoo::addAnimal(Animal* animal) {
    if (animal == nullptr) {
        throw ZooException("Cannot add animal: Pointer is null!");
    }
    Animal** newAnimals = new Animal * [count + 1];
    for (int i = 0; i < count; ++i) {
        newAnimals[i] = animals[i];
    }
    newAnimals[count] = animal;
    delete[] animals;
    animals = newAnimals;
    count++;
}
void Zoo::makeRandomSick() {
    if (count == 0) {
        throw ZooException("Cannot make animal sick: Zoo is empty!");
    }
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
void Zoo::saveToTextFile(const string& filename) const {
    ofstream fout(filename);
    if (!fout.is_open()) {
        throw ZooException("Failed to open text file for writing!");
    }
    fout << count << endl;
    for (int i = 0; i < count; ++i) {
        fout << animals[i]->getSort() << endl;
        fout << animals[i]->getName() << endl;
        fout << animals[i]->getAge() << endl;
        fout << animals[i]->getDailyFood() << endl;
        fout << animals[i]->getIsHealthy() << endl;
        animals[i]->writeSpecificData(fout);
    }
    fout.close();
    cout << "\nZoo successfully saved to " << filename << endl;
}
void Zoo::loadFromTextFile(const string& filename) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        throw ZooException("Failed to open text file for reading!");
    }
    for (int i = 0; i < count; ++i) {
        delete animals[i];
    }
    delete[] animals;
    animals = nullptr;
    count = 0;
    int totalCount = 0;
    fin >> totalCount;
    if (totalCount <= 0) {
        throw ZooException("Invalid animal count in file!");
    }
    while (totalCount-- > 0) {
        string sort, name;
        int age;
        double food;
        bool isHealthy;
        fin >> sort >> name >> age >> food >> isHealthy;
        Animal* animal = nullptr;
        if (sort == "Tiger") animal = new Tiger(name, age, 0);
        else if (sort == "Crocodile") animal = new Crocodile(name, age, 0.0);
        else if (sort == "Kangaroo")  animal = new Kangaroo(name, age, 0.0);
        if (animal) {
            animal->setDailyFood(food);
            animal->setHealthStatus(isHealthy);
            animal->readSpecificData(fin);
            addAnimal(animal);
        }
    }
    cout << "Zoo successfully loaded from " << filename << endl;
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