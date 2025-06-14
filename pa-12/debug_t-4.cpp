// Younes.al@northeastern.edu
// Ali Younes 6/13/2025#include <iostream>


// Fixes:
// - Constructor now uses correct type for both parameters (T instead of int)
// - Fixed missing return types in add(), subtract()
// - Rewrote multiply() and divide() to operate on internal members, not parameters
// - Changed divide() to use '/' instead of '%' to support double and string
// - Fixed isgreater() return type (was T, should be bool)
// - Made everything readable and consistent across types

#include <string>
using namespace std;

// Template Calculator class handles basic arithmetic for any type T
template <class T>
class Calculator
{
private:
    T num1;
    T num2;

public:
    Calculator(T n1, T n2); // constructor
    T add();
    T subtract();
    T multiply();
    T divide();
    bool isgreater();
};

// Fixed: second parameter in constructor had wrong type (was int)
template <class T>
Calculator<T>::Calculator(T n1, T n2)
{
    num1 = n1;
    num2 = n2;
}

// Fixed: missing return type
template <class T>
T Calculator<T>::add()
{
    return num1 + num2;
}

// Fixed: missing return type
template <class T>
T Calculator<T>::subtract()
{
    return num1 - num2;
}

// Fixed: removed extra parameters, function now works on class members
template <class T>
T Calculator<T>::multiply()
{
    return num1 * num2;
}

// Fixed: used '%' which is invalid for non-integers, changed to '/'
template <class T>
T Calculator<T>::divide()
{
    return num1 / num2;
}

// Fixed: return type was T instead of bool
template <class T>
bool Calculator<T>::isgreater()
{
    return num1 > num2;
}

int main()
{
    // Test with integers
    Calculator<int> calc(10, 4);
    cout << calc.add() << endl;
    cout << calc.subtract() << endl;
    cout << calc.multiply() << endl;
    cout << calc.divide() << endl;
    cout << boolalpha << calc.isgreater() << endl;

    // Test with doubles
    Calculator<double> calc2(10.234, 4.235);
    cout << calc2.add() << endl;
    cout << calc2.subtract() << endl;
    cout << calc2.multiply() << endl;
    cout << calc2.divide() << endl;
    cout << boolalpha << calc2.isgreater() << endl;

    // Test with strings (concatenation only, rest don’t make sense)
    Calculator<string> calc3("Hello", "World");
    cout << calc3.add() << endl;
    cout << boolalpha << calc3.isgreater() << endl;

    return 0;
}

