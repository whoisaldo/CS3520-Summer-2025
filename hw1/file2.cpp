/*
 * Q1B – Bugs fixed in file2.cpp:
 *  1. Missing opening quote on the first prompt.
 *  2. Mis‑typed stream operator and variable for reading areaCode/exchange.
 *  3. Missing semicolon after the second prompt.
 *  4. Loop headers used colons/commas instead of semicolons.
 *  5. Declared digit variables as char and did a complex nested loop → replaced with a single numeric loop.
 *  6. Incorrect cout syntax (`cout<< digit1,digit2…`) → now uses iomanip for zero‑padding.
 *  7. Printed the subscription message inside the loop instead of once before it.
 *  8. main returned nothing → changed to `return 0;`.
 */

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int areaCode, exchange;

    cout << "Hello, I am a telemarketing calling program.\n";
    cout << "Enter a three‑digit area code: ";
    cin  >> areaCode;
    cout << "Enter a three‑digit exchange to call: ";
    cin  >> exchange;

    // Print the sales message once
    cout << "\nI am calling to tell you to buy a subscription to Dogs Monthly Magazine!\n\n";

    // Print every number from 0001 to 9999 with leading zeros
    for (int num = 1; num <= 9999; ++num) {
        cout << setw(3) << setfill('0') << areaCode << '-'
             << setw(3) << setfill('0') << exchange << '-'
             << setw(4) << setfill('0') << num
             << "\n";
    }

    cout << "\nCalls completed\n";
    return 0;
}
