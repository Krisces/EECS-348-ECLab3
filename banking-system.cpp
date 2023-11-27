#include <iostream>
#include <iomanip>
#include <string>

class Account {
protected:
    std::string accountNumber;
    std::string accountHolder;
    double balance;

public:
    Account(const std::string& number, const std::string& holder, double initialBalance)
        : accountNumber(number), accountHolder(holder), balance(initialBalance) {}

    virtual void displayDetails() const {
        std::cout << "Account Details for Account (ID: " << accountNumber << "):\n"
            << "   Holder: " << accountHolder << "\n"
            << "   Balance: $" << std::fixed << std::setprecision(2) << balance << "\n\n";
    }

    void deposit(double amount) {
        balance += amount;
    }

    virtual void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
        }
    }

    double getBalance() const {
        return balance;
    }
};

class SavingsAccount : public Account {
private:
    double interestRate;

public:
    SavingsAccount(const std::string& number, const std::string& holder, double initialBalance, double rate)
        : Account(number, holder, initialBalance), interestRate(rate) {}

    void displayDetails() const override {
        std::cout << "Account Details for Savings Account (ID: " << accountNumber << "):\n"
            << "   Holder: " << accountHolder << "\n"
            << "   Balance: $" << std::fixed << std::setprecision(2) << balance << "\n"
            << "   Interest Rate: " << std::fixed << std::setprecision(2) << interestRate * 100 << "%\n\n";
    }

    void withdraw(double amount) override {
        const double minBalance = 100;  // Minimum balance for savings account
        if (balance - amount >= minBalance) {
            balance -= amount;
        }
    }
};

class CurrentAccount : public Account {
private:
    double overdraftLimit;

public:
    CurrentAccount(const std::string& number, const std::string& holder, double initialBalance, double limit)
        : Account(number, holder, initialBalance), overdraftLimit(limit) {}

    void displayDetails() const override {
        std::cout << "Account Details for Current Account (ID: " << accountNumber << "):\n"
            << "   Holder: " << accountHolder << "\n"
            << "   Balance: $" << std::fixed << std::setprecision(2) << balance << "\n"
            << "   Overdraft Limit: $" << std::fixed << std::setprecision(2) << overdraftLimit << "\n\n";
    }

    void withdraw(double amount) override {
        if (balance + overdraftLimit >= amount) {
            balance -= amount;
        }
    }
};

// Operator Overloading
CurrentAccount operator+(CurrentAccount& current, SavingsAccount& savings) {
    double transferAmount = 300;

    if (savings.getBalance() >= transferAmount) {
        current.deposit(transferAmount);
        savings.withdraw(transferAmount);
    }

    return current;
}

int main() {
    SavingsAccount savings("S123", "John Doe", 1000, 0.02);
    CurrentAccount current("C456", "Jane Doe", 2000, 500);

    std::cout << std::fixed << std::setprecision(2);

    savings.displayDetails();
    current.displayDetails();

    savings.deposit(500);
    current.withdraw(1000);

    std::cout << "\nAccount Details after deposit and withdrawal:\n";
    savings.displayDetails();
    current.displayDetails();

    // Transfer 300 from savings to current
    current = current + savings;

    std::cout << "\nAccount Details after transfer:\n";
    savings.displayDetails();
    current.displayDetails();

    return 0;
}
