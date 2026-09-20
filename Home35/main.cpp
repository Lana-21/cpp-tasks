#include <iostream>
#include <ctime>
#include "Zoo.h"
using namespace std;

int main() {
    srand(time(0));
    Zoo myZoo(10);
    try {
        myZoo.addAnimal(new Tiger("Sharchan", 6, 95));
        myZoo.addAnimal(new Crocodile("Genyk", 10, 4.8));
        myZoo.addAnimal(new Kangaroo("Jack", 4, 2.9));
        myZoo.addAnimal(new Tiger("Amily", 5, 78));
    }
    catch (const ZooException& err) {
        cout << "ZOO ERROR: " << err.what() << endl;
    }
    try {
        cout << "\n Add a tiger with age -5:" << endl;
        myZoo.addAnimal(new Tiger("BadTiger", -5, 50));
    }
    catch (const AnimalAgeException& err) {
        cout << err.what() << endl;
    }
    try {
        cout << "\n Set a negative food amount (-10.5 kg):" << endl;
        Tiger tempTiger("TempTiger", 3);
        tempTiger.setDailyFood(-10.5);
    }
    catch (const FoodAmountException& err) {
        cout << err.what() << endl;
    }
    cout << endl;
    cout << "Initial zoo status:" << endl << endl;
    cout << myZoo;
    cout << endl;
    cout << "Simulating random illness" << endl;
    myZoo.makeRandomSick();
    cout << "\nZoo status after illness:" << endl << endl;
    cout << myZoo;
    cout << endl;
    myZoo.printSortCount();
    myZoo.printBudget();
    cout << endl;
    system("pause");
    return 0;
}
