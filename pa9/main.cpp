// Younes.al@northeastern.edu
// Ali Younes 6/3/2025
// CS3520 course

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Employee class represents an employee with name, email, and role
class Employee {
private:
    string name;
    string email;
    string role;
public:
    // default constructor
    Employee() : name(""), email(""), role("") {}

    // parameterized constructor
    Employee(const string& name, const string& email, const string& role)
        : name(name), email(email), role(role) {}

    // getters
    string getName() const { return name; }
    string getEmail() const { return email; }
    string getRole() const { return role; }

    // setters
    void setName(const string& n) { name = n; }
    void setEmail(const string& e) { email = e; }
    void setRole(const string& r) { role = r; }

    // overload << to print an employee
    friend ostream& operator<<(ostream& os, const Employee& e) {
        os << "Name: " << e.name << ", Email: " << e.email << ", Role: " << e.role;
        return os;
    }

    // overload >> to read an employee from input
    friend istream& operator>>(istream& is, Employee& e) {
        cout << "Enter employee name: ";
        getline(is, e.name);
        cout << "Enter employee email: ";
        getline(is, e.email);
        cout << "Enter employee role: ";
        getline(is, e.role);
        return is;
    }
};

// Group class represents a group with identifier, name, area, and list of employees
class Group {
private:
    string groupId;
    string groupName;
    string areaOfResponsibility;
    vector<Employee> employees;

public:
    // default constructor
    Group() : groupId(""), groupName(""), areaOfResponsibility("") {}

    // parameterized constructor
    Group(const string& id, const string& name, const string& area)
        : groupId(id), groupName(name), areaOfResponsibility(area) {}

    // getters
    string getId() const { return groupId; }
    string getName() const { return groupName; }
    string getArea() const { return areaOfResponsibility; }
    vector<Employee> getEmployees() const { return employees; }

    // setters
    void setId(const string& id) { groupId = id; }
    void setName(const string& name) { groupName = name; }
    void setArea(const string& area) { areaOfResponsibility = area; }

    // add an employee to the group
    void addEmployee(const Employee& e) {
        employees.push_back(e);
    }

    // overload - operator to remove x employees from the group (remove last x)
    Group operator-(int x) const {
        Group result = *this;
        if (x >= static_cast<int>(result.employees.size())) {
            result.employees.clear();
        } else {
            for (int i = 0; i < x; ++i) {
                result.employees.pop_back();
            }
        }
        return result;
    }

    // overload + operator to merge two groups into a new group
    friend Group operator+(const Group& g1, const Group& g2) {
        string newId = g1.groupId + "_" + g2.groupId;
        string newName = g1.groupName + " & " + g2.groupName;
        string newArea = g1.areaOfResponsibility + " & " + g2.areaOfResponsibility;
        Group merged(newId, newName, newArea);
        // copy employees from first group
        for (const auto& e : g1.employees) {
            merged.employees.push_back(e);
        }
        // copy employees from second group
        for (const auto& e : g2.employees) {
            merged.employees.push_back(e);
        }
        return merged;
    }

    // overload << to print group details
    friend ostream& operator<<(ostream& os, const Group& g) {
        os << "Group ID: " << g.groupId << "\n";
        os << "Group Name: " << g.groupName << "\n";
        os << "Area: " << g.areaOfResponsibility << "\n";
        os << "Employees (" << g.employees.size() << "):\n";
        for (const auto& e : g.employees) {
            os << "  - " << e << "\n";
        }
        return os;
    }

    // overload >> to read group details and employees
    friend istream& operator>>(istream& is, Group& g) {
        cout << "Enter group ID: ";
        getline(is, g.groupId);
        cout << "Enter group name: ";
        getline(is, g.groupName);
        cout << "Enter area of responsibility: ";
        getline(is, g.areaOfResponsibility);
        int count = 0;
        cout << "Enter number of employees: ";
        is >> count;
        is.ignore(numeric_limits<streamsize>::max(), '\n');
        g.employees.clear();
        for (int i = 0; i < count; ++i) {
            cout << "Entering details for employee " << (i + 1) << ":\n";
            Employee e;
            is >> e;
            is.ignore(numeric_limits<streamsize>::max(), '\n');
            g.employees.push_back(e);
        }
        return is;
    }
};

int main() {
    // create first group with emplyes)
    Group g1("101", "SalesTeam", "Sales");
    g1.addEmployee(Employee("Ali Younes", "ali.younes@company.com", "SalesRep"));
    g1.addEmployee(Employee("Ali Tleis",  "ali.tleis@company.com",  "SalesRep"));
    g1.addEmployee(Employee("Adam Younes","adam.younes@company.com", "TeamLead"));

    // create second group with employees (example names—these can be anything)
    Group g2("202", "MarketingTeam", "Marketing");
    g2.addEmployee(Employee("Eve Martinez", "eve@company.com", "Marketer"));
    g2.addEmployee(Employee("Frank Gordon","frank@company.com","SEO Specialist"));

    // print initial groups
    cout << "Initial Group 1:\n" << g1 << "\n";
    cout << "Initial Group 2:\n" << g2 << "\n";

    // test - operator: remove 2 employees from group1
    Group g1Fired = g1 - 2;
    cout << "Group 1 after firing 2 employees:\n" << g1Fired << "\n";

    // test + operator: merge group1 and group2 into a new group
    Group merged = g1 + g2;
    cout << "Merged Group:\n" << merged << "\n";

    // test >> operator: read a new group from user
    Group g3;
    cout << "Create a new group by entering details:\n";
    cin >> g3;
    cout << "You entered:\n" << g3 << "\n";

    return 0;
}

