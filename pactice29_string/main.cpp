#include <iostream>
#include <string>
#include "StudentGroup.h"
using namespace std;

//завдання1
//string wrapSubstrings(string text, const string& target) {
//    size_t pos = text.find(target, 0);
//    while (pos != string::npos) {
//        text.insert(pos, "(");
//        pos += target.length() + 1;
//        text.insert(pos, ")");
//        pos++;
//        pos = text.find(target, pos);
//    }
//    return text;
//}
//int main() {
//    string defaultStr1 = "abracadabra";
//    string defaultStr2 = "ab";
//    cout << "Result: " << wrapSubstrings(defaultStr1, defaultStr2) << endl;
//    string userStr1, userStr2;
//    cout << " Enter your string: ";
//    getline(cin, userStr1);
//    cout << "Enter the substring you are looking for: ";
//    getline(cin, userStr2);
//    cout << "Result: " << wrapSubstrings(userStr1, userStr2) << endl;
//    return 0;
//}


//завдання2
//template <class T>
//double calcAverage(T arr[], int size) {
//    double sum = 0;
//    for (int i = 0; i < size; i++) {
//        sum += arr[i];
//    }
//    return sum / size;
//}
//int main() {
//    double doubleArr[] = { 10.5, 20.5, 30.0 };
//    int doubleSize = sizeof(doubleArr) / sizeof(doubleArr[0]);
//    cout << "Average for double: "
//        << calcAverage(doubleArr, doubleSize) << endl;
//    return 0;
//}


//завдання3
int main()
{
    Student st1("Svitlana", 20, "+38096000000", "Lviv", "Ukraine", 95.5);
    cout << "\nExplicit Student Constructor" << endl;
    Student stExplicit{ "Oleh Danuh" };
    cout << stExplicit << endl; 
    cout << "\nCopy Student" << endl;
    Student st2{ st1 };
    cout << "\nMove Student" << endl;
    Student st3{ move(st2) };
    cout << "\nCreating Student Group" << endl;
    StudentGroup group("ITS-11", "IT STEP");
    group.addStudent(st1);
    group.addStudent(st3);
    group.addStudent(stExplicit);
    cout << group << endl; 
    cout << "\nGroup Copy" << endl;
    StudentGroup groupCopy{ group };
    cout << groupCopy << endl;
    cout << "\nGroup Move" << endl;
    StudentGroup groupMove{ move(group) };
    cout << groupMove << endl;
    return 0;
}
