#include <iostream>
#include <string>
using namespace std;

// Template Calculator class to perform arithmetic operations on two values of type T
template <class T>
class Calculator
{
private:
    T num1;
    T num2;

public:
    Calculator(T n1, T n2);  // constructor
    T add();                 // addition
    T subtract();            // subtraction
    T multiply();            // multiplication
    T divide();              // division
    bool isgreater();        // compare which is greater
};

// Fixed: constructor now takes two values of type T (was T and int)
template <class T>
Calculator<T>::Calculator(T n1, T n2)
{
    num1 = n1;
    num2 = n2;
}

// Fixed: return type was missing for add()
template <class T>
T Calculator<T>::add()
{
    return num1 + num2;
}

// Fixed: return type was missing for subtract()
template <class T>
T Calculator<T>::subtract()
{
    return num1 - num2;
}

// Fixed: removed unnecessary parameters, now uses class members
template <class T>
T Calculator<T>::multiply()
{
    return num1 * num2;
}

// Fixed: division was using %, which only works for int
template <class T>
T Calculator<T>::divide()
{
    return num1 / num2;
}

// Fixed: return type should be bool, not T
template <class T>
bool Calculator<T>::isgreater()
{
    return num1 > num2;
}

int main()
{
    // Integer operations
    Calculator<int> calc(10, 4);
    cout << calc.add() << endl;
    cout << calc.subtract() << endl;
    cout << calc.multiply() << endl;
    cout << calc.divide() << endl;
    cout << boolalpha << calc.isgreater() << endl;

    // Double operations
    Calculator<double> calc2(10.234, 4.235);
    cout << calc2.add() << endl;
    cout << calc2.subtract() << endl;
    cout << calc2.multiply() << endl;
    cout << calc2.divide() << endl;
    cout << boolalpha << calc2.isgreater() << endl;

    // String operations (only add and isgreater make sense)
    Calculator<string> calc3("Hello", "World");
    cout << calc3.add() << endl;
    cout << boolalpha << calc3.isgreater() << endl;

    return 0;
}
