#include "Human.h"

class Apartment {
public:
    Apartment();
    Apartment(int);
    Apartment(const Apartment&);
    Apartment& operator=(const Apartment&);
    Apartment(Apartment&&);
    Apartment& operator=(Apartment&&);
    ~Apartment();

    inline void addPerson(const Human&);
    inline int getNumber() const;
    inline int getCount() const;

    Human& operator[](int index);
    const Human& operator[](int index) const;

    friend ostream& operator<<(ostream& os, const Apartment& apt) {
        os << "\nApartment N. " << apt.number << endl;
        os << "persons count: " << apt.count << endl;
        for (int i = 0; i < apt.count; i++) {
            os << i + 1 << ". " << apt.persons[i] << endl;
        }
        return os;
    }
    friend istream& operator>>(istream& is, Apartment& apt) {
            cout << "Enter apartment number: ";
            is >> apt.number;
            return is;
        }
private:
    Human* persons{ nullptr };
    int count{ 0 };
    int number{ 0 };
};

inline Apartment::Apartment() {
    cout << "Constructor Apartment(default): " << this << endl;
}
inline Apartment::Apartment(int number) : number{ number } {
    cout << "Constructor Apartment(parameter): " << this << endl;
}

inline Apartment::Apartment(const Apartment& apt) : number{ apt.number }, count{ apt.count } {
    if (apt.persons != nullptr && count > 0) {
        persons = new Human[count];
        for (int i = 0; i < count; i++) {
            persons[i] = apt.persons[i];
        }
    }
    cout << "Constructor Apartment(copy): " << this << endl;
}
inline Apartment& Apartment::operator=(const Apartment& apt) {
    delete[] persons;
    persons = nullptr;
    number = apt.number;
    count = apt.count;
    if (apt.persons != nullptr && count > 0) {
        persons = new Human[count];
        for (int i = 0; i < count; i++) {
            persons[i] = apt.persons[i];
        }
    }
    return *this;
}

inline Apartment::Apartment(Apartment&& apt) : persons{ apt.persons }, count{ apt.count }, number{ apt.number } {
    apt.persons = nullptr;
    apt.count = 0;
    apt.number = 0;
    cout << "Constructor Apartment(move): " << this << endl;
}
inline Apartment& Apartment::operator=(Apartment&& apt) {
    delete[] persons;
    persons = apt.persons;
    count = apt.count;
    number = apt.number;
    apt.persons = nullptr;
    apt.count = 0;
    apt.number = 0;
    return *this;
}

inline Apartment::~Apartment() {
    if (persons != nullptr) {
        delete[] persons;
    }
    cout << "Delete Apartment object: " << this << endl;
}

inline void Apartment::addPerson(const Human& h) {
    Human* temp = new Human[count + 1];
    for (int i = 0; i < count; i++) {
        temp[i] = persons[i];
    }
    temp[count] = h;
    delete[] persons;
    persons = temp;
    count++;
}

inline int Apartment::getNumber() const { return number; }
inline int Apartment::getCount() const { return count; }

inline Human& Apartment::operator[](int index) {
    return persons[index];
}

inline const Human& Apartment::operator[](int index) const {
    return persons[index];
}
