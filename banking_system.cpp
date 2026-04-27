#include <iostream>
using namespace std;

// Base Class
class BankAccount {
protected:
    int accountNumber;
    string accountHolderName;
    double balance;

public:
    BankAccount(int accNo, string name, double bal) {
        accountNumber = accNo;
        accountHolderName = name;
        balance = bal;
    }

    void deposit(double amount) {
        balance += amount;
        cout << "Deposited: " << amount << endl;
    }

    virtual void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            cout << "Withdrawn: " << amount << endl;
        } else {
            cout << "Insufficient Balance!" << endl;
        }
    }

    double getBalance() {
        return balance;
    }

    virtual void displayAccountInfo() {
        cout << "\n--- Account Info ---\n";
        cout << "Account No: " << accountNumber << endl;
        cout << "Name: " << accountHolderName << endl;
        cout << "Balance: " << balance << endl;
    }

    // Polymorphism
    virtual void calculateInterest() {
        cout << "No interest for this account\n";
    }
};

// Savings Account
class SavingsAccount : public BankAccount {
    double interestRate;

public:
    SavingsAccount(int accNo, string name, double bal, double rate)
        : BankAccount(accNo, name, bal) {
        interestRate = rate;
    }

    void calculateInterest() override {
        double interest = balance * interestRate / 100;
        cout << "Savings Interest: " << interest << endl;
    }
};

// Checking Account
class CheckingAccount : public BankAccount {
    double overdraftLimit;

public:
    CheckingAccount(int accNo, string name, double bal, double limit)
        : BankAccount(accNo, name, bal) {
        overdraftLimit = limit;
    }

    void withdraw(double amount) override {
        if (amount <= balance + overdraftLimit) {
            balance -= amount;
            cout << "Withdrawn (with overdraft): " << amount << endl;
        } else {
            cout << "Overdraft limit exceeded!" << endl;
        }
    }
};

// Fixed Deposit Account
class FixedDepositAccount : public BankAccount {
    int term; // in months

public:
    FixedDepositAccount(int accNo, string name, double bal, int t)
        : BankAccount(accNo, name, bal) {
        term = t;
    }

    void calculateInterest() override {
        double interest = balance * 0.07 * term / 12;
        cout << "Fixed Deposit Interest: " << interest << endl;
    }
};

// Main Function (Menu Driven)
int main() {
    SavingsAccount s(101, "Neev", 10000, 5);
    CheckingAccount c(102, "Raj", 5000, 2000);
    FixedDepositAccount f(103, "Amit", 20000, 12);

    BankAccount* acc = NULL;
    int choice, op;

    do {
        cout << "\n====== BANK MENU ======\n";
        cout << "1. Savings Account\n";
        cout << "2. Checking Account\n";
        cout << "3. Fixed Deposit Account\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: acc = &s; break;
            case 2: acc = &c; break;
            case 3: acc = &f; break;
            case 4: cout << "Thank you!\n"; return 0;
            default: cout << "Invalid choice\n"; continue;
        }

        cout << "\n1. Deposit\n";
        cout << "2. Withdraw\n";
        cout << "3. Show Info\n";
        cout << "4. Calculate Interest\n";
        cout << "Enter option: ";
        cin >> op;

        switch (op) {
            case 1: {
                double amt;
                cout << "Enter amount: ";
                cin >> amt;
                acc->deposit(amt);
                break;
            }
            case 2: {
                double amt;
                cout << "Enter amount: ";
                cin >> amt;
                acc->withdraw(amt);
                break;
            }
            case 3:
                acc->displayAccountInfo();
                break;

            case 4:
                acc->calculateInterest(); // polymorphism
                break;

            default:
                cout << "Invalid option\n";
        }

    } while (true);

    return 0;
}