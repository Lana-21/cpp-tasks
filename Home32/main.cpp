#include <iostream>
#include <string>
using namespace std;

//exercise2
class Animal {
public:
    Animal() : name(""), age(0) {}
    Animal(string n, int a) : name(n), age(a) {}
    ~Animal() {}
    string getName() const { return name; }
    int getAge() const { return age; }
    void setName(string n) { name = n; }
    void setAge(int a) { age = a; }
    friend ostream& operator<<(ostream& os, const Animal& a) {
        return os << "Animal: " << a.name << "Life span: " << a.age << " years";
    }
private:
    string name;
    int age;
};
class Predator : public Animal {
public:
    Predator() : Animal(), location(""), population(0), coefficient(1.0) {}
    Predator(string n, int a, string loc, int pop, double coef)
        : Animal(n, a), location(loc), population(pop), coefficient(coef) {
    }
    ~Predator() {}
    string getLocation() const { return location; }
    int getPopulation() const { return population; }
    double getCoefficient() const { return coefficient; }
    void setLocation(string loc) { location = loc; }
    void setPopulation(int pop) { population = pop; }
    void setCoefficient(double coef) { coefficient = coef; }
    string getSuccessStatus() const {
        if (coefficient > 1.0 && population > 500) {
            return "Grow";
        }
        else if (coefficient >= 0.88) {
            return "Stable";
        }
        else {
            return "Risk";
        }
    }
    friend ostream& operator<<(ostream& os, const Predator& p) {
        os << static_cast<const Animal&>(p)
            << " Location: " << p.location
            << " Population: " << p.population
            << " Growth Coef: " << p.coefficient
            << " Status: " << p.getSuccessStatus();
        return os;
    }
private:
    string location;
    int population;
    double coefficient;
};
int main() {
    const int SIZE = 4;
    Predator animals[SIZE] = {
        Predator("Wolf", 11, "Carpathian Mountains", 1110, 1.2),
        Predator("Tiger", 16, "Taiga", 550, 0.95),
        Predator("Leopard", 11, "Himalayas", 300, 0.8),
        Predator("Lion", 13, "Savannah", 2010, 1.15)
    };
    for (int i = 0; i < SIZE; i++) {
        cout << animals[i] << endl;
    }
    int maxIdx = 0;
    int minIdx = 0;
    for (int i = 0; i < SIZE; i++) {
        maxIdx = (animals[i].getPopulation() > animals[maxIdx].getPopulation()) ? i : maxIdx;
        minIdx = (animals[i].getPopulation() < animals[minIdx].getPopulation()) ? i : minIdx;
    }
    cout << endl;
    cout << "Animal with the highest population: " << endl;
    cout << animals[maxIdx] << endl;
    cout << "\nAnimal needing protection: " << endl;
    cout << animals[minIdx] << endl;
    return 0;
}


//exercise1
class Triad {
public:
    Triad() : first(0), second(0), third(0) {}
    Triad(int f, int s, int t) : first(f), second(s), third(t) {}
    ~Triad() {}
    int getFirst() const { return first; }
    int getSecond() const { return second; }
    int getThird() const { return third; }
    void setFirst(int f) { first = f; }
    void setSecond(int s) { second = s; }
    void setThird(int t) { third = t; }
    void increment() {
        first++;
        second++;
        third++;
    }
    friend ostream& operator<<(ostream& os, const Triad& t) {
        return os << t.first << ", " << t.second << ", " << t.third << endl;
    }
private:
    int first, second, third;
};
class Date : public Triad {
public:
    Date() : Triad(2026, 1, 1) {}
    Date(int y, int m, int d) : Triad(y, m, d) {}
    ~Date() {}
    int daysInMonth() const {
        int y = getFirst();
        int m = getSecond();
        switch (m) {
        case 2:
            return 28;
        case 4: case 6: case 9: case 11:
            return 30;
        default:
            return 31;
        }
    }
    void increment() {
        setThird(getThird() + 1);
        if (getThird() > daysInMonth()) {
            setThird(1);
            setSecond(getSecond() + 1);
            if (getSecond() > 12) {
                setSecond(1);
                setFirst(getFirst() + 1);
            }
        }
    }
    void addDays(int n) {
        for (int i = 0; i < n; i++) {
            increment();
        }
    }
    friend ostream& operator<<(ostream& os, const Date& d) {
        return os << d.getThird() << "." << d.getSecond() << "." << d.getFirst();
    }
};
int main() {
    cout << "Testing Triad" << endl;
    Triad t(10, 20, 30);
    cout << "Triad before: " << t << endl;
    t.increment();
    cout << "Triad after:  " << t << endl << endl;
    cout << "Testing Date" << endl;
    Date d(2025, 12, 31);
    cout << "Start date: " << d << endl;
    d.increment();
    cout << "+1 day: " << d << endl;
    d.addDays(59);
    cout << "+59 days: " << d << endl;
    return 0;
}
