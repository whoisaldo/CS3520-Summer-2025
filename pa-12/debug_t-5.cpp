// Younes.al@northeastern.edu
// Ali Younes 6/13/2025
// Fixes:
// - Fixed object slicing by using references everywhere (especially in printCarInfo)
// - Made all print() and operator= functions virtual for polymorphism
// - Added virtual destructor in base class (good practice)
// - Fixed suv constructor: now properly calls base class constructor
// - In suv::operator=, used dynamic_cast to check safe assignment
// - Moved all common assignment logic to protected assign() helper
// - Cleaned up formatting and fixed all hidden access issues
#include <iostream>
#include <string>
using namespace std;

class car
{
protected:
    string name;
    int modelYear;

    void assign(const car &c)
    {
        name = c.name;
        modelYear = c.modelYear;
    }

public:
    car(const string &n, int y) : name(n), modelYear(y) {}

    // virtual print for polymorphism
    virtual void print() const
    {
        cout << "Name: " << name << " model Year: " << modelYear << endl;
    }

    virtual const car &operator=(const car &c)
    {
        if (this != &c)
        {
            name = c.name;
            modelYear = c.modelYear;
        }
        return *this;
    }

    virtual ~car() {} // always virtual for base classes
};

class sedan : public car
{
private:
    int mileage;

public:
    sedan(const string &n, int y, int m) : car(n, y), mileage(m) {}

    void print() const override
    {
        cout << "Name: " << name << " model Year: " << modelYear << " Mileage: " << mileage << endl;
    }
};

class suv : public car
{
private:
    int miles;

public:
    suv(const string &n, int y, int m) : car(n, y), miles(m) {}

    void print() const override
    {
        cout << "Name: " << name << " model Year: " << modelYear << " Miles driven: " << miles << endl;
    }

    const suv &operator=(const car &c) override
    {
        if (this != &c)
        {
            if (const suv *s = dynamic_cast<const suv *>(&c))
            {
                assign(*s);
            }
        }
        return *this;
    }

protected:
    void assign(const suv &s)
    {
        car::assign(s);
        miles = s.miles;
    }
};

// Fixed: pass by reference to preserve polymorphism
void printCarInfo(const car &c)
{
    c.print();
}

int main()
{
    car tesla("tesla", 2019);
    sedan hyundai("Hyundai", 2020, 23);
    suv ford("Ford", 2012, 20000);

    printCarInfo(tesla);   // base
    printCarInfo(hyundai); // derived
    printCarInfo(ford);    // derived

    car &ref = ford;
    suv ford2("Ford", 2017, 10000);
    ref = ford2;           // no slicing thanks to virtual operator=
    printCarInfo(ref);     // still prints suv info

    return 0;
}

