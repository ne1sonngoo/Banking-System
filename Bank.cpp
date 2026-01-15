#include "Bank.h"
#include <fstream>
#include <iostream>

void Bank::loadFromFile()
{
    std::ifstream file("data.txt");
    std::string line;

    while (getline(file, line))
    {
        accounts.push_back(Account::deserialize(line));
    }
}

void Bank::saveToFile() const
{
    std::ofstream file("data.txt");
    for (const auto &acc : accounts)
    {
        file << acc.serialize() << std::endl;
    }
}

void Bank::createAccount()
{
    int accNum, pin;
    std::cout << "Enter new account number: ";
    std::cin >> accNum;
    std::cout << "Set PIN: ";
    std::cin >> pin;

    accounts.emplace_back(accNum, pin);
    std::cout << "Account created!\n";
}

Account *Bank::authenticate(int accNum, int pin)
{
    for (auto &acc : accounts)
    {
        if (acc.getAccountNumber() == accNum && acc.verifyPin(pin))
        {
            return &acc;
        }
    }
    return nullptr;
}
