#ifndef BANK_H
#define BANK_H

#include "Account.h"
#include <vector>

class Bank
{
private:
    std::vector<Account> accounts;

public:
    void loadFromFile();
    void saveToFile() const;
    bool transfer(Account *from, int toAccountNumber, double amount);

    void createAccount();
    Account *authenticate(int accNum, int pin);
};

#endif
