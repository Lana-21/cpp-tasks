#include <iostream>
#include <string>
using namespace std;

class Employee
{
public:
    Employee(const string& firstName, const string& lastName, const string& birthDate, int experience, double baseSalary)
        : firstName(firstName), lastName(lastName), birthDate(birthDate), experience(experience), baseSalary(baseSalary)
    {
    }
    virtual ~Employee() {}
    const string& getFirstName() const { return firstName; }
    const string& getLastName() const { return lastName; }
    const string& getBirthDate() const { return birthDate; }
    int getExperience() const { return experience; }
    double getBaseSalary() const { return baseSalary; }

    virtual double calculateSalary() const = 0;
    virtual string whatIDo() const = 0;
    virtual void showInfo() const
    {
        cout << "Name: " << firstName << " " << lastName
            << " BirthDate: " << birthDate
            << " Experience: " << experience << " yrs" << endl;
    }
private:
    string firstName;
    string lastName;
    string birthDate;
    int experience;
    double baseSalary;
};
class Manager : public Employee
{
public:
    Manager(const string& firstName, const string& lastName, const string& birthDate, int experience, double baseSalary, double bonus)
        : Employee(firstName, lastName, birthDate, experience, baseSalary), bonus(bonus)
    {
    }
    double calculateSalary() const
    {
        return getBaseSalary() + bonus;
    }
    string whatIDo() const
    {
        return "Organizes team workflow.";
    }
private:
    double bonus;

};
class Developer : public Employee
{
public:
    Developer(const string& firstName, const string& lastName, const string& birthDate, int experience, double baseSalary, int linesOfCode, double ratePerLine)
        : Employee(firstName, lastName, birthDate, experience, baseSalary), linesOfCode(linesOfCode), ratePerLine(ratePerLine)
    {
    }
    double calculateSalary() const
    {
        return getBaseSalary() + (linesOfCode * ratePerLine);
    }
    string whatIDo() const
    {
        return "Write code";
    }
private:
    int linesOfCode;
    double ratePerLine;
};
int main()
{
    Employee* employees[] = {
        new Manager("Vika", "Makosh", "19.01.2000", 7, 5070.0, 740.0),
        new Developer("Ivan", "Ivanov", "20.02.2005", 4, 8500.0, 1250, 1.01),
        new Developer("Maria", "Koval", "09.11.2010", 3, 3020.0, 550, 1.30),
        new Manager("Olena", "Kalush", "11.08.1999", 6, 5820.0, 600.0)
    };
    double totalSalary = 0.0;
    for (auto item : employees)
    {
        item->showInfo();
        cout << "Responsibilities: " << item->whatIDo() << endl;
        cout << "Salary: $" << item->calculateSalary() << endl;
        cout << string(15, '-') << endl;
        totalSalary += item->calculateSalary();
    }
    cout << "\nTotal Salary: $" << totalSalary << endl;
    for (auto item : employees)
    {
        delete item;
    }
    return 0;
}
