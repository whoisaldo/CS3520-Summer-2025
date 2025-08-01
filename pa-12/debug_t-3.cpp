// Younes.al@northeastern.edu
// Ali Younes 6/13/2025
// Fixes:
// - Fixed CommaSeparatedList constructor to take T* not T
// - Fixed syntax in printList: wrong brackets, wrong operators, bad variable use
// - printList now prints items correctly with commas between them
// - Fixed typo: 'prinList()' → 'printList()'
// - Fixed typo: 'sizeif' → 'sizeof'
// - Fixed Book and Customer output functions to return correctly and print nicely
// - Made variable names and structure a lot more readable
#include <iostream>
#include <string>
using namespace std;

// Template class that stores and prints a list of items separated by commas
template <class T>
class CommaSeparatedList
{
private:
    T *data;
    int size;

public:
    CommaSeparatedList(T *d, int s); // constructor
    void printList();                // prints the list
};

// Fixed: constructor had wrong parameter type (T vs T*)
template <class T>
CommaSeparatedList<T>::CommaSeparatedList(T *d, int s)
{
    data = d;
    size = s;
}

// Fixed: had a ton of syntax errors (<< >> mixup, invalid type declarations)
// Also renamed variable y → x to match loop control
template <class T>
void CommaSeparatedList<T>::printList()
{
    cout << "Comma separated list:" << endl;
    for (int x = 0; x < size; ++x)
    {
        cout << data[x];
        if (x != size - 1)
            cout << ", ";
    }
    cout << endl << endl;
}

class Book
{
    friend ostream &operator<<(ostream &, const Book &);

private:
    string title;
    int year;

public:
    void setBook(string, int);
};

void Book::setBook(string Title, int y)
{
    title = Title;
    year = y;
}

ostream &operator<<(ostream &out, const Book &b)
{
    out << b.title << " was published in " << b.year;
    return out;
}

class Customer
{
    friend ostream &operator<<(ostream &, const Customer &);

private:
    string name;
    double balDue;

public:
    void setCustomer(string, double);
};

void Customer::setCustomer(string CustomerName, double amount)
{
    name = CustomerName;
    balDue = amount;
}

ostream &operator<<(ostream &out, const Customer &c)
{
    out << c.name << " owes $" << c.balDue;
    return out;
}

int main()
{
    int size;

    // Create lists of different types
    int someInts[] = {12, 34, 55, 77, 99};
    double someDoubles[] = {11.11, 23.44, 44.55, 123.66};

    Book someBooks[2];
    someBooks[0].setBook("Wizard of Oz", 1986);
    someBooks[1].setBook("Harry Potter", 2000);

    Customer someCustomers[6];
    someCustomers[0].setCustomer("Zaps", 23.55);
    someCustomers[1].setCustomer("Martin", 155.77);
    someCustomers[2].setCustomer("Fine", 333.88);
    someCustomers[3].setCustomer("Torrence", 123.99);
    someCustomers[4].setCustomer("Richard", 20.06);
    someCustomers[5].setCustomer("Curtin", 56999.19);

    // Print lists
    size = sizeof(someInts) / sizeof(someInts[0]);
    CommaSeparatedList<int> intList(someInts, size);
    intList.printList();

    size = sizeof(someDoubles) / sizeof(someDoubles[0]);
    CommaSeparatedList<double> doubleList(someDoubles, size);
    doubleList.printList();

    size = sizeof(someBooks) / sizeof(someBooks[0]);
    CommaSeparatedList<Book> bookList(someBooks, size);
    bookList.printList();

    size = sizeof(someCustomers) / sizeof(someCustomers[0]);
    CommaSeparatedList<Customer> customerList(someCustomers, size);
    customerList.printList();

    return 0;
}

