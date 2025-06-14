// Younes.al@northeastern.edu
// Ali Younes 6/13/2025
#include <iostream>
#include <string>
using namespace std;

// Fixed: All template parameters must have types; fixed incorrect int usage and logic
template <class T>
void findBiggest(T a, T b, T c)
{
    T large = a;
    if (b > large)
        large = b;
    if (c > large)
        large = c;
    cout << "The largest of " << a << ", " << b << ", " << c << " is " << large << endl;
}

// Fixed: Logical bug — if (b == large) does nothing meaningful for finding largest
// Fixed: 'larger' was undeclared — changed output to use correct 'large'
template <class T>
void findBiggest(T a, T b)
{
    T large = a;
    if (b > large)
        large = b;
    cout << "The larger of " << a << " and " << b << " is " << large << endl;
}

class BankAccount
{
    // Fixed: Added correct ostream friend declaration
    friend ostream &operator<<(ostream &, const BankAccount &);

private:
    string name;
    int amount;

public:
    BankAccount(const string &, int); // Fixed: added string name param in declaration
    bool operator>(const BankAccount &) const;
};

// Fixed: constructor had missing string name argument in header
BankAccount::BankAccount(const string &n, int a)
{
    name = n;
    amount = a;
}

// Fixed: incorrect syntax: 'Name << " name' changed to proper stream insertion
ostream &operator<<(ostream &out, const BankAccount &bh)
{
    out << "Name: " << bh.name << " Amount: " << bh.amount;
    return out;
}

// Fixed: '==' used instead of '='; also added const correctness
bool BankAccount::operator>(const BankAccount &bh) const
{
    return amount > bh.amount;
}

int main()
{
    BankAccount bAA("A", 800);
    BankAccount bAB("B", 120);
    BankAccount bAC("C", 500);

    findBiggest(bAA, bAB);
    findBiggest(bAB, bAC);
    findBiggest(bAC, bAA);
    findBiggest(bAA, bAB, bAC);

    return 0;
}

