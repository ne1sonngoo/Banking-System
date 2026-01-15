#include "Account.h"
#include <iostream>
#include <iomanip>
#include <ctime>

std::string currentTimestamp()
{
    std::time_t now = std::time(nullptr);
    char buf[100];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return buf;
}

Account::Account() : accountNumber(""), name(""), balance(0.0) {}

Account::Account(const std::string &accNum, const std::string &accName, double initialBalance)
    : accountNumber(accNum), name(accName), balance(initialBalance) {}

std::string Account::getAccountNumber() const
{
    return accountNumber;
}

std::string Account::getName() const
{
    return name;
}

double Account::getBalance() const
{
    return balance;
}

void Account::deposit(double amount)
{
    if (amount <= 0)
    {
        std::cout << "Invalid deposit amount!\n";
        return;
    }

    balance += amount;
    transactions.push_back({TransactionType::Deposit, amount, currentTimestamp()});
}

bool Account::withdraw(double amount)
{
    if (amount <= 0 || amount > balance)
    {
        std::cout << "Insufficient funds or invalid amount!\n";
        return false;
    }

    balance -= amount;
    transactions.push_back({TransactionType::Withdraw, amount, currentTimestamp()});
    return true;
}

void Account::display() const
{
    std::cout << "\nAccount Number: " << accountNumber << "\n";
    std::cout << "Account Name: " << name << "\n";
    std::cout << "Balance: $" << std::fixed << std::setprecision(2) << balance << "\n";
}

void Account::printTransactions() const
{
    if (transactions.empty())
    {
        std::cout << "No transactions available.\n";
        return;
    }

    std::cout << "\n--- Transaction History ---\n";
    for (const auto &t : transactions)
    {
        std::cout
            << (t.type == TransactionType::Deposit ? "DEPOSIT " : "WITHDRAW ")
            << "$" << t.amount
            << " | " << t.timestamp << "\n";
    }
}
