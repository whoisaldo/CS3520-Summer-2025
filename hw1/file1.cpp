/*
 * Q1A – file1.cpp fixes:
 *  1. limit was initialized to 0 instead of 10.
 *  2. even_product & odd_product were 0 (should start at 1 for multiplication).
 *  3. for‑loop syntax used colons; replaced with semicolons and declared i.
 *  4. Tested even with `i/2 = 0` (assignment! wrong test) → changed to `i % 2 == 0`.
 *  5. Used `i ** 2 == 1` (invalid C++) → changed to `i % 2 != 0`.
 *  6. sum was updated inside loop and printed with wrong `cout` syntax → moved outside loop and fixed stream insertion.
 *  7. No `std::` or `using namespace std;` for `cout` → added `using namespace std;`.
 *  8. Character loop used lowercase and wrong variable (`i`); fixed to loop `c` from 'Z' to 'A' stepping –2 and print `c`.
 */
#include <iostream>
using namespace std;

int main() {
    int limit = 10;                   // 1. Set limit to 10
    long long even_product = 1,       // 2. Initialize products to 1
              odd_product = 1;
    long long sum = 0;

    cout << "The value of limit is " << limit << endl;

    // Compute product of evens and odds from 1 to limit
    for (int i = 1; i <= limit; ++i) {       // 3. Proper for‑loop
        if (i % 2 == 0)                      // 4. Even test
            even_product *= i;              // multiply evens
        else                                 // 5. Odd test
            odd_product *= i;               // multiply odds
    }

    sum = even_product + odd_product;        // 6. Sum products once
    cout << "The Sum = " << sum << endl;

    // Print alternate uppercase letters in reverse
    cout << " ";
    for (char c = 'Z'; c >= 'A'; c -= 2) {   // 8. c from Z down to A, step 2
        cout << c << " ";
    }
    cout << endl;

    return 0;
}
