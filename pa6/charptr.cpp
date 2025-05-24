// Younes.al@northeastern.edu
// Ali Younes 5/23/2025 CS3520 course

// Bug fixes summary:
// 1. Switched include to <iostream> and removed invalid <stdio> and unused <string>.
// 2. Changed main signature from void main to int main.
// 3. Used cin.getline(s, 20) so input can include spaces.
// 4. Declared cPtr as char* (pointer), not char.
// 5. Initialized cPtr to point at the start of the array: cPtr = s.
// 6. Replaced the broken while loop (cPtr-- == '\0') with a for-loop using pointer offset.
// 7. Corrected loop condition to stop at the null terminator: *(cPtr + i) != '\0'.
// 8. Added return 0 at end of main and removed unreachable code paths.

#include <iostream>
using namespace std;

int main() {
    char s[20];       // buffer for input string (max 19 chars + '\0')
    char* cPtr;       // pointer to walk through the string

    // prompt and read a full line, including spaces
    cout << "Enter a string: ";
    cin.getline(s, 20);

    // point cPtr to the first character of s
    cPtr = s;

    // print each character using pointer offset notation
    for (int i = 0; *(cPtr + i) != '\0'; i++) {
        cout << *(cPtr + i);
    }
    cout << "\n";

    return 0;
}

