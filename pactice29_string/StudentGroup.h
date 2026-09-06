#pragma once
#include "Student.h"

class StudentGroup {
public:
    StudentGroup() {
        cout << "Constructor Group(default): " << this << endl;
    }
    StudentGroup(const string&, const string&);
    StudentGroup(const StudentGroup&);
    StudentGroup& operator=(const StudentGroup&);
    StudentGroup(StudentGroup&&);
    StudentGroup& operator=(StudentGroup&&);
    ~StudentGroup();
    string getInstitution() const;
    string getGroupNumber() const;
    void setGroupNumber(const string&);
    void setInstitution(const string&);
    void addStudent(const Student&);

    friend ostream& operator<<(ostream& s, const StudentGroup& grp) {
        s << "\nGROUP: " << grp.groupNumber << endl;
        s << "Institution: " << grp.getInstitution() << endl;
        s << "Total Students: " << grp.count << endl;
        for (int i = 0; i < grp.count; ++i) {
            s << "\nStudent #" << i + 1 << ":" << grp.students[i];
        }
        return s;
    }
private:
    string groupNumber{ "NoGroup" };
    string institution{ "NoInstitution" };
    Student* students{ nullptr };
    int count{ 0 };
};

inline StudentGroup::StudentGroup(const string& gr, const string& inst) {
    setGroupNumber(gr);
    setInstitution(inst);
    cout << "Constructor Group(parameter): " << this << endl;
}
inline StudentGroup::StudentGroup(const StudentGroup& grp) :
    groupNumber{ grp.groupNumber }, institution{ grp.institution }, count{ grp.count } {
    students = nullptr;
    if (count > 0 && grp.students != nullptr) {
        students = new Student[count];
        for (int i = 0; i < count; ++i) {
            students[i] = grp.students[i];
        }
    }
    cout << "Constructor Group(copy): " << this << endl;
}
inline StudentGroup& StudentGroup::operator=(const StudentGroup& grp) {
        if (students != nullptr) {
            delete[] students;
            students = nullptr;
        }
        if (count > 0 && grp.students != nullptr) {
            students = new Student[count];
            for (int i = 0; i < count; ++i) {
                students[i] = grp.students[i];
            }
    }
    return *this;
}
inline StudentGroup::StudentGroup(StudentGroup&& grp)
    : groupNumber{ grp.groupNumber },
    institution{ grp.institution },
    students{ grp.students },
    count{ grp.count }
{
    grp.students = nullptr;
    grp.count = 0;
    cout << "Constructor Group(move): " << this << endl;
}
inline StudentGroup& StudentGroup::operator=(StudentGroup&& grp) {
        if (students != nullptr) delete[] students;
        students = grp.students;
        count = grp.count;
        grp.students = nullptr;
        grp.count = 0;
        return *this;
}
inline StudentGroup::~StudentGroup() {
    if (students != nullptr) {
        delete[] students;
        students = nullptr;
    }
    cout << "Delete Group object: " << this << endl;
}
inline string StudentGroup::getGroupNumber() const { return groupNumber; }
inline string StudentGroup::getInstitution() const { return institution; }
inline void StudentGroup::setGroupNumber(const string& grp) {
    if (!grp.empty()) groupNumber = grp;
}
inline void StudentGroup::setInstitution(const string& inst) {
    if (!inst.empty()) institution = inst;
}
inline void StudentGroup::addStudent(const Student& st) {
    Student* temp = new Student[count + 1];
    for (int i = 0; i < count; ++i) {
        temp[i] = students[i];
    }
    temp[count] = st;
    if (students != nullptr) delete[] students;
    students = temp;
    count++;
}
