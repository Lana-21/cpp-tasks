#include "FinanceManager.h"
#include <algorithm>
#include <map>
#include <fstream> 
using namespace std;

void FinanceManager::addWallet(unique_ptr<Wallet> wallet) {
    wallets.push_back(move(wallet));
    saveToFile("data.txt");
}
void FinanceManager::depositToWallet(size_t index, double amount) {
    if (index >= wallets.size()) {
        throw FinanceException("Invalid wallet index!");
    }
    wallets[index]->deposit(amount);
    saveToFile("data.txt");
}
void FinanceManager::addExpense(size_t walletIndex, double amount, const string& category, int day) {
    if (walletIndex >= wallets.size()) {
        throw FinanceException("Invalid wallet index!");
    }
    Expense exp(amount, category, day);
    if (!exp.isValid()) {
        throw InvalidAmountException("Invalid expense details!");
    }
    wallets[walletIndex]->withdraw(amount);
    expenses.push_back(move(exp));
    saveToFile("data.txt");
}
string FinanceManager::getWalletName(size_t index) const {
    if (index >= wallets.size()) {
        throw FinanceException("Invalid wallet index!");
    }
    return wallets[index]->getName();
}
vector<Expense> FinanceManager::getExpensesForPeriod(int currentDay, int daysPeriod) const {
    vector<Expense> filtered;
    for (const auto& exp : expenses) {
        if (exp.isInPeriod(currentDay, daysPeriod)) {
            filtered.push_back(exp);
        }
    }
    return filtered;
}
string FinanceManager::generateReport(int currentDay, int daysPeriod, const string& periodName) const {
    vector<Expense> periodExpenses = getExpensesForPeriod(currentDay, daysPeriod);
    string res = "REPORT FOR " + periodName + "\n";
    if (periodExpenses.empty()) return res + "  No expenses in this period.\n";
    double total = 0.0;
    for (const auto& exp : periodExpenses) {
        res += "  " + exp.toString() + "\n";
        total += exp.getAmount();
    }
    res += "TOTAL EXPENSES: " + formatDouble(total) + " USD\n";
    return res;
}
string FinanceManager::getTop3Expenses(int currentDay, int daysPeriod, const string& periodName) const {
    vector<Expense> periodExpenses = getExpensesForPeriod(currentDay, daysPeriod);
    sort(periodExpenses.begin(), periodExpenses.end(), Expense::compareByAmountDesc);
    string res = "\nTOP-3 EXPENSES FOR " + periodName + "\n";
    if (periodExpenses.empty()) return res + "  No data available.\n";
    size_t count = min(periodExpenses.size(), TOP);
    for (size_t i = 0; i < count; ++i) {
        res += "  " + to_string(i + 1) + ". " + periodExpenses[i].toString() + "\n";
    }
    return res;
}
string FinanceManager::getTop3Categories(int currentDay, int daysPeriod, const string& periodName) const {
    vector<Expense> periodExpenses = getExpensesForPeriod(currentDay, daysPeriod);
    map<string, double> categoryTotalsMap;
    for (const auto& exp : periodExpenses) {
        categoryTotalsMap[toLower(exp.getCategory())] += exp.getAmount();
    }
    vector<CategoryTotal> sorted;
    for (const auto& pair : categoryTotalsMap) {
        sorted.push_back({ pair.first, pair.second });
    }
    sort(sorted.begin(), sorted.end(), CategoryTotal::compareByTotalDesc);
    string res = "\nTOP-3 CATEGORIES FOR " + periodName + "\n";
    if (sorted.empty()) return res + "  No data available.\n";
    size_t count = min(sorted.size(), TOP);
    for (size_t i = 0; i < count; ++i) {
        res += "  " + to_string(i + 1) + ". " + sorted[i].toString() + "\n";
    }
    return res;
}
void FinanceManager::saveToFile(const string& filename) const {
    ofstream fout(filename);
    if (!fout.is_open()) throw FinanceException("Cannot open file for writing!");
    fout << wallets.size() << "\n";
    for (const auto& w : wallets) {
        w->save(fout);
    }
    fout << expenses.size() << "\n";
    for (const auto& exp : expenses) {
        fout << exp << "\n"; 
    }
}
void FinanceManager::loadFromFile(const string& filename) {
    ifstream fin(filename);
    if (!fin.is_open()) throw FinanceException("Cannot open file!");
    wallets.clear();
    expenses.clear();
    size_t walletCount = 0, expenseCount = 0;
    if (fin >> walletCount) {
        fin.ignore(1000, '\n'); 
        while (walletCount--) {
            if (auto wallet = Wallet::load(fin)) {
                wallets.push_back(move(wallet));
            }
        }
    }
    if (fin >> expenseCount) {
        fin.ignore(1000, '\n'); 
        Expense exp;
        while (expenseCount-- && (fin >> exp)) {
            expenses.push_back(exp);
        }
    }
}
void FinanceManager::saveReportToFile(const string& filename, int currentDay) const {
    ofstream fout(filename);
    if (!fout.is_open()) throw FinanceException("Cannot open report file for writing!");
    fout << generateReport(currentDay, 1, "DAY") << "\n";
    fout << generateReport(currentDay, 7, "WEEK") << "\n";
    fout << generateReport(currentDay, 30, "MONTH") << "\n";
    fout << getTop3Expenses(currentDay, 7, "WEEK") << "\n";
    fout << getTop3Expenses(currentDay, 30, "MONTH") << "\n";
    fout << getTop3Categories(currentDay, 7, "WEEK") << "\n";
    fout << getTop3Categories(currentDay, 30, "MONTH") << "\n";
}
ostream& operator<<(ostream& os, const FinanceManager& fm) {
    os << "WALLETS LIST\n";
    if (fm.wallets.empty()) {
        os << "  No wallets added yet.\n";
    }
    else {
        for (size_t i = 0; i < fm.wallets.size(); ++i) {
            os << "  " << (i + 1) << ". " << fm.wallets[i]->toString() << "\n";
        }
    }
    return os;
}
