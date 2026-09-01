
#include <iostream>
#include <cstring>
#define N 50
using namespace std;

struct MyDate {
    int day;
    int month;
    int year;
    void input() {
        cout << "Day: ";
    cin >> day;
    cout << "month: ";
    cin >> month;
    cout << "year: ";
    cin >> year;
    }
    void show() const {
        cout << day << "." << month << "." << year << endl;
    }
};
class Student {
public:
    Student() {
        cout << "Constructor(default): " << this << endl;
    }
    Student(const char*, const MyDate&, const char*, const char*, const char*, const char*, const char*);

    ~Student();
   
    inline const char* getFullName() const;
    inline MyDate getBirthDate() const;
    inline const char* getPhone() const;
    inline const char* getCity() const;
    inline const char* getCountry() const;
    inline const char* getInstitution() const;
    inline const char* getGroupNumber() const;

    inline void setFullName(const char*);
    inline void setBirthDate(MyDate);
    inline void setPhone(const char*);
    inline void setCity(const char*);
    inline void setCountry(const char*);
    inline void setInstitution(const char*);
    inline void setGroupNumber(const char*);
 
    void show() const;
    void input();

private:
    char fullName[N]{ "NoName" };
    MyDate dt{ 0,0,0 };
    char phone[N]{ "NoPhone" };
    char city[N]{ "NoCity" };
    char country[N]{ "NoCountry" };
    char* institution{ nullptr };
    char groupNumber[N]{ "NoGroup" };
};

Student::Student(const char* nm, const MyDate& dt, const char* ph, const char* ct, const char* cntr, const char* inst, const char* gr) :
    dt{ dt } {
    cout << "Constructor(parameter): " << this << endl;
    setFullName(nm);
    setPhone(ph);
    setCity(ct);
    setCountry(cntr);
    setInstitution(inst);
    setGroupNumber(gr);
}

Student::~Student() {
    if (institution != nullptr) {
        delete[] institution;
        institution = nullptr;
    }
    cout << "Delete student object: " << this << endl;
}

const char* Student::getFullName() const { 
    return fullName;
}
MyDate Student::getBirthDate() const {
    return dt; 
}
const char* Student::getPhone() const { 
    return phone; 
}
const char* Student::getCity() const {
    return city;
}
const char* Student::getCountry() const {
    return country;
}
const char* Student::getInstitution() const { 
    return (institution == nullptr) ? "NoInstitution" : institution;
}
const char* Student::getGroupNumber() const { 
    return groupNumber;
}


void Student::setFullName(const char* nm) {
    if (strlen(nm) != 0) 
        strcpy_s(this->fullName, nm);
}
void Student::setBirthDate(MyDate dt) {
    this->dt = dt;
}
void Student::setPhone(const char* ph) {
    if (strlen(ph) != 0) 
        strcpy_s(this->phone, ph);
}
void Student::setCity(const char* ct) {
    if (strlen(ct) != 0) 
        strcpy_s(this->city, ct);
}
void Student::setCountry(const char* cntr) {
    if (strlen(cntr) != 0) 
        strcpy_s(this->country, cntr);
}
void Student::setInstitution(const char* inst) {
    if (inst != nullptr && strlen(inst) != 0) {
        delete[] institution; 
        institution = new char[strlen(inst) + 1];
        strcpy_s(institution, strlen(inst) + 1, inst);
    }
}
void Student::setGroupNumber(const char* gr) {
    if (strlen(gr) != 0) 
        strcpy_s(this->groupNumber, gr);
}

void Student::input() {
    char buf[N];
    cout << "Full Name: ";
    cin.getline(fullName, N);
    cout << "Input Birth Date: ";
    dt.input();
    cin.ignore();
    cout << "Phone: "; 
    cin.getline(phone, N);
    cout << "City: "; 
    cin.getline(city, N);
    cout << "Country: "; 
    cin.getline(country, N);
    cout << "Educational Institution: ";
    cin.getline(buf, N);
    setInstitution(buf);
    cout << "Group Number: "; 
    cin.getline(groupNumber, N);
}

void Student::show() const {
    cout << "\nStudent:" << endl
        << "Full Name: " << getFullName() << endl
        << "Birth Date: ";
        dt.show();
        cout << "Phone: " << getPhone() << endl
        << "City: " << getCity() << endl
        << "Country: " << getCountry() << endl
        << "Institution: " << getInstitution() << endl
        << "Group: " << getGroupNumber() << endl;
}

int main()
{
    cout << "Entering data for Student 1" << endl;
    Student st1;
    st1.input();
    st1.show();

    cout << "\nCreating Student 2 with parameters" << endl;
    MyDate d{ 15, 5, 2000 };
    Student st2("Svitlana", d, "+38096000000", "Lviv", "Ukraine", "ITS", "ITS-11");
    st2.show();
    return 0;
}
