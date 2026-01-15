#include <iostream>
#include <unordered_map>
#include "Account.h"

int main()
{
    std::unordered_map<std::string, Account> accounts;

    while (true)
    {
        std::cout << "\n=== Banking System ===\n";
        std::cout << "1. Create Account\n";
        std::cout << "2. Deposit\n";
        std::cout << "3. Withdraw\n";
        std::cout << "4. Display Account\n";
        std::cout << "5. Show Transactions\n";
        std::cout << "6. Exit\n";
        std::cout << "Choose option: ";

        int choice;
        std::cin >> choice;

        if (choice == 1)
        {
            std::string accNum, name;
            double balance;

            std::cout << "Enter account number: ";
            std::cin >> accNum;

            if (accounts.find(accNum) != accounts.end())
            {
                std::cout << "Account already exists!\n";
                continue;
            }

            std::cin.ignore();
            std::cout << "Enter account name: ";
            std::getline(std::cin, name);

            std::cout << "Enter initial balance: ";
            std::cin >> balance;

            accounts.emplace(accNum, Account(accNum, name, balance));
            std::cout << "Account created successfully!\n";
        }

        else if (choice == 2)
        {
            std::string accNum;
            double amount;

            std::cout << "Enter account number: ";
            std::cin >> accNum;

            auto it = accounts.find(accNum);
            if (it != accounts.end())
            {
                std::cout << "Enter deposit amount: ";
                std::cin >> amount;
                it->second.deposit(amount);
            }
            else
            {
                std::cout << "Account not found!\n";
            }
        }

        else if (choice == 3)
        {
            std::string accNum;
            double amount;

            std::cout << "Enter account number: ";
            std::cin >> accNum;

            auto it = accounts.find(accNum);
            if (it != accounts.end())
            {
                std::cout << "Enter withdrawal amount: ";
                std::cin >> amount;
                it->second.withdraw(amount);
            }
            else
            {
                std::cout << "Account not found!\n";
            }
        }

        else if (choice == 4)
        {
            std::string accNum;
            std::cout << "Enter account number: ";
            std::cin >> accNum;

            auto it = accounts.find(accNum);
            if (it != accounts.end())
            {
                it->second.display();
            }
            else
            {
                std::cout << "Account not found!\n";
            }
        }

        else if (choice == 5)
        {
            std::string accNum;
            std::cout << "Enter account number: ";
            std::cin >> accNum;

            auto it = accounts.find(accNum);
            if (it != accounts.end())
            {
                it->second.printTransactions();
            }
            else
            {
                std::cout << "Account not found!\n";
            }
        }

        else if (choice == 6)
        {
            std::cout << "Exiting program...\n";
            break;
        }

        else
        {
            std::cout << "Invalid choice!\n";
        }
    }

    return 0;
}
