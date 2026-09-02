#pragma once
#include <iostream>
using namespace std;

//завдання1
class Drib {
public:
    Drib(int c = 0, int z = 1);

    Drib operator+(const Drib& drb) const;
    Drib operator-(const Drib& drb) const;
    Drib operator*(const Drib& drb) const;
    Drib operator/(const Drib& drb) const;

    bool operator==(const Drib& drb) const;
    bool operator!=(const Drib& drb) const;
    bool operator<(const Drib& drb) const;
    bool operator>(const Drib& drb) const;

    friend ostream& operator<<(ostream& os, const Drib& d) {
        int c = d.ch / d.zn;
        int rem = abs(d.ch % d.zn);
        if (c != 0) os << c;
        if (rem != 0 || c == 0) os << rem << "/" << d.zn;
        return os;
    }
    friend istream& operator>>(istream& is, Drib& d) {
        cout << "\nInput ch: ";
        is >> d.ch;
        cout << "Input zn: ";
        is >> d.zn;
        d.skor();
        return is;
    }
private:
    int ch;
    int zn;
    int ncd(int, int) const;
    void skor();
};

int Drib::ncd(int a, int b) const {
    return (b == 0 ? a : ncd(b, a % b));
}
void Drib::skor() {
    int d = ncd(ch, zn);
    ch /= d;
    zn /= d;
}

Drib::Drib(int c, int z) : ch{ c }, zn{ z == 0 ? 1 : z } {
    skor();
}
inline Drib Drib::operator+(const Drib& drb) const {
    return Drib(ch * drb.zn + drb.ch * zn, zn * drb.zn);
}
inline Drib Drib::operator-(const Drib& drb) const {
    return Drib(ch * drb.zn - drb.ch * zn, zn * drb.zn);
}
inline Drib Drib::operator*(const Drib& drb) const {
    return Drib(ch * drb.ch, zn * drb.zn);
}
inline Drib Drib::operator/(const Drib& drb) const {
    return Drib(ch * drb.zn, zn * drb.ch);
}

inline bool Drib::operator==(const Drib& drb) const {
    return ch * drb.zn == drb.ch * zn;
}
inline bool Drib::operator!=(const Drib& drb) const {
    return ch * drb.zn != drb.ch * zn;
} 
inline bool Drib::operator<(const Drib& drb) const {
    return ch * drb.zn < drb.ch * zn;
}
inline bool Drib::operator>(const Drib& drb) const {
    return ch * drb.zn > drb.ch * zn;
}



//завдання2
class Flat {
public:
    Flat(double, double, int);

    double getArea() const;
    double getPriceM() const;
    int getRooms() const;
    void setArea(double);
    void setPriceM(double);
    void setRooms(int);

    double getTotalPrice() const;

    bool operator==(const Flat&) const;
    bool operator!=(const Flat&) const;

    Flat& operator++();
    Flat& operator--();

    bool operator>(const Flat&) const;
    bool operator<(const Flat&) const;
    friend ostream& operator<<(ostream& s, const Flat& f) {
        s << "Flat(Area: " << f.area << " sq.m"
            << ", Price/sq.m: $" << f.priceM
            << ", Total Price: $" << f.getTotalPrice()
            << ", Rooms: " << f.rooms << ")";
        return s;
    }
private:
    double area{ 0.0 };         
    double priceM{ 0.0 };  
    int rooms{ 1 };            
};

inline Flat::Flat(double a, double p, int r) {
    setArea(a);
    setPriceM(p);
    setRooms(r);
}

inline double Flat::getArea() const { return area; }
inline double Flat::getPriceM() const { return priceM; }
inline int Flat::getRooms() const { return rooms; }
inline void Flat::setArea(double a) { area = (a < 0) ? 0 : a; }
inline void Flat::setPriceM(double p) { priceM = (p < 0) ? 0 : p; }
inline void Flat::setRooms(int r) { rooms = (r < 1) ? 1 : r; }

inline double Flat::getTotalPrice() const { return area * priceM; }

inline bool Flat::operator==(const Flat& fl) const {
    return this->area == fl.area;
}
inline bool Flat::operator!=(const Flat& fl) const {
    return this->area != fl.area;
}

inline Flat& Flat::operator++() {
    this->rooms++;
    return *this;
}
inline Flat& Flat::operator--() {
    if (this->rooms > 1) {
        this->rooms--;
    }
    return *this;
}

inline bool Flat::operator>(const Flat& fl) const {
    return this->getTotalPrice() > fl.getTotalPrice();
}
inline bool Flat::operator<(const Flat& fl) const {
    return this->getTotalPrice() < fl.getTotalPrice();
}