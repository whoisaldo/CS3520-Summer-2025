/* 
 * Author:  Ali Younes & Ali Tleis 
 * Course:  CS3520
 * Date:    6/17/2025
 * Assignment 6: Automatic Parking Lot + Object Pool
 */
#include "Customer.hpp"
using namespace std;
Customer::Customer(const string& id, const string& name, 
                  const string& email, CustomerType type)
    : customerId(id), name(name), email(email), type(type) {}

const string& Customer::getId() const {
    return customerId;
}

const string& Customer::getName() const {
    return name;
}

const string& Customer::getEmail() const {
    return email;
}

CustomerType Customer::getType() const {
    return type;
}

void Customer::reset() {
    customerId.clear();
    name.clear();
    email.clear();
    type = CustomerType::REGULAR;
}

// RegularCustomer implementation
RegularCustomer::RegularCustomer(const string& id, const string& name, 
                               const string& email)
    : Customer(id, name, email, CustomerType::REGULAR) {}

double RegularCustomer::getDiscountRate() const {
    return 0.0; // No discount for regular customers
}

// CommuterCustomer implementation
CommuterCustomer::CommuterCustomer(const string& id, const string& name, 
                                 const string& email)
    : Customer(id, name, email, CustomerType::COMMUTER), hasMonthlyPass(false) {}

double CommuterCustomer::getDiscountRate() const {
    return hasMonthlyPass ? 0.20 : 0.10; // 20% with pass, 10% without
}

void CommuterCustomer::setMonthlyPass(bool hasPass) {
    hasMonthlyPass = hasPass;
}

bool CommuterCustomer::getMonthlyPass() const {
    return hasMonthlyPass;
}

// EmployeeCustomer implementation
EmployeeCustomer::EmployeeCustomer(const string& id, const string& name, 
                                 const string& email, const string& empId)
    : Customer(id, name, email, CustomerType::EMPLOYEE), employeeId(empId) {}

double EmployeeCustomer::getDiscountRate() const {
    return 0.50; // 50% discount for employees
}

const string& EmployeeCustomer::getEmployeeId() const {
    return employeeId;
}

