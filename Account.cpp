#include "Account.h"
#include <iostream>
#include <sstream>
#include "Utils.h"

Account::Account(int accNum, int pin, double balance)
    : accountNumber(accNum), pin(pin), balance(balance) {}

int Account::getAccountNumber() const
{
    return accountNumber;
}

bool Account::verifyPin(int inputPin) const
{
    return pin == inputPin;
}

double Account::getBalance() const
{
    return balance;
}

void Account::clearTransactions()
{
    transactions.clear();
}

void Account::deposit(double amount)
{
    balance += amount;
    transactions.push_back("Deposited: $" + formatMoney(amount));
}

void Account::addTransaction(const std::string &message)
{
    transactions.push_back(message);
}

bool Account::withdraw(double amount)
{
    if (amount > balance)
        return false;
    balance -= amount;
    transactions.push_back("Withdrew: $" + formatMoney(amount));
    return true;
}

void Account::printTransactions() const
{
    for (const auto &t : transactions)
    {
        std::cout << t << std::endl;
    }
}

std::string Account::serialize() const
{
    std::ostringstream out;
    out << accountNumber << "," << pin << "," << balance;
    for (const auto &t : transactions)
    {
        out << "," << t;
    }
    return out.str();
}

Account Account::deserialize(const std::string &line)
{
    std::stringstream ss(line);
    std::string token;

    getline(ss, token, ',');
    int accNum = std::stoi(token);

    getline(ss, token, ',');
    int pin = std::stoi(token);

    getline(ss, token, ',');
    double balance = std::stod(token);

    Account acc(accNum, pin, balance);

    while (getline(ss, token, ','))
    {
        acc.transactions.push_back(token);
    }

    return acc;
}
