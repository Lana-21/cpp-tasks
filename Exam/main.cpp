#include <iostream>
#include <cstdlib> 
#include "FinanceManager.h"
#include "Console.h"
#include "Encryption.h"
using namespace std;

bool authorize() {
    Encryption enc;
    if (!enc.isRegistered()) {
        cout << "SYSTEM OWNER REGISTRATION\n";
        while (true) {
            string username, password;
            cout << "Enter new username: ";
            getline(cin >> ws, username);
            cout << "Enter new password: ";
            getline(cin >> ws, password);
            if (enc.registerUser(username, password)) {
                cout << "\nSUCCESS\n\n";
                return true; 
            }
            else {
                cout << "\nERROR\n";
                cout << "Please try registering again\n\n";
            }
        }
    }
    cout << "USER LOGIN\n";
    while (true) {
        string username, password;
        cout << "Username: ";
        getline(cin >> ws, username);
        cout << "Password: ";
        getline(cin >> ws, password);
        if (enc.login(username, password)) {
            cout << "\nSUCCESS\n\n";
            return true; 
        }
        else {
            cout << "\nERROR\n";
            cout << "Please try again\n\n";
        }
    }
}
int main() {
    if (!authorize()) {
        return 0;
    }
    FinanceManager fm;
    try {
        fm.loadFromFile("data.txt");
    }
    catch (...) {
    }
    int choice = 0;
    int currentDay = 30;
    do {
        system("cls");
        showMenu(currentDay);
        if (!(cin >> choice)) {
            cout << "Invalid input" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            system("pause");
            continue;
        }
        try {
            switch (choice) {
            case 1:  inputAddWallet(fm); break;
            case 2:  inputDeposit(fm); break;
            case 3:  inputAddExpense(fm); break;
            case 4:  cout << fm << endl; break;
            case 5:  showReports(fm, currentDay); break;
            case 6:  showTop3(fm, currentDay); break;
            case 7:  fm.saveReportToFile("report.txt", currentDay); cout << "Report saved successfully\n"; break;
            case 8:  inputChangeDay(currentDay); break;
            case 0:  cout << "Exiting program" << endl; break;
            default: cout << "Invalid menu choice" << endl; break;
            }
        }
        catch (const FinanceException& e) {
            cerr << "\nFinance Error: " << e.what() << endl;
        }
        catch (const exception& e) {
            cerr << "\nStandard Error: " << e.what() << endl;
        }
        if (choice != 0) {
         system("pause");
        }
    } while (choice != 0);
    return 0;
}
