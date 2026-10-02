#include "Manager.h"
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

void Manager::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Failed to open file\n";
        return;
    }
    data.clear();
    string country, city;
    while (getline(file, country) && getline(file, city)) {
        if (!country.empty() && !city.empty()) {
            data[country].push_back(city);
        }
    }
    file.close();
    cout << "Successfully loaded from '" << filename << "\n";
}
void Manager::saveToFile(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Failed to open file\n";
        return;
    }
    for (const auto& [country, cities] : data) {
        for (const auto& city : cities) {
            file << country << "\n" << city << "\n";
        }
    }
    file.close();
    cout << "Successfully saved to " << filename << "\n";
}

void Manager::searchCities() const {
    string country;
    cout << "Enter country name: ";
    getline(cin, country);
    if (data.contains(country) && !data.at(country).empty()) {
        cout << "Cities in " << country << ":\n";
        for (const auto& city : data.at(country)) {
            cout << " - " << city << "\n";
        }
    }
    else {
        cout << "Country not found\n";
    }
}
void Manager::replaceCity() {
    string country, oldCity, newCity;
    cout << "Enter country name: ";
    getline(cin, country);
    if (!data.contains(country)) { 
        cout << "Country not found\n";
        return;
    }
    cout << "Enter city name to replace: ";
    getline(cin, oldCity);
    bool found = false;
    for (auto& city : data.at(country)) {
        if (city == oldCity) {
            cout << "Enter new city name: ";
            getline(cin, newCity);
            city = newCity;
            found = true;
            cout << "City updated successfully!\n";
            break;
        }
    }
    if (!found) {
        cout << "City not found\n";
    }
}
void Manager::addCountry() {
    string country, city;
    cout << "Enter country name: ";
    getline(cin, country);
    cout << "Enter city name: ";
    getline(cin, city);
    if (city.empty()) {
        data[country]; 
        cout << "Country '" << country << "' added.\n";
    }
    else {
        data[country].push_back(city);
        cout << "City '" << city << "' added to country '" << country << "'.\n";
    }
}
void Manager::deleteCountry() {
    string country;
    cout << "Enter country name: ";
    getline(cin, country);
    if (!data.contains(country)) { 
        cout << "Country not found.\n";
        return;
    }
    cout << "1. Delete a city\n"
        << "2. Delete a country\n"
        << "Select option: ";
    int choice;
    if (!(cin >> choice)) {
        cin.clear();
        cout << "Invalid selection.\n";
        return;
    }
    switch (choice) {
    case 1: {
        string city;
        cout << "Enter city name to delete: ";
        getline(cin, city);
        auto& cities = data.at(country);
        bool found = false;
        for (size_t i = 0; i < cities.size(); ++i) {
            if (cities[i] == city) {
                cities.erase(cities.begin() + i);
                found = true;
                cout << "City '" << city << "' deleted.\n";
                break;
            }
        }
        if (!found) cout << "City not found.\n";
        break;
    }
    case 2:
        data.erase(country);
        cout << "Country '" << country << "' deleted.\n";
        break;
    default:
        cout << "Invalid option.\n";
        break;
    }
}
void Manager::countCities() const {
    size_t totalCities = 0;
    for (const auto& [country, cities] : data) {
        totalCities += cities.size();
    }
    cout << "Total number of cities: " << totalCities << "\n";
}
ostream& operator<<(ostream& os, const Manager& manager) {
    if (manager.data.empty()) {
        os << "Database is empty.\n";
        return os;
    }
    os << "\nLIST OF COUNTRIES AND CITIES\n";
    for (const auto& [country, cities] : manager.data) {
        os << "Country: " << country << "cities count: " << cities.size() << "\n";
        for (const auto& city : cities) {
            os << " " << city << "\n";
        }
    }
    return os;
}
