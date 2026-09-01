#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#define N 100
using namespace std;

class Reservoir {
public:
    Reservoir() {
        cout << "Constructor Reservoir(default): " << this << endl;
    }
    Reservoir(const char*, const char*, double, double, double);
    Reservoir(const Reservoir&);
    Reservoir& operator=(const Reservoir&);

    explicit Reservoir(const char*);
    ~Reservoir();

    inline const char* getName() const;
    inline const char* getType() const;
    inline double getWidth() const;
    inline double getLength() const;
    inline double getMaxDepth() const;

    inline void setName(const char*);
    inline void setType(const char*);
    inline void setWidth(double w);
    inline void setLength(double l);
    inline void setMaxDepth(double d);

    inline double getVolume() const;
    inline double getArea() const;
    inline bool isSameType(const Reservoir& other) const;
    inline bool isAreaGreater(const Reservoir& other) const;

    inline void saveText(ofstream& file) const;

    friend ostream& operator<<(ostream& s, const Reservoir& r) {
        s << "\nReservoir: \n"
            << "Name: " << r.getName() << endl
            << "Type: " << r.getType() << endl
            << "Width: " << r.getWidth() << endl
            << "Length: " << r.getLength() << endl
            << "Max Depth: " << r.getMaxDepth() << endl
            << "Area: " << r.getArea() << endl
            << "Volume: " << r.getVolume() << endl;
        return s;
    }
    friend istream& operator>>(istream& s, Reservoir& r) {
        char bufName[N];
        char bufType[N];
        double w, l, d;
        cout << "Input Name: ";
        s.getline(bufName, N);
        r.setName(bufName);
        cout << "Input Type: ";
        s.getline(bufType, N);
        r.setType(bufType);
        cout << "Input Width: ";
        s >> w;
        r.setWidth(w);
        cout << "Input Length: ";
        s >> l;
        r.setLength(l);
        cout << "Input Max Depth: ";
        s >> d;
        r.setMaxDepth(d);
        s.ignore();
        return s;
    }
private:
    char* name{ nullptr };
    char* type{ nullptr };
    double width{ 0.0 };
    double length{ 0.0 };
    double maxDepth{ 0.0 };
};
inline Reservoir::Reservoir(const char* resName) : Reservoir(resName, "Unknown", 0.0, 0.0, 0.0) {
    cout << "Constructor explicit: " << this << endl;
}
inline Reservoir::Reservoir(const char* n, const char* t, double w, double l, double d) :
    width{ w < 0 ? 0 : w }, length{ l < 0 ? 0 : l }, maxDepth{ d < 0 ? 0 : d } {
    setName(n);
    setType(t);
    cout << "Constructor Reservoir(parameter): " << this << endl;
}

inline Reservoir::Reservoir(const Reservoir& res) :
    width{ res.width }, length{ res.length }, maxDepth{ res.maxDepth } {
    if (res.name != nullptr) {
        name = new char[strlen(res.name) + 1];
        strcpy_s(name, strlen(res.name) + 1, res.name);
    }
    if (res.type != nullptr) {
        type = new char[strlen(res.type) + 1];
        strcpy_s(type, strlen(res.type) + 1, res.type);
    }
    cout << "Constructor Reservoir(copy): " << this << endl;
}
inline Reservoir& Reservoir::operator=(const Reservoir& res) {
    width = res.width;
    length = res.length;
    maxDepth = res.maxDepth;
    delete[] name;
    name = nullptr;
    if (res.name != nullptr) {
        name = new char[strlen(res.name) + 1];
        strcpy_s(name, strlen(res.name) + 1, res.name);
    }
    delete[] type;
    type = nullptr;
    if (res.type != nullptr) {
        type = new char[strlen(res.type) + 1];
        strcpy_s(type, strlen(res.type) + 1, res.type);
    }
    return *this;
}
inline Reservoir::~Reservoir() {
    delete[] name;
    delete[] type;
    cout << "Delete reservoir object: " << this << endl;
}

inline const char* Reservoir::getName() const { return (name != nullptr) ? name : "No Name"; }
inline const char* Reservoir::getType() const { return (type != nullptr) ? type : "No Type"; }
inline double Reservoir::getWidth() const { return width; }
inline double Reservoir::getLength() const { return length; }
inline double Reservoir::getMaxDepth() const { return maxDepth; }

inline void Reservoir::setName(const char* n) {
    if (n != nullptr && strlen(n) != 0) {
        delete[] name;
        name = new char[strlen(n) + 1];
        strcpy_s(name, strlen(n) + 1, n);
    }
}
inline void Reservoir::setType(const char* t) {
    if (t != nullptr && strlen(t) != 0) {
        delete[] type;
        type = new char[strlen(t) + 1];
        strcpy_s(type, strlen(t) + 1, t);
    }
}
inline void Reservoir::setWidth(double w) { width = (w < 0) ? 0 : w; }
inline void Reservoir::setLength(double l) { length = (l < 0) ? 0 : l; }
inline void Reservoir::setMaxDepth(double d) { maxDepth = (d < 0) ? 0 : d; }

inline double Reservoir::getVolume() const {
    return width * length * maxDepth;
}
inline double Reservoir::getArea() const {
    return width * length;
}
inline bool Reservoir::isSameType(const Reservoir& other) const {
    return strcmp(this->getType(), other.getType()) == 0;
}
inline bool Reservoir::isAreaGreater(const Reservoir& other) const {
    if (isSameType(other)) {
        return this->getArea() > other.getArea();
    }
    return false;
}

inline void Reservoir::saveText(ofstream& file) const {
    if (file.is_open()) {
        file << getName() << " " << getType() << " " << width << " " << length << " " << maxDepth << "\n";
    }
}