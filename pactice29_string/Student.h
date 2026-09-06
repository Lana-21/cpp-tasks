#pragma once
#include <iostream>
#include <string>
using namespace std;

class Student {
public:
    Student() {
        cout << "Constructor Student(default): " << this << endl;
    }
    Student(const string&, int, const string&, const string&, const string&, double);
    explicit Student(const string& studentName);
    ~Student() {
        cout << "Delete student object: " << this << endl;
    }
    string getFullName() const;
    int getAge() const;
    string getPhone() const;
    string getCity() const;
    string getCountry() const;
    double getRating() const;
    void setFullName(const string&);
    void setAge(int);
    void setPhone(const string&);
    void setCity(const string&);
    void setCountry(const string&);
    void setRating(double);
    friend ostream& operator<<(ostream& s, const Student& st) {
        s << "\nStudent: \n"
            << "Full Name: " << st.getFullName() << endl
            << "Age: " << st.getAge() << endl
            << "Phone: " << st.getPhone() << endl
            << "City: " << st.getCity() << endl
            << "Country: " << st.getCountry() << endl
            << "Rating: " << st.getRating() << endl;
        return s;
    }
    friend istream& operator>>(istream& s, Student& st) {
        cout << "Input Full Name: ";
        getline(s, st.fullName);
        cout << "Input Age: ";
        s >> st.age;
        s.ignore();
        cout << "Input Phone: ";
        getline(s, st.phone);
        cout << "Input City: ";
        getline(s, st.city);
        cout << "Input Country: ";
        getline(s, st.country);
        cout << "Input Rating: ";
        s >> st.rating;
        s.ignore();
        return s;
    }
private:
    string fullName{ "NoName" };
    int age{ 0 };
    string phone{ "NoPhone" };
    string city{ "NoCity" };
    string country{ "NoCountry" };
    double rating{ 0.0 };
};
inline string Student::getFullName() const { return fullName; }
inline int Student::getAge() const { return age; }
inline string Student::getPhone() const { return phone; }
inline string Student::getCity() const { return city; }
inline string Student::getCountry() const { return country; }
inline double Student::getRating() const { return rating; }
inline void Student::setFullName(const string& nm) { if (!nm.empty()) fullName = nm; }
inline void Student::setAge(int a) { age = a; }
inline void Student::setPhone(const string& ph) { if (!ph.empty()) phone = ph; }
inline void Student::setCity(const string& ct) { if (!ct.empty()) city = ct; }
inline void Student::setCountry(const string& cntr) { if (!cntr.empty()) country = cntr; }
inline void Student::setRating(double r) { rating = r; }

inline Student::Student(const string& studentName)
    : Student(studentName, 0, "None", "None", "None", 0.0) {
    cout << "Constructor explicit : " << this << endl;
}
inline Student::Student(const string& nm, int a, const string& ph, const string& ct, const string& cntr, double r) :
    fullName{ nm }, age{ a }, phone{ ph }, city{ ct }, country{ cntr }, rating{ r } {
    cout << "Constructor Student(parameter): " << this << endl;
}