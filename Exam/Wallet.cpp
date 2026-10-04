#include "Wallet.h"
#include "Struct.h"
#include <sstream>
using namespace std;

Wallet::Wallet(string name, double balance) : name(move(name)), balance(balance) {
}
void Wallet::deposit(double amount) {
    if (amount <= 0) {
        throw InvalidAmountException("Deposit amount must be positive!");
    }
    balance += amount;
}
void Wallet::withdraw(double amount) {
    if (amount <= 0) {
        throw InvalidAmountException("Withdrawal amount must be positive!");
    }
    if (amount > balance) {
        throw InsufficientFundsException("Insufficient funds in wallet: " + name);
    }
    balance -= amount;
}
string Wallet::toString() const {
    return " " + getType() + " " + name + ": " + formatDouble(balance) + " USD";
}
void Wallet::save(ofstream& fout) const {
    fout << getType() << "\n" << name << "\n" << balance << "\n";
}
DebitCard::DebitCard(string name, double balance)
    : Wallet(move(name), balance) {
}
CreditCard::CreditCard(string name, double balance, double creditLimit)
    : Wallet(move(name), balance), creditLimit(creditLimit) {
    if (creditLimit < 0) {
        throw InvalidAmountException("Credit limit cannot be negative!");
    }
}
void CreditCard::withdraw(double amount) {
    if (amount <= 0) {
        throw InvalidAmountException("Withdrawal amount must be positive!");
    }
    if (balance + creditLimit < amount) {
        throw InsufficientFundsException("Credit limit exceeded on card: " + name);
    }
    balance -= amount;
    double available = balance + creditLimit;
    cout << "Remaining available for withdrawal: " << formatDouble(available) << " USD\n";
}
string CreditCard::toString() const {
    return Wallet::toString() + " (Credit Limit: " + formatDouble(creditLimit) + " USD)";
}
void CreditCard::save(ofstream& fout) const {
    Wallet::save(fout);
    fout << creditLimit << "\n";
}
unique_ptr<Wallet> Wallet::create(int choice, const string& name, double balance, double limit) {
    switch (choice) {
    case 1:
        if (balance < 0) throw InvalidAmountException("Initial balance cannot be negative!");
        return make_unique<Wallet>(name, balance);
    case 2:
        if (balance < 0) throw InvalidAmountException("Initial balance cannot be negative!");
        return make_unique<DebitCard>(name, balance);
    case 3:
        return make_unique<CreditCard>(name, balance, limit);
    default:
        throw FinanceException("Invalid wallet type selected!");
    }
}
unique_ptr<Wallet> Wallet::load(istream& is) {
    string type, name;
    double balance;
    if (!getline(is, type) || type.empty()) return nullptr;
    if (!getline(is, name)) return nullptr;
    if (!(is >> balance)) return nullptr;
    is.ignore(1000, '\n');
    if (type == "Credit Card" || type == "CreditCard") {
        double limit;
        if (is >> limit) {
            is.ignore(1000, '\n'); 
            return make_unique<CreditCard>(name, balance, limit);
        }
    }
    else if (type == "Debit Card" || type == "DebitCard") {
        return make_unique<DebitCard>(name, balance);
    }
    else if (type == "Cash Wallet" || type == "Cash") {
        return make_unique<Wallet>(name, balance);
    }
    return nullptr;
}
