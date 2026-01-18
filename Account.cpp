#include "Account.h"
#include "Utils.h"
#include <iostream>
#include <sstream>
#include <iomanip>

Account::Account(int accNum, int pinCode, double initialBalance)
    : accountNumber(accNum), pin(pinCode), balance(initialBalance) {}

bool Account::verifyPin(int enteredPin) const
{
    return pin == enteredPin;
}

void Account::deposit(double amount)
{
    balance += amount;
    addTransaction("Deposited $" + formatMoney(amount));
}

bool Account::withdraw(double amount)
{
    if (amount > balance)
        return false;
    balance -= amount;
    addTransaction("Withdrew $" + formatMoney(amount));
    return true;
}

void Account::clearTransactions()
{
    transactions.clear();
}

bool Account::transfer(Account &to, double amount)
{
    if (amount > balance)
        return false;
    balance -= amount;
    to.balance += amount;

    addTransaction("Sent $" + formatMoney(amount) +
                   " to Account #" + std::to_string(to.accountNumber));
    to.addTransaction("Received $" + formatMoney(amount) +
                      " from Account #" + std::to_string(accountNumber));
    return true;
}

double Account::getBalance() const
{
    return balance;
}

int Account::getAccountNumber() const
{
    return accountNumber;
}

void Account::addTransaction(const std::string &entry)
{
    std::string timestampedEntry = "[" + currentTimestamp() + "] " + entry;
    transactions.push_back(timestampedEntry);
}

void Account::printTransactions() const
{
    for (const auto &t : transactions)
    {
        std::cout << t << std::endl;
    }
}

std::string Account::formatMoney(double amount) const
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << amount;
    return oss.str();
}

std::string Account::serialize() const
{
    std::ostringstream oss;
    oss << accountNumber << "," << pin << "," << balance;
    for (const auto &t : transactions)
    {
        oss << "," << t;
    }
    return oss.str();
}

Account Account::deserialize(const std::string &data)
{
    std::stringstream ss(data);
    std::string token;

    getline(ss, token, ',');
    int accNum = std::stoi(token);

    getline(ss, token, ',');
    int pinCode = std::stoi(token);

    getline(ss, token, ',');
    double bal = std::stod(token);

    Account acc(accNum, pinCode, bal);

    while (getline(ss, token, ','))
    {
        acc.transactions.push_back(token);
    }

    return acc;
}
