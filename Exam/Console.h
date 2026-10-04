#pragma once
#include <iostream>
#include <string>
#include "FinanceManager.h"
#include "Wallet.h"
using namespace std;

inline void showMenu(int currentDay) {
    cout << endl;
    cout << "PERSONAL FINANCE MANAGER\n\n";
    cout << "Current Day of Month: " << currentDay << "\n";
    cout << " 1. Add Wallet\n";
    cout << " 2. Deposit Money\n";
    cout << " 3. Add Expense\n";
    cout << " 4. Show All Wallets and Balances\n";
    cout << " 5. Show Finance Reports (Day/Week/Month)\n";
    cout << " 6. Show TOP-3 Expenses and Categories\n";
    cout << " 7. Save Reports to File\n";
    cout << " 8. Change Current Day\n";
    cout << " 0. Exit\n";
    cout << "Select option: ";
}
template <typename T>
void readInput(T& value, const string& errorMessage) {
    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << errorMessage;
    }
}
inline size_t selectWalletIndex(FinanceManager& fm) {
    if (fm.getWalletCount() == 0) {
        throw FinanceException("No wallets available! Please create a wallet first.");
    }
    cout << fm << endl;
    cout << "Select wallet number (1-" << fm.getWalletCount() << "): ";
    int index;
    readInput(index, "Invalid input! Select wallet number: ");
    if (index < 1 || static_cast<size_t>(index) > fm.getWalletCount()) {
        throw FinanceException("Invalid wallet selection!");
    }
    return static_cast<size_t>(index - 1);
}
inline void inputAddWallet(FinanceManager& fm) {
    cout << "Select type (1 - Cash Wallet, 2 - Debit Card, 3 - Credit Card): ";
    int choice;
    readInput(choice, "Invalid input! Select type (1-3): ");
    cout << "Enter wallet name: ";
    string name;
    cin.ignore(1000, '\n');
    getline(cin, name);
    cout << "Enter initial balance: ";
    double balance;
    readInput(balance, "Invalid input! Enter balance: ");
    double limit = 0.0;
    if (choice == 3) {
        cout << "Enter credit limit: ";
        readInput(limit, "Invalid input! Enter credit limit: ");
    }
    auto wallet = Wallet::create(choice, name, balance, limit);
    fm.addWallet(move(wallet));
    cout << "Wallet successfully added!\n";
}
inline void inputDeposit(FinanceManager& fm) {
    size_t walletIdx = selectWalletIndex(fm);
    cout << "Enter deposit amount: ";
    double amount;
    readInput(amount, "Invalid input! Enter deposit amount: ");
    fm.depositToWallet(walletIdx, amount);
    cout << "Deposit successful!\n";
}
inline void inputAddExpense(FinanceManager& fm) {
    size_t walletIdx = selectWalletIndex(fm);
    cout << "Enter expense amount: ";
    double amount;
    readInput(amount, "Invalid input! Enter expense amount: ");
    cout << "Enter category: ";
    string category;
    cin.ignore(1000, '\n');
    getline(cin, category);
    category = toLower(category);
    cout << "Enter day of month (1-31): ";
    int day;
    readInput(day, "Invalid input! Enter day (1-31): ");
    fm.addExpense(walletIdx, amount, category, day);
    cout << "Expense added successfully!\n";
}
inline void showReports(const FinanceManager& fm, int currentDay) {
    cout << fm.generateReport(currentDay, 1, "DAY") << endl;
    cout << fm.generateReport(currentDay, 7, "WEEK") << endl;
    cout << fm.generateReport(currentDay, 30, "MONTH") << endl;
}
inline void showTop3(const FinanceManager& fm, int currentDay) {
    cout << fm.getTop3Expenses(currentDay, 7, "WEEK") << endl;
    cout << fm.getTop3Expenses(currentDay, 30, "MONTH") << endl;
    cout << fm.getTop3Categories(currentDay, 7, "WEEK") << endl;
    cout << fm.getTop3Categories(currentDay, 30, "MONTH") << endl;
}
inline void inputChangeDay(int& currentDay) {
    cout << "Enter new current day (1-31): ";
    int newDay;
    readInput(newDay, "Invalid input! Enter day (1-31): ");
    if (newDay < 1 || newDay > 31) throw FinanceException("Invalid day");
    currentDay = newDay;
    cout << "Current day successfully updated to " << currentDay << endl;
}
