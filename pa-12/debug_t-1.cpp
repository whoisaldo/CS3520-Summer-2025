#include <iostream>
#include <string>
using namespace std;

// Fixed: Second parameter of template function had missing type
// Fixed: Removed incorrect 'U sum;' (undefined type). Replaced with T sum.
template <class T>
T add(T x, T y)
{
    T sum = x + y;
    return sum;
}

class Person
{
    // Fixed: Made output stream accept const Person&
    friend ostream &operator<<(ostream &, const Person &);

private:
    string lastName;
    string firstName;
    int age;

public:
    void setValues(string, string, int);
    Person operator+(const Person &) const; // Fixed: Marked parameter const, and function as const
};

// Fixed: Added 'const' to match friend declaration
// Fixed: Added return statement for ostream
ostream &operator<<(ostream &out, const Person &per)
{
    out << per.firstName << " " << per.lastName << " " << per.age << " years old";
    return out;
}

// Fixed: Renamed input variable from 'age' to 'a' to avoid shadowing
void Person::setValues(string last, string first, int a)
{
    lastName = last;
    firstName = first;
    age = a;
}

// Fixed: Logic corrected to compute sum of ages and store it in new Person
Person Person::operator+(const Person &p) const
{
    Person temp;
    temp.firstName = "Sum";
    temp.lastName = "of Age";
    temp.age = this->age + p.age; // Fixed: was assigning to own age
    return temp;
}

int main()
{
    cout << "Start!" << endl;

    int a = 7, b = 26, c;
    double d = 39.25, e = 2.01, f;
    Person g, h, i;

    g.setValues("Mitchell", "Donald", 40);
    h.setValues("Clayton", "Rita", 35);

    c = add(a, b);   // Should print 33
    f = add(d, e);   // Should print 41.26
    i = add(g, h);   // Should print: Sum of Age 75 years old

    cout << c << endl;
    cout << f << endl;
    cout << i << endl;

    cout << "Bye" << endl;
    return 0;
}

