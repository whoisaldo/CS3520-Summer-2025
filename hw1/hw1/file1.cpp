/*
 * Q1A – Bugs fixed in file1.cpp:
 * 1. limit was initialized to 0 instead of 10.
 * 2. even_product & odd_product initialized to 1 (not 0).
 * 3. Fixed for-loop syntax (semicolons, declared int i).
 * 4. Changed i/2=0 to i%2==0; changed i**2==1 to i%2!=0.
 * 5. Moved sum calculation & print outside loop; fixed cout syntax.
 * 6. Added using namespace std; for cout.
 * 7. Changed character loop to start at 'Z', step -2, and print c.
 */

#include <iostream>
using namespace std;

int main() {
    int limit = 10;
    long long even_product = 1, odd_product = 1;
    long long sum = 0;

    cout << "The value of limit is " << limit << endl;

    for (int i = 1; i <= limit; ++i) {
        if (i % 2 == 0)
            even_product *= i;
        else
            odd_product *= i;
    }

    sum = even_product + odd_product;
    cout << "The Sum = " << sum << endl;

    cout << " ";
    for (char c = 'Z'; c >= 'A'; c -= 2) {
        cout << c << " ";
    }
    cout << endl;

    return 0;
}

