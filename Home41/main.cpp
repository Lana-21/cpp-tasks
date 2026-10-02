#include "Manager.h"
#include <iostream>
using namespace std;

int main() {
    Manager manager;
    string filename = "countries.txt";
    int choice;
    do {
        cout << "\nMENU\n"
            << "1. Load data from file\n"
            << "2. Save data to file\n"
            << "3. Search cities of a specific country\n"
            << "4. Replace a city name\n"
            << "5. Add a city or country\n"
            << "6. Delete a city or country\n"
            << "7. Count total number of cities\n"
            << "8. Display all countries and cities\n"
            << "0. Exit\n"
            << "Select choice: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid choice. Please try again.\n";
            continue;
        }
        cin.ignore();
        switch (choice) {
        case 1:
            manager.loadFromFile(filename); break;
        case 2:
            manager.saveToFile(filename); break;
        case 3:
            manager.searchCities(); break;
        case 4:
            manager.replaceCity(); break;
        case 5:
            manager.addCountry(); break;
        case 6:
            manager.deleteCountry(); break;
        case 7:
            manager.countCities(); break;
        case 8:
            cout << "\n" << manager; break;
        case 0:
            cout << "Exiting program.\n"; break;
        default:
            cout << "Invalid choice. Please try again.\n"; break;
        }
    } while (choice != 0);
    return 0;
}
