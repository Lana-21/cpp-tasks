#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <format>
using namespace std;

class Animal {
protected:
    string name;
    string sort;
    double dailyFood;
    string foodType;
    int age;
    bool isHealthy;
public:
    Animal(string name, string sort, double food, string foodType, int age)
        : name(name), sort(sort), dailyFood(food), foodType(foodType), age(age), isHealthy(true) {
    }
    virtual ~Animal() {}
    virtual void makeSound() const = 0;
    string getName() const { return name; }
    string getSort() const { return sort; }
    double getDailyFood() const { return dailyFood; }
    string getFoodType() const { return foodType; }
    int getAge() const { return age; }
    bool getIsHealthy() const { return isHealthy; }
    void setDailyFood(double food) {
        if (food > 0) dailyFood = food;
    }
    void setAge(int newAge) {
        if (newAge > age) age = newAge;
    }
    void setHealthStatus(bool status) { isHealthy = status; }
    virtual string getInfo() const {
        string status = isHealthy ? "Healthy" : "Needs Doctor";
        return format("{} ({}, {} y.o.) - Status: {}", name, sort, age, status);
    }
};
class Tiger : public Animal {
public:
    Tiger(string name, int age, int stripes = 100)
        : Animal(name, "Tiger", 9.0, "Meat", age), stripeCount(stripes) {
    }
    int getStripeCount() const { return stripeCount; }
    void makeSound() const {
        cout << "Rooaar!";
    }
    string getInfo() const {
        return Animal::getInfo() + format(" Stripes: {}", stripeCount);
    }
private:
    int stripeCount;
};
class Crocodile : public Animal {
public:
    Crocodile(string name, int age, double length = 4.0)
        : Animal(name, "Crocodile", 4.0, "Fish", age), bodyLength(length) {
    }
    double getBodyLength() const { return bodyLength; }
    void makeSound() const {
        cout << "Snap!";
    }
    string getInfo() const {
        return Animal::getInfo() + format(" Length: {} m", bodyLength);
    }
private:
    double bodyLength;
};
class Kangaroo : public Animal {
public:
    Kangaroo(string name, int age, double jump = 2.2)
        : Animal(name, "Kangaroo", 3.0, "Grass", age), jumpHeight(jump) {
    }
    double getJumpHeight() const { return jumpHeight; }
    void makeSound() const {
        cout << "Hop-Hop!";
    }
    string getInfo() const {
        return Animal::getInfo() + format(" Jump: {} m", jumpHeight);
    }
private:
    double jumpHeight;
};
class Zoo {
public:
    Zoo() : count(0) {}
    ~Zoo() {
        for (int i = 0; i < count; ++i) {
            delete animals[i];
        }
    }
    bool addAnimal(Animal* animal) {
        if (count < MAX_CAPACITY) {
            animals[count++] = animal;
            return true;
        }
        cout << "Zoo is full!" << endl;
        delete animal; 
        return false;
    }
    void makeRandomSick() {
        if (count == 0) return;
        int randomIndex = rand() % count;
        animals[randomIndex]->setHealthStatus(false);
        cout << format("\nAnimal {} ({}) got sick!",
            animals[randomIndex]->getName(),
            animals[randomIndex]->getSort()) << endl;
    }
    void printSortCount() const {
        int tigerCount = 0;
        int crocodileCount = 0;
        int kangarooCount = 0;

        for (int i = 0; i < count; ++i) {
            if (animals[i]->getSort() == "Tiger") {
                tigerCount++;
            }
            else if (animals[i]->getSort() == "Crocodile") {
                crocodileCount++;
            }
            else if (animals[i]->getSort() == "Kangaroo") {
                kangarooCount++;
            }
        }
        cout << "\nSORT COUNT:" << endl;
        cout << format("Tigers: {}", tigerCount) << endl;
        cout << format("Crocodiles: {}", crocodileCount) << endl;
        cout << format("Kangaroos: {}", kangarooCount) << endl;
        cout << format("Total animals: {}", count) << endl;
    }
    friend ostream& operator<<(ostream& os, const Zoo& zoo) {
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
    void printBudget() const {
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
private:
    Animal* animals[10];
    int count;
    const int MAX_CAPACITY = 10;
};
int main() {
    srand(time(0));
    Zoo myZoo;
    myZoo.addAnimal(new Tiger("Sharchan", 6, 95));
    myZoo.addAnimal(new Crocodile("Genyk", 10, 4.8));
    myZoo.addAnimal(new Kangaroo("Jack", 4, 2.9));
    myZoo.addAnimal(new Tiger("Amily", 5, 78));
    cout << myZoo;
    myZoo.makeRandomSick();
    cout << myZoo;
    myZoo.printSortCount();
    myZoo.printBudget();
    return 0;
}
