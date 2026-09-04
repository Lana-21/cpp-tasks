#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <algorithm>
using namespace std;

//завдання1
string deleteComments(string text) {
    string result = "";
    size_t pos = 0;
    while (pos < text.length()) {
        size_t lineComment = text.find("//", pos);
        size_t  blockComment = text.find("/*", pos);
        size_t nextComment = min(lineComment, blockComment);
        if (nextComment == string::npos) {
            result += text.substr(pos);
            break;
        }
        result += text.substr(pos, nextComment - pos);
        if (nextComment == lineComment) {
            size_t endLine = text.find("\n", nextComment+2);
            pos = (endLine != string::npos) ? endLine : text.length();
        }
        else {
            size_t endBlock = text.find("*/", nextComment + 2);
            pos = (endBlock != string::npos) ? endBlock + 2 : text.length();
        }
    }
    return result;
}
int main() {
    ifstream file("input.txt");
    if (!file.is_open()) {
        cerr << "Error!" << endl;
        return 1;
    }
    string text = "";
    string line;
    while (getline(file, line)) {
        text += line + "\n";
    }
    file.close();
    string cleanText = deleteComments(text);
    cout << cleanText << endl;
    return 0;
}



//завдання2
string compressText(string str) {
    size_t last = str.find_last_not_of(' ');
    if (last == string::npos) {
        return str;
    }
    str.erase(last + 1);
    size_t first = str.find_first_not_of(' ');
    size_t i = first;
    while (i < str.length() - 1) {
        if (str[i] == ' ' && str[i + 1] == ' ') {
            str.erase(i, 1); 
        }
        else {
            ++i; 
        }
    }
    return str;
}
int main() {
    string test1 = "   Hello    world   from   ITSTEP   ";
    string test2 = "     "; 
    cout << "Test 1 Original: \"" << test1 << "\"" << endl;
    cout << "Test 1 Result:   \"" << compressText(test1) << "\"" << endl;
    cout << "Test 2 Original: \"" << test2 << "\"" << endl;
    cout << "Test 2 Result:   \"" << compressText(test2) << "\"" << endl;
    return 0;
}


//завдання3
template <typename T, size_t N>
class StaticArray {
private:
    T data[N]; 
public:
    StaticArray() = default;
    size_t getSize() const {
        return N;
    }
    T& operator[](size_t index) {
        assert(index < N && "Index out of range!");
        return data[index];
    }
    const T& operator[](size_t index) const {
        assert(index < N && "Index out of range!");
        return data[index];
    }
    void showAll() const {
        for (size_t i = 0; i < N; ++i) {
            cout << i + 1 << data[i] << endl;
        }
    }
};
class Student {
private:
    string fullName{ "NoName" };
    int age{ 0 };
    string phone{ "NoPhone" };
    string city{ "NoCity" };
    string country{ "NoCountry" };
    double rating{ 0.0 };

public:
    Student() = default;
    Student(const string& nm, int a, const string& ph, const string& ct, const string& cntr, double r)
        : fullName{ nm }, age{ a }, phone{ ph }, city{ ct }, country{ cntr }, rating{ r } {
    }

    inline string getFullName() const { return fullName; }
    inline int getAge() const { return age; }
    inline string getPhone() const { return phone; }
    inline string getCity() const { return city; }
    inline string getCountry() const { return country; }
    inline double getRating() const { return rating; }

    inline void setFullName(const string& nm) { if (!nm.empty()) fullName = nm; }
    inline void setAge(int a) { age = a; }
    inline void setPhone(const string& ph) { if (!ph.empty()) phone = ph; }
    inline void setCity(const string& ct) { if (!ct.empty()) city = ct; }
    inline void setCountry(const string& cntr) { if (!cntr.empty()) country = cntr; }
    inline void setRating(double r) { rating = r; }

    friend ostream& operator<<(ostream& s, const Student& st) {
        s << "\nStudent Details:\n"
            << "Full Name: " << st.fullName << endl
            << "Age: " << st.age << endl
            << "Phone: " << st.phone << endl
            << "City: " << st.city << endl
            << "Country: " << st.country << endl
            << "Rating: " << st.rating << endl;
        return s;
    }
};
int main() {
    StaticArray<string, 3> stringArray;
    stringArray[0] = "C++ Language";
    stringArray[1] = "Class Templates";
    stringArray[2] = "string ITSTEP";

    cout << "ARRAY OF STRINGS" << endl;
    stringArray.showAll();

    StaticArray<Student, 2> studentGroup;
    studentGroup[0] = Student("Svitlana", 20, "+38096000000", "Lviv", "Ukraine", 90.5);
    studentGroup[1] = Student("Oleh Petrenko", 21, "+38097000000", "Kyiv", "Ukraine", 88.0);

    cout << "\nARRAY OF STUDENTS" << endl;
    studentGroup.showAll();

    return 0;
}
