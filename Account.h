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

    std::string formatMoney(double amount) const;
    void addTransaction(const std::string &entry);

public:
    Account(int accNum, int pinCode, double initialBalance = 0.0);
    void clearTransactions();
    bool verifyPin(int enteredPin) const;

    void deposit(double amount);
    bool withdraw(double amount);
    bool transfer(Account &to, double amount);

    double getBalance() const;
    int getAccountNumber() const;

    void printTransactions() const;

    std::string serialize() const;
    static Account deserialize(const std::string &data);
};

#endif
