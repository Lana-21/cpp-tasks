#include <iostream>
#include <string>
#include <format>
using namespace std;

struct Date {
    int day;
    int month;
    int year;
    Date() : day{ 1 }, month{ 1 }, year{ 2026 } {}
    Date(int d, int m, int y) : day{ d }, month{ m }, year{ y } {}
    string toString() const {
        return format("{:02d}.{:02d}.{}", day, month, year);
    }
};
class Passport {
public:
    Passport() {
        cout << "constructor Passport " << this << endl;
    }
    Passport(string fullName, string number) :
        fullName{ fullName },
        number{ number } {
        cout << "constructor Passport " << this << endl;
    }
    Passport(string fullName, string number, Date issueDate) :
        fullName{ fullName },
        number{ number },
        issueDate{ issueDate } {
        cout << "constructor Passport " << this << endl;
    }
    ~Passport() {
        cout << "destructor Passport " << this << endl;
    }
    string getFullName() const { return fullName; }
    string getNumber() const { return number; }
    Date getIssueDate() const { return issueDate; }
    void setFullName(string name) {
        if (!name.empty()) fullName = name;
    }
    void setNumber(string num) {
        if (num.length() >= 6) number = num;
    }
    void setIssueDate(Date date) {
        issueDate = date;
    }
    string passportToString() const {
        return format("Full Name: {}; Passport: {}; Date: {}\n", fullName, number, issueDate.toString());
    }
    void show() {
        cout << passportToString();
    }
protected:
    string fullName{ "" };
    string number{ "" };
    Date issueDate{};
};
class ForeignPassport : public Passport {
public:
    ForeignPassport(int pageCount, string foreignNum) :
        pageCount{ pageCount },
        foreignNumber{ foreignNum } {
        cout << "constructor ForeignPassport " << this << endl;
    }
    ForeignPassport(string fullName, string number, string foreignNum, int pageCount, Date issueDate) :
        Passport(fullName, number, issueDate),
        foreignNumber{ foreignNum },
        pageCount{ pageCount } {
        cout << "constructor ForeignPassport " << this << endl;
    }
    ~ForeignPassport() {
        cout << "destructor ForeignPassport " << this << endl;
    }
    int getPageCount() const { return pageCount; }
    string getForeignNumber() const { return foreignNumber; }
    int getVisaCount() const { return visaCount; }
    void setPageCount(int pages) {
        if (pages > 0) pageCount = pages;
    }
    void setForeignNumber(string fNum) {
        if (!fNum.empty()) foreignNumber = fNum;
    }
    void addVisa(string newVisa) {
        if (visaCount < 10) {
            visas[visaCount] = newVisa;
            visaCount++;
        }
    }
    string foreignPassportToString() const {
        string visaList = "";
        for (int i = 0; i < visaCount; i++) {
            visaList += visas[i] + " ";
        }
        if (visaCount == 0) visaList = "none";
        return format("Foreign No: {}, Pages: {}, Visas: {}\n", foreignNumber, pageCount, visaList);
    }
    void show() {
        Passport::show();
        cout << foreignPassportToString();
    }
private:
    int pageCount{ 0 };
    string foreignNumber{ "" };
    string visas[10];
    int visaCount{ 0 };
};
int main()
{
    Passport passport{ "Oleh Ivanov", "123456789", {12, 4, 2026} };
    passport.show();
    cout << endl;
    passport.setFullName("Oleh V. Ivanov");
    passport.setIssueDate(Date(15, 7, 2026));
    cout << "Updated Passport\n";
    passport.show();
    cout << endl;
    ForeignPassport fp{ 32, "FP987654" };
    fp.show();
    cout << endl;
    ForeignPassport fp1{ "Ivan Ivanov", "987654321", "FP112233", 48, {15, 8, 2026} };
    fp1.show();
    cout << "\n addVisa Schengen\n";
    fp1.addVisa("Schengen");
    fp1.show();
    cout << endl;
    Passport* passport1 = new ForeignPassport("Alex Botter", "555666777", "FP445566", 32, { 1, 1, 2026 });
    ((ForeignPassport*)passport1)->show();
    cout << "\n addVisa USA\n";
    ((ForeignPassport*)passport1)->addVisa("USA");
    ((ForeignPassport*)passport1)->setPageCount(64);
    ((ForeignPassport*)passport1)->show();
    delete (ForeignPassport*)passport1;
    system("pause");
    return 0;
}
