#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "Exceptions.h" 
#include "Struct.h"
#include <memory>
using namespace std;

class Wallet {
public:
    Wallet(string name, double balance);
    virtual ~Wallet() = default;
    virtual void deposit(double amount);
    virtual void withdraw(double amount);
    string getName() const { return name; }
    double getBalance() const { return balance; }
    virtual string getType() const { return "Cash"; }
    virtual string toString() const;
    virtual void save(ofstream& fout) const;
    static unique_ptr<Wallet> create(int choice, const string& name, double balance, double limit);
    static unique_ptr<Wallet> load(istream& is);
protected:
    string name;
    double balance;
};
class DebitCard : public Wallet {
public:
    DebitCard(string name, double balance);
    string getType() const { return "DebitCard"; }
};
class CreditCard : public Wallet {
public:
    CreditCard(string name, double balance, double creditLimit);
    double getCreditLimit() const { return creditLimit; }
    void withdraw(double amount);
    string getType() const { return "CreditCard"; }
    string toString() const;
    void save(ofstream& fout) const ;
private:
    double creditLimit;
};
