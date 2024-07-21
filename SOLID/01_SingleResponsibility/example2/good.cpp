#include <iostream>
#include <string>

class Employee {
public:
    Employee(const std::string& name, double salary)
        : m_name{name}, m_salary{salary} {}

    // Responsibility 1: Store employee details
    std::string getName() const { return m_name; }
    double getSalary() const { return m_salary; }

private:
    std::string m_name {"Unknown"};
    double m_salary {0.0};
};

class Payroll
{
public:
    // Responsibility 2: Calculate pay
    double calculatePay(const Employee& employee) const {
        const double pfDeduction = (employee.getSalary() * 0.12);
        return {employee.getSalary() - pfDeduction};
    }

};

class EmployeePrinter
{
public:
    // Responsibility 3: Print details
    void printDetails(const Employee& employee) const {
        Payroll payroll;
        const auto salaryAfterDeduction = payroll.calculatePay(employee);
        std::cout << "------------------------------------\n";
        std::cout << "Employee Name: " << employee.getName() << std::endl;
        std::cout << "Employee Salary: Rs." << employee.getSalary() << "/-" << std::endl;

        // Below flexibility comes when we break the classes
        std::cout << "Employee Salary after deduction: Rs." << salaryAfterDeduction << "/-" << std::endl;
        std::cout << "------------------------------------\n";
    }
};

int main()
{
    EmployeePrinter ep;
    Payroll pr;
    Employee e {"Bhavith", 40000};
    std::cout << "Pay after deduction: " << pr.calculatePay(e) << "\n\n";
    ep.printDetails(e);
    return 0;
}