#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// Expense class (abstract base class)
class Expense
{
protected:
    double amount;
    string description;

public:
    Expense(double amount, const string &description) : amount(amount), description(description) {}

    virtual void display() = 0; // pure virtual function

    // Getters and setters
    double getAmount() const { return amount; }
    string getDescription() const { return description; }
};

// Income class (derived from Expense)
class Income : public Expense
{
public:
    Income(double amount, const string &description) : Expense(amount, description) {}

    // Display function implementation
    void display()
    {
        cout << "Income: +" << amount << " (" << description << ")" << endl;
    }
};

// Expense class (derived from Expense)
class ExpenseItem : public Expense
{
public:
    ExpenseItem(double amount, const string &description) : Expense(amount, description) {}

    // Display function implementation
    void display()
    {
        cout << "Expense: -" << amount << " (" << description << ")" << endl;
    }
};

// Expense manager class
class ExpenseManager
{
private:
    vector<Expense *> expenses; // vector to store expenses
    double balance = 0;         // current balance

public:
    // Function to add income
    void addIncome(double amount, const string &description)
    {
        Expense *income = new Income(amount, description);
        expenses.push_back(income);
        balance += amount;
        cout << "Income added successfully!" << endl;
    }

    // Function to add expense
    void addExpense(double amount, const string &description)
    {
        if (amount <= balance)
        {
            Expense *expense = new ExpenseItem(amount, description);
            expenses.push_back(expense);
            balance -= amount;
            cout << "Expense added successfully!" << endl;
        }
        else
        {
            cout << "Insufficient balance to add expense!" << endl;
        }
    }

    // Function to display all expenses
    void displayExpenses()
    {
        if (expenses.empty())
        {
            cout << "No expenses to display!" << endl;
        }
        else
        {
            for (const auto &expense : expenses)
            {
                expense->display();
            }
        }

        cout << "Current balance: " << balance << endl;
    }

    // Function to save expenses to file
    void saveExpensesToFile(const string &filename)
    {
        ofstream file(filename);

        if (!file.is_open())
        {
            cout << "Error opening file!" << endl;
        }
        else
        {
            for (const auto &expense : expenses)
            {
                file << expense->getAmount() << "," << expense->getDescription() << endl;
            }

            cout << "Expenses saved to file!" << endl;
        }

        file.close();
    }
};

// Main function
int main()
{
    ExpenseManager expenseManager;
    int choice;

    do
    {
        cout << "\nExpense Management System Menu" << endl;
        cout << "1. Add income" << endl;
        cout << "2. Add expense" << endl;
        cout << "3. Display expenses" << endl;
        cout << "4. Save expenses to file" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            double amount;
            string description;

            cout << "Enter amount: ";
            cin >> amount;

            cout << "Enter description: ";
            cin.ignore(); // ignore newline character from previous input
            getline(cin, description);

            expenseManager.addIncome(amount, description);
            break;
        }
        case 2:
        {
            double amount;
            string description;

            cout << "Enter amount: ";
            cin >> amount;

            cout << "Enter description: ";
            cin.ignore(); // ignore newline character from previous input
            getline(cin, description);

            expenseManager.addExpense(amount, description);
            break;
        }
        case 3:
        {
            expenseManager.displayExpenses();
            break;
        }
        case 4:
        {
            string filename;

            cout << "Enter filename: ";
            cin >> filename;

            expenseManager.saveExpensesToFile(filename);
            break;
        }
        case 5:
        {
            cout << "Exiting expense management system..." << endl;
            break;
        }
        default:
        {
            cout << "Invalid choice! Please try again." << endl;
            break;
        }
        }
    } while (choice != 5);

    return 0;
}
