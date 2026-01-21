#include "Bank.h"
#include <iostream>
#include <limits>

using namespace std;

// ---------- Input Utilities ----------
int getIntInput(const string &prompt)
{
    int value;
    while (true)
    {
        cout << prompt;
        if (cin >> value)
            break;
        cout << "Invalid input. Try again.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear newline
    return value;
}

double getDoubleInput(const string &prompt)
{
    double value;
    while (true)
    {
        cout << prompt;
        if (cin >> value)
            break;
        cout << "Invalid input. Try again.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear newline
    return value;
}

// ---------- Menus ----------
int mainMenu()
{
    cout << "\n===== Welcome to Simple Bank =====\n";
    cout << "1. Create Account\n2. Login\n3. Exit\n";
    return getIntInput("Choice: ");
}

int accountMenu()
{
    cout << "\n----- Account Menu -----\n";
    cout << "1. Deposit\n2. Withdraw\n3. Check Balance\n4. View Transactions\n";
    cout << "5. Clear Transactions\n6. Transfer\n7. Search Transactions\n8. Logout\n";
    return getIntInput("Choice: ");
}

// ---------- Account Handler ----------
void handleAccount(Bank &bank, Account *acc)
{
    cout << "\nWelcome, Account #" << acc->getAccountNumber() << "!\n";

    while (true)
    {
        int choice = accountMenu();
        switch (choice)
        {
        case 1:
        { // Deposit
            double amt = getDoubleInput("Amount to deposit: ");
            acc->deposit(amt);
            cout << "Deposited $" << amt << ". New balance: $" << acc->getBalance() << "\n";
            break;
        }
        case 2:
        { // Withdraw
            double amt = getDoubleInput("Amount to withdraw: ");
            if (!acc->withdraw(amt))
                cout << "Insufficient funds!\n";
            else
                cout << "Withdrew $" << amt << ". New balance: $" << acc->getBalance() << "\n";
            break;
        }
        case 3: // Balance
            cout << "Current balance: $" << acc->getBalance() << "\n";
            break;
        case 4: // Transactions
            acc->printTransactions();
            break;
        case 5:
        { // Clear transactions
            char confirm;
            cout << "Are you sure you want to clear all transactions? (y/n): ";
            cin >> confirm;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (confirm == 'y' || confirm == 'Y')
            {
                acc->clearTransactions();
                cout << "Transaction history cleared.\n";
            }
            else
            {
                cout << "Cancelled.\n";
            }
            break;
        }
        case 6:
        { // Transfer
            int targetAcc = getIntInput("Transfer to account #: ");
            double amt = getDoubleInput("Amount to transfer: ");
            if (bank.transfer(acc, targetAcc, amt))
                cout << "Transfer successful.\n";
            else
                cout << "Transfer failed.\n";
            break;
        }
        case 7:
        { // Search transactions
            cout << "Enter keyword or date (YYYY-MM-DD): ";
            string query;
            getline(cin, query);
            acc->searchTransactions(query);
            break;
        }
        case 8: // Logout
            cout << "Logging out...\n";
            return;
        default:
            cout << "Invalid choice. Try again.\n";
            break;
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
                cout << "Invalid credentials!\n";
                continue;
            }
            handleAccount(bank, acc);
        }
        else if (choice == 3)
        {
            bank.saveToFile();
            cout << "Exiting program. Goodbye!\n";
            break;
        }
        else
        {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
