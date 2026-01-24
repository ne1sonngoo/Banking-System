#include "Bank.h"
#include <iostream>
#include <limits>
#include <string>

// ---------- Input Utilities ----------
int getIntInput(const std::string &prompt)
{
    int value;
    while (true)
    {
        std::cout << prompt;
        if (std::cin >> value)
            break;

        std::cout << "Invalid input. Try again.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

double getDoubleInput(const std::string &prompt)
{
    double value;
    while (true)
    {
        std::cout << prompt;
        if (std::cin >> value)
            break;

        std::cout << "Invalid input. Try again.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

// ---------- Menus ----------
int mainMenu()
{
    std::cout << "\n===== Welcome to Simple Bank =====\n";
    std::cout << "1. Create Account\n2. Login\n3. Exit\n";
    return getIntInput("Choice: ");
}

int accountMenu()
{
    std::cout << "\n----- Account Menu -----\n";
    std::cout << "1. Deposit\n2. Withdraw\n3. Check Balance\n4. View Transactions\n";
    std::cout << "5. Clear Transactions\n6. Transfer\n7. Search Transactions\n8. Logout\n";
    return getIntInput("Choice: ");
}

// ---------- Account Handler ----------
void handleAccount(Bank &bank, Account *acc)
{
    std::cout << "\nWelcome, Account #" << acc->getAccountNumber() << "!\n";

    while (true)
    {
        int choice = accountMenu();
        switch (choice)
        {
        case 1:
        {
            double amt = getDoubleInput("Amount to deposit: ");
            acc->deposit(amt);
            std::cout << "Deposited $" << amt
                      << ". New balance: $" << acc->getBalance() << "\n";
            break;
        }
        case 2:
        {
            double amt = getDoubleInput("Amount to withdraw: ");
            if (!acc->withdraw(amt))
                std::cout << "Insufficient funds!\n";
            else
                std::cout << "Withdrew $" << amt
                          << ". New balance: $" << acc->getBalance() << "\n";
            break;
        }
        case 3:
            std::cout << "Current balance: $" << acc->getBalance() << "\n";
            break;
        case 4:
            acc->printTransactions();
            break;
        case 5:
        {
            char confirm;
            std::cout << "Are you sure you want to clear all transactions? (y/n): ";
            std::cin >> confirm;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (confirm == 'y' || confirm == 'Y')
            {
                acc->clearTransactions();
                std::cout << "Transaction history cleared.\n";
            }
            else
            {
                std::cout << "Cancelled.\n";
            }
            break;
        }
        case 6:
        {
            int targetAcc = getIntInput("Transfer to account #: ");
            double amt = getDoubleInput("Amount to transfer: ");
            if (bank.transfer(acc, targetAcc, amt))
                std::cout << "Transfer successful.\n";
            else
                std::cout << "Transfer failed.\n";
            break;
        }
        case 7:
        {
            std::cout << "Enter keyword or date (YYYY-MM-DD): ";
            std::string query;
            std::getline(std::cin, query);
            acc->searchTransactions(query);
            break;
        }
        case 8:
            std::cout << "Logging out...\n";
            return;
        default:
            std::cout << "Invalid choice. Try again.\n";
        }
    }
}

// ---------- Main ----------
int main()
{
    Bank bank;
    bank.loadFromFile();

    while (true)
    {
        int choice = mainMenu();
        if (choice == 1)
        {
            bank.createAccount();
        }
        else if (choice == 2)
        {
            int accNum = getIntInput("Account Number: ");
            int pin = getIntInput("PIN: ");
            Account *acc = bank.authenticate(accNum, pin);

            if (!acc)
            {
                std::cout << "Invalid credentials!\n";
                continue;
            }

            handleAccount(bank, acc);
        }
        else if (choice == 3)
        {
            bank.saveToFile();
            std::cout << "Exiting program. Goodbye!\n";
            break;
        }
        else
        {
            std::cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
