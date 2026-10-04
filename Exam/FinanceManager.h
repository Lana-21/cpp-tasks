#pragma once
#include <vector>
#include <memory>
#include <ostream>
#include "Struct.h"
#include "Wallet.h"
using namespace std;

class FinanceManager {
public:
    FinanceManager() = default;
    void addWallet(unique_ptr<Wallet> wallet);
    void depositToWallet(size_t index, double amount);
    void addExpense(size_t walletIndex, double amount, const string& category, int day);

    size_t getWalletCount() const { return wallets.size(); }
    string getWalletName(size_t index) const;

    string generateReport(int currentDay, int daysPeriod, const string& periodName) const;
    string getTop3Expenses(int currentDay, int daysPeriod, const string& periodName) const;
    string getTop3Categories(int currentDay, int daysPeriod, const string& periodName) const;

    void saveToFile(const string& filename) const;
    void loadFromFile(const string& filename);
    void saveReportToFile(const string& filename, int currentDay) const;
    friend ostream& operator<<(ostream& os, const FinanceManager& fm);
private:
    vector<unique_ptr<Wallet>> wallets;
    vector<Expense> expenses;
    vector<Expense> getExpensesForPeriod(int currentDay, int daysPeriod) const;
    const size_t TOP = 3;
};
