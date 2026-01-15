#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>

class Account
{
private:
    int accountNumber;
    int pin;
    double balance;
    std::vector<std::string> transactions;

public:
    Account(int accNum, int pin, double balance = 0.0);

    int getAccountNumber() const;
    bool verifyPin(int inputPin) const;
    double getBalance() const;

    void deposit(double amount);
    bool withdraw(double amount);

    void printTransactions() const;
    void clearTransactions();

    std::string serialize() const;
    static Account deserialize(const std::string &line);
};

#endif
