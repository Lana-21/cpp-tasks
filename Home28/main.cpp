#include "House.h"

int main() {
    cout << "CREATING HUMANS" << endl;
    Human h1("Taras Shevchenko", 47);
    Human h2("Ivan Franko", 59);
    cout << "\nCREATING HOUSE & APARTMENTS" << endl;
    House myHouse("Khreshchatyk St. 1", 2);
    myHouse[0].addPerson(h1);
    myHouse[1].addPerson(h2);
    cout << "\n OPERATOR (<<)" << endl;
    cout << myHouse;
    cout << "\nOperator []" << endl;
    cout << "Initial resident of apartment 1: " << myHouse[0][0] << endl;
    Human h3("Lesya Ukrainka", 42);
    myHouse[0][0] = h3;
    cout << "Updated resident of apartment 1: " << myHouse[0][0] << endl;
    cout << "\nOperator ()" << endl;
    cout << "Total number of people in the house: " << myHouse() << endl;
    return 0;
}
