/*
 * Q1C – Bugs fixed in file3.cpp:
 *  1. Fixed header typo: changed <iosteam> to <iostream>.
 *  2. Added `using namespace std;` so cout/cin resolve.
 *  3. Replaced Python‑style `False` with C++ `false`.
 *  4. Changed `if(num == 0 && num ==1)` to `if(num == 0 || num == 1)`.
 *  5. Replaced colons in `if` and `for` headers with semicolons.
 *  6. Fixed loop syntax to `for(int i = 2; i * i <= num; ++i)`.
 *  7. Added parentheses in `if (num % i == 0)` test.
 *  8. Unified variable name to `factor_found`.
 *  9. Replaced `not factor_found` with `!factor_found`.
 * 10. Ensured `main` returns 0 at the end.
 */

#include <iostream>
using namespace std;

int main() {
    int num;
    bool factor_found = false;

    // Prompt the user
    cout << "Enter Number: ";
    cin  >> num;

    // 0 and 1 are neither prime nor composite
    if (num == 0 || num == 1) {
        cout << num << " is not prime or composite\n";
        return 0;
    }

    // Check for divisors up to sqrt(num)
    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) {
            factor_found = true;
            break;
        }
    }

    // Output the result
    if (!factor_found) {
        cout << num << " is a prime number\n";
    } else {
        cout << num << " is a composite number\n";
    }

    return 0;
}
