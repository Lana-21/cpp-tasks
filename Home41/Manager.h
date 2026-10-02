#pragma once
#include <string>
#include <map>
#include <vector>
using namespace std;

using Map = map<string, vector<string>>;
class Manager {
public:
    void loadFromFile(const string& filename);
    void saveToFile(const string& filename) const;
    void searchCities() const;
    void replaceCity();
    void addCountry();
    void deleteCountry();
    void countCities() const;
    friend ostream& operator<<(ostream& os, const Manager& manager);
private:
    Map data;
};
