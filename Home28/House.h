#include "Apartment.h"

class House {
public:
    House();
    House(const char*, int);
    House(const House&);
    House& operator=(const House&);
    House(House&&);
    House& operator=(House&&);
    ~House();

    inline void setAddress(const char*);
    inline Apartment& getApartment(int);

    Apartment& operator[](int index);
    const Apartment& operator[](int index) const;
    int operator()() const;

    friend ostream& operator<<(ostream& os, const House& h) {
        os << "HOUSE ADDRESS: " << ((h.address != nullptr) ? h.address : "No Address") << endl;
        os << "Total Apartments: " << h.count << endl;
        for (int i = 0; i < h.count; i++) {
            os << h.apartments[i]; 
        }
        return os;
    }
    friend istream& operator>>(istream& is, House& h) {
        char buffer[256];
        cout << "Enter house address: ";
        is.getline(buffer, 256);
        h.setAddress(buffer);
        return is;
    }
private:
    char* address{ nullptr };
    Apartment* apartments{ nullptr };
    int count{ 0 };
};

inline House::House() {
    cout << "Constructor House(default): " << this << endl;
}
inline House::House(const char* addr, int aptCount) : count{ aptCount } {
    setAddress(addr);
    if (count > 0) {
        apartments = new Apartment[count];
        for (int i = 0; i < count; i++) {
            apartments[i] = Apartment(i + 1);
        }
    }
    cout << "Constructor House(parameter): " << this << endl;
}

inline House::House(const House& h) : count{ h.count } {
    setAddress(h.address);
    if (h.apartments != nullptr && count > 0) {
        apartments = new Apartment[count];
        for (int i = 0; i < count; i++) {
            apartments[i] = h.apartments[i];
        }
    }
    cout << "Constructor House(copy): " << this << endl;
}
inline House& House::operator=(const House& h) {
    delete[] address;
    delete[] apartments;
    address = nullptr;
    apartments = nullptr;
    count = h.count;
    setAddress(h.address);
    if (h.apartments != nullptr && count > 0) {
        apartments = new Apartment[count];
        for (int i = 0; i < count; i++) {
            apartments[i] = h.apartments[i];
        }
    }
    return *this;
}

inline House::House(House&& h) : address{ h.address }, apartments{ h.apartments }, count{ h.count } {
    h.address = nullptr;
    h.apartments = nullptr;
    h.count = 0;
    cout << "Constructor House(move): " << this << endl;
}
inline House& House::operator=(House&& h) {
    if (address != nullptr) {
        delete[] address;
    }
    if (apartments != nullptr) {
        delete[] apartments;
    }
    address = h.address;
    apartments = h.apartments;
    count = h.count;
    h.address = nullptr;
    h.apartments = nullptr;
    h.count = 0;
    return *this;
}

inline House::~House() {
    if (address != nullptr) {
        delete[] address;
    }
    if (apartments != nullptr) {
        delete[] apartments;
    }
    cout << "Delete House object: " << this << endl;
}

inline void House::setAddress(const char* addr) {
    if (addr != nullptr && strlen(addr) != 0) {
        delete[] address;
        address = new char[strlen(addr) + 1];
        strcpy_s(address, strlen(addr) + 1, addr);
    }
}
inline Apartment& House::getApartment(int index) {
    return apartments[index];
}

inline Apartment& House::operator[](int index) {
    return apartments[index];
}
inline const Apartment& House::operator[](int index) const {
    return apartments[index];
}
inline int House::operator()() const {
    int totalPeople = 0;
    for (int i = 0; i < count; i++) {
        totalPeople += apartments[i].getCount();
    }
    return totalPeople;
}

