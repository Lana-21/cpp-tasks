#pragma once
#include <exception>
#include <string>
using namespace std;

class FinanceException : public exception {
public:
    FinanceException(const string& message) : message{ message } {}
    const char* what() const noexcept override {
        return message.c_str();
    }
private:
    string message;
};
class InsufficientFundsException : public FinanceException {
public:
    InsufficientFundsException(const string& message) : FinanceException(message) {}
};
class InvalidAmountException : public FinanceException {
public:
    InvalidAmountException(const string& message) : FinanceException(message) {}
};
class WalletNotFoundException : public FinanceException {
public:
    WalletNotFoundException(const string& message) : FinanceException(message) {}
};
