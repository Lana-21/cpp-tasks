#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Company {
public:
    Company() {}
    Company(string title, string owner, string phone, string address, string activity)
        : title(title), owner(owner), phone(phone), address(address), activity(activity) {
    }
    string getTitle() const { return title; }
    string getOwner() const { return owner; }
    string getPhone() const { return phone; }
    string getActivity() const { return activity; }
    friend ifstream& operator>>(ifstream& s, Company& cm) {
        getline(s, cm.title);
        getline(s, cm.owner);
        getline(s, cm.phone);
        getline(s, cm.address);
        getline(s, cm.activity);
        return s;
    }
    friend ofstream& operator<<(ofstream& s, const Company& cm) {
        s << cm.title << endl;
        s << cm.owner << endl;
        s << cm.phone << endl;
        s << cm.address << endl;
        s << cm.activity << endl;
        return s;
    }
    friend ostream& operator<<(ostream& s, const Company& cm) {
        s << "Title: " << cm.title << endl;
        s << "Owner: " << cm.owner << endl;
        s << "Phone: " << cm.phone << endl;
        s << "Address: " << cm.address << endl;
        s << "Activity: " << cm.activity << endl;
        return s;
    }
private:
    string title;
    string owner;
    string phone;
    string address;
    string activity;
};

class Directory {
public:
    Directory() {
        loadFromFile();
    }
    ~Directory() {
        delete[] companies;
    }
    void loadFromFile() {
        if (companies != nullptr) {
            delete[] companies;
            companies = nullptr;
        }
        ifstream my_fin(path);
        if (!my_fin.is_open()) {
            count = 0;
            return;
        }
        my_fin >> count;
        my_fin.ignore(); 
        if (count > 0) {
            companies = new Company[count];
            for (int i = 0; i < count; i++) {
                my_fin >> companies[i];
            }
        }
        my_fin.close();
    }
    void saveToFile() {
        ofstream my_fout(path);
        if (!my_fout.is_open()) {
            cerr << "Error: open file!!!\n";
            return;
        }
        my_fout << count << endl;
        for (int i = 0; i < count; i++) {
            my_fout << companies[i];
        }
        my_fout.close();
    }
    void addCompany() {
        string title, owner, phone, address, activity;
        cin.ignore();
        cout << "Enter company title: ";
        getline(cin, title);
        cout << "Enter owner name: ";
        getline(cin, owner);
        cout << "Enter phone number: "; 
        getline(cin, phone);
        cout << "Enter address: "; 
        getline(cin, address);
        cout << "Enter activity: ";
        getline(cin, activity);
        Company* temp = new Company[count + 1];
        for (int i = 0; i < count; i++) {
            temp[i] = companies[i];
        }
        temp[count] = Company(title, owner, phone, address, activity);
        delete[] companies;
        companies = temp;
        count++;
        saveToFile();
        cout << "Company successfully added!\n";
    }
    void deleteCompany() {
        if (count == 0) {
            cout << "Directory is empty.\n";
            return;
        }
        string title;
        cout << "Enter company title to delete: ";
        cin.ignore();
        getline(cin, title);
        int index = -1;
        for (int i = 0; i < count; i++) {
            if (companies[i].getTitle() == title) {
                index = i;
                break;
            }
        }
        if (index != -1) {
            Company* temp = nullptr;
            if (count - 1 > 0) {
                temp = new Company[count - 1];
                for (int i = 0, j = 0; i < count; i++) {
                    if (i != index) {
                        temp[j++] = companies[i];
                    }
                }
            }
            delete[] companies;
            companies = temp;
            count--;
            saveToFile();
            cout << "Record deleted!\n";
        }
        else {
            cout << "Company was not found.\n";
        }
    }
    void showAll() const {
        if (count == 0) {
            cout << "Directory is empty.\n";
            return;
        }
        for (int i = 0; i < count; i++) {
            cout << companies[i];
        }
    }
    void searchByTitle() const {
        string query;
        cout << "Enter title to search: ";
        cin.ignore(); 
        getline(cin, query);
        for (int i = 0; i < count; i++) {
            if (companies[i].getTitle() == query) cout << companies[i];
        }
    }
    void searchByOwner() const {
        string query;
        cout << "Enter owner name to search: ";
        cin.ignore(); 
        getline(cin, query);
        for (int i = 0; i < count; i++) {
            if (companies[i].getOwner() == query) cout << companies[i];
        }
    }
    void searchByPhone() const {
        string query;
        cout << "Enter phone number to search: ";
        cin.ignore();
        getline(cin, query);
        for (int i = 0; i < count; i++) {
            if (companies[i].getPhone() == query) cout << companies[i];
        }
    }
    void searchByActivity() const {
        string query;
        cout << "Enter activity to search: ";
        cin.ignore(); 
        getline(cin, query);
        for (int i = 0; i < count; i++) {
            if (companies[i].getActivity() == query) cout << companies[i];
        }
    }
private:
    Company* companies = nullptr;
    int count = 0;
    string path = "info.txt";
};

int main() {
    Directory dir;
    int choice;
    do {
        cout << "\nDIRECTORY MENU\n"
            << "1. Search by title\n"
            << "2. Search by owner\n"
            << "3. Search by phone number\n"
            << "4. Search by activity\n"
            << "5. Display all companies\n"
            << "6. Add company\n"
            << "7. Delete company\n"
            << "0. Exit\n"
            << "Select an option: ";
        cin >> choice;
        switch (choice) {
        case 1: dir.searchByTitle(); break;
        case 2: dir.searchByOwner(); break;
        case 3: dir.searchByPhone(); break;
        case 4: dir.searchByActivity(); break;
        case 5: dir.showAll(); break;
        case 6: dir.addCompany(); break;
        case 7: dir.deleteCompany(); break;
        case 0: cout << "Exiting program\n"; break;
        default: cout << "Invalid choice!\n"; break;
        }
    } while (choice != 0);
    return 0;
}
