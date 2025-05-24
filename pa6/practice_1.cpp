// Younes.al@northeastern.edu
// Ali Younes 5/23/2025 CS3520 course
//
// Bug fixes summary:
// 1. Changed void main() to int main().
// 2. Added #include <iostream> and using namespace std.
// 3. Read the number from user instead of using a hard-coded char.
// 4. Renamed and fixed the palindrome function signature to bool isPalindrome(int).
// 5. Fixed while loop to use `while (n != 0)` and correct % and / operations.
// 6. Built the reversed number properly with `rev = rev * 10 + digit`.
// 7. Added missing semicolons and quotes around text in cout.
// 8. Made main return 0 at the end.

// Program to check if the user-provided number is a palindrome

#include <iostream>
using namespace std;

// returns true if n reads the same forward and backward
bool isPalindrome(int n) {
    int original = n;
    int rev = 0;
    int digit;

    // build reversed number
    while (n != 0) {
        digit = n % 10;      // last digit
        n = n / 10;          // drop last digit
        rev = rev * 10 + digit;  // append digit
    }
    return (rev == original);
}

int main() {
    int number;
    cout << "Enter an integer: ";
    cin >> number;

    // check and print result
    if (isPalindrome(number))
        cout << "It is a palindrome" << endl;
    else
        cout << "It is not a palindrome" << endl;

    return 0;
}

