#include <iostream>
#include <string>

class Employee {
public:
    Employee(const std::string& name, double salary)
        : m_name{name}, m_salary{salary} {}

    // Responsibility 1: Store employee details
    std::string getName() const { return m_name; }
    double getSalary() const { return m_salary; }

    // Responsibility 2: Calculate pay
    double calculatePay() const {
        const double pfDeduction = (m_salary * 0.12);
        return {m_salary - pfDeduction};
    }

    // Responsibility 3: Print details
    void printDetails() const {
        std::cout << "Employee Name: " << m_name << std::endl;
        std::cout << "Employee Salary: Rs." << m_salary << "/-" << std::endl;
    }

private:
    std::string m_name {"Unknown"};
    double m_salary {0.0};
};

int main()
{
    Employee e {"Bhavith", 40000};
    std::cout << "Name: " << e.getName() << "\n";
    std::cout << "Salary: " << e.getSalary() << "\n";
    std::cout << "Pay after deduction: " << e.calculatePay() << "\n\n";
    std::cout << "Employee info\n";
    std::cout << "---------------\n";
    e.printDetails();
    std::cout << "---------------\n";
    return 0;
}