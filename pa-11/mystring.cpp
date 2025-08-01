//younes.al@northeastern.edu
//CS3520 - Summer 2025 - 6/13/2025
//Ali younes
#include <iostream>
#include <memory>
#include <cstring>
using namespace std;

class MyString {
    unique_ptr<char[]> str; // use smart pointer for RAII

public:
    // default constructor
    MyString() {
        str = make_unique<char[]>(1);
        str[0] = '\0';
    }

    // constructor with C-string
    MyString(char* val) {
        if (val == nullptr) {
            str = make_unique<char[]>(1);
            str[0] = '\0';
        } else {
            size_t len = strlen(val) + 1;
            str = make_unique<char[]>(len);
            strcpy(str.get(), val);
            cout << "The given string is: " << str.get() << endl;
        }
    }

    // copy constructor
    MyString(const MyString& source) {
        size_t len = strlen(source.str.get()) + 1;
        str = make_unique<char[]>(len);
        strcpy(str.get(), source.str.get());
    }

    // move constructor
    MyString(MyString&& source) noexcept {
        str = move(source.str); // move ownership
    }

    // destructor is implicit, smart pointer handles it
};

int main() {
    cout << "Start!" << endl;
    MyString a;
    MyString b{ (char*)"Hello" };
    MyString c{ a };
    MyString d{ MyString{ (char*)"World" } };
    cout << "Bye" << endl;
}

