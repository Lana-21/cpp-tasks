#pragma once
#include <string>
#include <iostream>
#include <utility>
#include <sstream>
#include <cctype>
using namespace std;

inline string formatDouble(double val) {
    ostringstream oss;
    oss << val;
    return oss.str();
}
inline string toLower(string str) {
    for (char& c : str) {
        c = tolower(c);
    }
    return str;
}
struct Expense {
    double amount;
    string category;
    int day;
    Expense(double amount = 0.0, string category = "", int day = 1)
        : amount(amount), category(move(category)), day(day) {
    }
    double getAmount() const { return amount; }
    const string& getCategory() const { return category; }
    int getDay() const { return day; }
    bool isValid() const {
        return amount > 0 && !category.empty() && day >= 1 && day <= 31;
    }
    bool isInPeriod(int currentDay, int daysPeriod) const {
        int startDay = currentDay - daysPeriod + 1;
        return day >= startDay && day <= currentDay;
    }
    string toString() const {
        return category + " - " + formatDouble(amount) + " USD (Day " + to_string(day) + ")";
    }
    static bool compareByAmountDesc(const Expense& a, const Expense& b) {
        return a.amount > b.amount;
    }
    friend ostream& operator<<(ostream& os, const Expense& exp) {
        return os << exp.amount << "\n" << exp.category << "\n" << exp.day;
    }
    friend istream& operator>>(istream& is, Expense& exp) {
        if (is >> exp.amount >> ws) {
            if (getline(is, exp.category)) {
                is >> exp.day;
            }
        }
        return is;
    }
};
struct CategoryTotal {
    string name;
    double amount;
    CategoryTotal(string name = "", double amount = 0.0)
        : name(move(name)), amount(amount) {
    }
    void addAmount(double val) { amount += val; }
    string toString() const {
        return name + " - " + formatDouble(amount) + " USD";
    }
    static bool compareByTotalDesc(const CategoryTotal& a, const CategoryTotal& b) {
        return a.amount > b.amount;
    }
    friend ostream& operator<<(ostream& os, const CategoryTotal& cat) {
        return os << cat.toString();
    }
};
