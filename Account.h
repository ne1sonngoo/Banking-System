#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>

// Transaction types
enum class TransactionType
{
    Deposit,
    Withdraw
};

// Transaction record
struct Transaction
{
    TransactionType type;
    double amount;
    std::string timestamp;
};

class Account
{
private:
    std::string accountNumber;
    std::string name;
    double balance;
    std::vector<Transaction> transactions;

public:
    Account();
    Account(const std::string &accNum, const std::string &accName, double initialBalance);

    std::string getAccountNumber() const;
    std::string getName() const;
    double getBalance() const;

    void deposit(double amount);
    bool withdraw(double amount);

    void display() const;
    void printTransactions() const;
};

#endif
