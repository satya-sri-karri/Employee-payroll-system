#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
using namespace std;

class Employee {
protected:
    int id;
    string name;

public:
    Employee(int id, const string& name) : id(id), name(name) {}

    virtual double calculateSalary() const = 0;

    virtual void display() const {
        cout << "ID: " << id << "\nName: " << name << endl;
    }

    int getId() const { return id; }

    virtual ~Employee() = default;
};

class FullTimeEmployee : public Employee {
private:
    double monthlySalary;

public:
    FullTimeEmployee(int id, const string& name, double salary)
        : Employee(id, name), monthlySalary(salary) {}

    double calculateSalary() const override {
        return monthlySalary;
    }

    void display() const override {
        Employee::display();
        cout << "Type: Full-Time\nSalary: ?" << calculateSalary() << endl;
    }
};

class PartTimeEmployee : public Employee {
private:
    int hoursWorked;
    double hourlyRate;

public:
    PartTimeEmployee(int id, const string& name, int hours, double rate)
        : Employee(id, name), hoursWorked(hours), hourlyRate(rate) {}

    double calculateSalary() const override {
        return hoursWorked * hourlyRate;
    }

    void display() const override {
        Employee::display();
        cout << "Type: Part-Time\nSalary: ?" << calculateSalary() << endl;
    }
};

class PayrollSystem {
private:
    vector<unique_ptr<Employee>> employees;

public:
    void addFullTimeEmployee() {
        int id;
        string name;
        double salary;

        cout << "Enter ID: ";
        cin >> id;
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Monthly Salary: ";
        cin >> salary;

        employees.push_back(make_unique<FullTimeEmployee>(id, name, salary));
        cout << "Full-Time Employee Added!\n";
    }

    void addPartTimeEmployee() {
        int id, hours;
        string name;
        double rate;

        cout << "Enter ID: ";
        cin >> id;
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Hours Worked: ";
        cin >> hours;
        cout << "Enter Hourly Rate: ";
        cin >> rate;

        employees.push_back(make_unique<PartTimeEmployee>(id, name, hours, rate));
        cout << "Part-Time Employee Added!\n";
    }

    void displayAll() const {
        if (employees.empty()) {
            cout << "No employees found.\n";
            return;
        }

        for (const auto& emp : employees) {
            emp->display();
            cout << "-------------------\n";
        }
    }

    void searchById() const {
        int id;
        cout << "Enter Employee ID to search: ";
        cin >> id;

        for (const auto& emp : employees) {
            if (emp->getId() == id) {
                emp->display();
                return;
            }
        }
        cout << "Employee not found!\n";
    }

    void deleteById() {
        int id;
        cout << "Enter Employee ID to delete: ";
        cin >> id;

        auto it = remove_if(employees.begin(), employees.end(),
            [id](const unique_ptr<Employee>& emp) {
                return emp->getId() == id;
            });

        if (it != employees.end()) {
            employees.erase(it, employees.end());
            cout << "Employee deleted successfully!\n";
        } else {
            cout << "Employee not found!\n";
        }
    }
};


int main() {
    PayrollSystem system;
    int choice;

    do {
        cout << "\n--- Employee Payroll System ---\n";
        cout << "1. Add Full-Time Employee\n";
        cout << "2. Add Part-Time Employee\n";
        cout << "3. Display All Employees\n";
        cout << "4. Search Employee by ID\n";
        cout << "5. Delete Employee by ID\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: system.addFullTimeEmployee(); break;
            case 2: system.addPartTimeEmployee(); break;
            case 3: system.displayAll(); break;
            case 4: system.searchById(); break;
            case 5: system.deleteById(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 6);

    return 0;
}
