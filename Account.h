#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account
{
private:
    std::string accountNumber;
    std::string name;
    double balance;

public:
    Account(const std::string &accNum, const std::string &accName, double initialBalance);

    std::string getAccountNumber() const;
    std::string getName() const;
    double getBalance() const;

    void deposit(double amount);
    bool withdraw(double amount);
    void display() const;
};

#endif
