#include <iostream>
#include <ctime>
#include "Zoo.h"
using namespace std;

int main() {
    srand(time(0));
    Zoo myZoo;
    try {
        myZoo.loadFromTextFile("zoo.txt");
    }
    catch (const ZooException& err) {
        cout << "File not found" << endl;
    }
    cout << "\nAdding new animals to the zoo" << endl;
    try {
        myZoo.addAnimal(new Tiger("Rajah", 7, 88));
        myZoo.addAnimal(new Crocodile("Gena", 12, 5.1));
        myZoo.addAnimal(new Kangaroo("Joey", 2, 1.8));
    }
    catch (const ZooException& err) {
        cout << "Error adding animal: " << err.what() << endl;
    }
    cout << "\nCURRENT ZOO" << endl;
    cout << myZoo;
    cout << "\nSimulating random illness" << endl;
    try {
        myZoo.makeRandomSick();
    }
    catch (const ZooException& err) {
        cout << err.what() << endl;
    }
    cout << "\nZoo status after illness:" << endl << endl;
    cout << myZoo;
    cout << endl;
    myZoo.printSortCount();
    myZoo.printBudget();
    cout << endl;
    try {
        myZoo.saveToTextFile("zoo.txt");
        cout << "Data successfully saved to file!" << endl;
    }
    catch (const ZooException& err) {
        cout << "Error saving to file: " << err.what() << endl;
    }
    system("pause");
    return 0;
}
