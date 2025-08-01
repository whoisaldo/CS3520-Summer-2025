#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
using namespace std;
enum class CustomerType {
    REGULAR,
    COMMUTER,
    EMPLOYEE
};

class Customer {
protected:
    string customerId;
    string name;
    string email;
    CustomerType type;

public:
    Customer(const string& id, const string& name, 
             const string& email, CustomerType type);
    virtual ~Customer() = default;
    
    const string& getId() const;
    const string& getName() const;
    const string& getEmail() const;
    CustomerType getType() const;
    
    virtual double getDiscountRate() const = 0;
    virtual void reset(); // For object pool
};

class RegularCustomer : public Customer {
public:
    RegularCustomer(const string& id = "", const string& name = "", 
                   const string& email = "");
    double getDiscountRate() const override;
};

class CommuterCustomer : public Customer {
private:
    bool hasMonthlyPass;

public:
    CommuterCustomer(const string& id = "", const string& name = "", 
                    const string& email = "");
    double getDiscountRate() const override;
    void setMonthlyPass(bool hasPass);
    bool getMonthlyPass() const;
};

class EmployeeCustomer : public Customer {
private:
    string employeeId;

public:
    EmployeeCustomer(const string& id = "", const string& name = "", 
                    const string& email = "", const string& empId = "");
    double getDiscountRate() const override;
    const string& getEmployeeId() const;
};

#endif // CUSTOMER_H
