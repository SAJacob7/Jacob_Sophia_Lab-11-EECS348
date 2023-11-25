/*
Name: account.cpp
Purpose: Creates Accounts that can transfer, withdraw, and deposit money and can be two types of accounts: Checking or Savings.

The code ...
*/

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;

class Account
{
public:
    // These are the functionalities and methods of the base class Account.
    string accountNumber;
    string accountHolder;
    double balance;
    void deposit(int amount);
    bool withdraw(int amount);
    void displayDetails();
    friend ostream &operator<<(ostream &os, Account &account); // This is the operator overloading of <<.
    double get_Balance();
    // void operator+(Account &);
};
double Account::get_Balance()
{
    return balance;
}
void Account::deposit(int amount)
{
    if (amount >= 0)
    {
        balance = balance + amount; // You can deposite an amount as long as it is not negative, and it will be added to balance.
    }
}
bool Account::withdraw(int amount)
{
    if ((balance - amount) >= 0 && amount >= 0) // When you withdraw an amount, there should be enough to withdraw and the amount should be greater than 0 to withdraw.
    {
        balance = balance - amount; // Then it is subtracted from balance.
        return true;                // Transaction occured so True.
    }
    else
    {
        cout << "Not enought money to withdraw amount." << endl; // Otherwise, False.
        return false;
    }
}
void Account::displayDetails()
{
    cout << *this; // Calls to the overloaded operator for printing the object.
}
ostream &operator<<(ostream &os, Account &account)
{
    // Prints the basic Account details.
    os << "\t"
       << "Holder: " << account.accountHolder << endl;
    os << "\t"
       << "Balance: $" << setprecision(2) << fixed << (account.balance) << endl;
    return os;
}
#endif

class SavingsAccount : public Account
{
    // These are all the functionalities and methods of the derived class SavingsAccount from base class Account.
    double interestRate;

public:
    SavingsAccount(string id, string name, double balance1, double interest)
    {
        accountNumber = id;
        accountHolder = name;
        balance = balance1;
        interestRate = interest;
    }
    bool withdraw(int amount);
    SavingsAccount operator+(Account &other); // This is the overloaded operator + to have a transfer of money.
    void displayDetails();
};

bool SavingsAccount::withdraw(int amount)
{
    double min_balance = 10;                              // The minimum balance is 10 dollars.
    if ((balance - amount) >= min_balance && amount >= 0) // They should only be able to withdraw if the balance will be at or above min_balance and the amount greater than 0.
    {
        balance = balance - amount; // If so, then subtract from balance.
        return true;                // Transaction occured so True.
    }
    else
    {
        cout << "Not enought money to withdraw amount for min balance of $" << min_balance << "." << endl; // Otherwise, False.
        return false;
    }
}

void SavingsAccount::displayDetails()
{
    // Prints specfic details of SavingsAccount.
    cout << "Account Details for Savings Account (ID: " << accountNumber << ")" << endl;
    cout << *this; // Calls to the overloaded operator << to print the details of the Account.
    double interest = interestRate * 100.00;
    cout << "\t"
         << "Interest Rate: " << setprecision(2) << fixed << interest << "%" << endl;
    cout << endl;
}
SavingsAccount SavingsAccount::operator+(Account &other)
{
    // As per the requirements on the Assignment, we must transfer $300 from one account to the other.
    // We are transfering from the paremeter other to the SavingsAccount.
    if (other.withdraw(300) == true) // We can only transfer if a withdrawal of the other account can occur.
    {
        balance += 300; // Then this balance gets updated to $300 more.
        return *this;
    }
    else
    {
        return *this;
    }

    /*
    if (other.balance >= 300) // The minimum the other balance has to be to ensure it can clear the transaction (no matter the overdraft fee) is $300 because we are transfering $300.
    {
        balance += 300;
        other.balance -= 300;
        return (*this);
    }
    else
    {
        return (*this);
    }
    */
}

class CurrentAccount : public Account
{
    // These are all the functionalities and methods of the derived class SavingsAccount from base class Account.
    double overdraftLimit;

public:
    CurrentAccount(string id, string name, double balance1, double limit)
    {
        accountNumber = id;
        accountHolder = name;
        balance = balance1;
        overdraftLimit = limit;
    }
    bool withdraw(int amount);
    void displayDetails();
    CurrentAccount operator+(Account &); // This is the overloaded operator + to have a transfer of money.
};
bool CurrentAccount::withdraw(int amount)
{
    // We can withdraw only if the balance will be greater than or equal to negative overdraft limit,
    // since we are allowed to take money even if our balance is below 0, as long as its above the overdraft. Amount must be positive/0 too.
    if ((balance - amount) >= -overdraftLimit && amount >= 0)
    {
        balance = balance - amount; // Take away amout from balance.
        return true;                // Transaction occured so True.
    }
    else
    {
        cout << "Amount you are trying to withdraw exceeds overdraft Limit of $" << overdraftLimit << "." << endl; // Otherwise it is False.
        return false;
    }
}

void CurrentAccount::displayDetails()
{
    // Prints specific details of CurrentAccount.
    cout << "Account Details for Current Account (ID: " << accountNumber << ")" << endl;
    cout << *this; // Calls to overloaded operator to print Account details.
    cout << "\t"
         << "Overdraft Limit: $" << overdraftLimit << endl;
    cout << endl;
}

CurrentAccount CurrentAccount::operator+(Account &other)
{
    // Overloaded + function.
    // As per the requirements on the Assignment, we must transfer $300 from one account to the other.
    // We are transfering from the paremeter other to the SavingsAccount.
    if (other.withdraw(300) == true) // Only allows for transfering of money if a withdrawal of other account occurs.
    {
        balance += 300; // Update the balance of the Account money is transfered to.
        return *this;
    }
    else
    {
        return *this;
    }

    /*
    if (other.balance >= 300) // We can only allow a transfer of $300 if the other account has at least $300 to give.
    {
        balance += 300;       // Transfering from other account to this (Current) account, so add 300 here.
        other.balance -= 300; // Taking away 300 from other account to transfer to this account, so subtract 300.
        return *this;
    }
    else
    {
        return *this;
    }
    */
}
int main()
{
    // Examples showing transactions, depositing, withdrawal, and displaying Details.
    SavingsAccount savings("S123", "John Doe", 1000, 0.02);
    CurrentAccount current("C456", "Jane Doe", 2000, 500);
    savings.displayDetails();
    current.displayDetails();
    savings.deposit(500);
    current.withdraw(1000);
    cout << "Account Details after Deposit and Withdrawal: " << endl;
    savings.displayDetails();
    current.displayDetails();
    current = current + savings;
    cout << "Account Details after transfer: " << endl;
    savings.displayDetails();
    current.displayDetails();
    return 0;
}