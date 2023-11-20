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
    string accountNumber;
    string accountHolder;
    double balance;
    void deposit(int amount);
    void withdraw(int amount);
    void displayDetails();
    friend ostream &operator<<(ostream &os, Account &account);
    // void operator+(Account &);
};
void Account::deposit(int amount)
{
    balance = balance + amount;
}
void Account::withdraw(int amount)
{
    if ((balance - amount) >= 0 && amount >= 0)
    {
        balance = balance - amount;
    }
    else
    {
        cout << "Not enought money to withdraw amount." << endl;
    }
}
void Account::displayDetails()
{
    cout << *this;
}
ostream &operator<<(ostream &os, Account &account)
{
    os << "\t"
       << "Holder: " << account.accountHolder << endl;
    os << "\t"
       << "Balance: $" << setprecision(2) << fixed << (account.balance) << endl;
    return os;
}
#endif

class SavingsAccount : public Account
{
protected:
    double interestRate;

public:
    SavingsAccount(string id, string name, double balance1, double interest)
    {
        accountNumber = id;
        accountHolder = name;
        balance = balance1;
        interestRate = interest;
    }
    void withdraw(int amount);
    SavingsAccount operator+(Account &other);
    void displayDetails();
};

void SavingsAccount::withdraw(int amount)
{
    double min_balance = 0;
    if ((balance - amount) >= min_balance && amount >= 0)
    {
        balance = balance - amount;
    }
    else
    {
        cout << "Not enought money to withdraw amount for min balance of $" << min_balance << "." << endl;
    }
}

void SavingsAccount::displayDetails()
{
    cout << "Account Details for Savings Account (ID: " << accountNumber << ")" << endl;
    cout << *this;
    double interest = interestRate * 100.00;
    cout << "\t"
         << "Interest Rate: " << setprecision(2) << fixed << interest << "%" << endl;
    cout << endl;
}
SavingsAccount SavingsAccount::operator+(Account &other)
{
    if (other.balance >= -200) // The minimum the other balance has to be to ensure it does not go over its overdraft limit is -200 because we are transfering $300.
    {
        balance += 300;
        other.balance -= 300;
        return (*this);
    }
    else
    {
        return (*this);
    }
}

class CurrentAccount : public Account
{
protected:
    double overdraftLimit;

public:
    CurrentAccount(string id, string name, double balance1, double limit)
    {
        accountNumber = id;
        accountHolder = name;
        balance = balance1;
        overdraftLimit = limit;
    }
    void withdraw(int amount);
    void displayDetails();
    CurrentAccount operator+(Account &);
};
void CurrentAccount::withdraw(int amount)
{
    if ((balance - amount) >= -overdraftLimit && amount >= 0)
    {
        balance = balance - amount;
    }
    else
    {
        cout << "Amount you are trying to withdraw exceeds overdraft Limit of $" << overdraftLimit << "." << endl;
    }
}

void CurrentAccount::displayDetails()
{
    cout << "Account Details for Current Account (ID: " << accountNumber << ")" << endl;
    cout << *this;
    cout << "\t"
         << "Overdraft Limit: $" << overdraftLimit << endl;
    cout << endl;
}

CurrentAccount CurrentAccount::operator+(Account &other)
{
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
}
int main()
{
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