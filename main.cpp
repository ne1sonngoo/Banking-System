#include "Bank.h"
#include <iostream>

int main()
{
    Bank bank;
    bank.loadFromFile();

    while (true)
    {
        std::cout << "\n1. Create Account\n2. Login\n3. Exit\nChoice: ";
        int choice;
        std::cin >> choice;

        if (choice == 1)
        {
            bank.createAccount();
        }
        else if (choice == 2)
        {
            int accNum, pin;
            std::cout << "Account Number: ";
            std::cin >> accNum;
            std::cout << "PIN: ";
            std::cin >> pin;

            Account *acc = bank.authenticate(accNum, pin);

            if (!acc)
            {
                std::cout << "Invalid credentials\n";
                continue;
            }
            std::cout << "\nWelcome, Account #" << acc->getAccountNumber() << "!\n";
            while (true)
            {
                std::cout << "\n1. Deposit\n2. Withdraw\n3. Balance\n4. Transactions\n5. Clear Transactions\n6. Logout\nChoice: ";
                int c;
                std::cin >> c;

                if (c == 1)
                {
                    double amt;
                    std::cout << "Amount to deposit: ";
                    std::cin >> amt;
                    acc->deposit(amt);
                    std::cout << "Deposited $" << amt << "!\n";
                    std::cout << "New Balance: $" << acc->getBalance() << std::endl;
                }
                else if (c == 2)
                {
                    double amt;
                    std::cout << "Amount to withdraw: ";
                    std::cin >> amt;
                    if (!acc->withdraw(amt))
                        std::cout << "Insufficient funds\n";
                    else
                        std::cout << "Withdrew $" << amt << "!\n";
                    std::cout << "New Balance: $" << acc->getBalance() << std::endl;
                }
                else if (c == 3)
                {
                    std::cout << "Balance: $" << acc->getBalance() << std::endl;
                }
                else if (c == 4)
                {
                    acc->printTransactions();
                }
                else if (c == 5)
                {
                    acc->clearTransactions();
                    std::cout << "Transaction history cleared.\n";
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            bank.saveToFile();
            break;
        }
    }

    return 0;
}
