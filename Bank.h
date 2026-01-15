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

    void createAccount();
    Account *authenticate(int accNum, int pin);
};

#endif
