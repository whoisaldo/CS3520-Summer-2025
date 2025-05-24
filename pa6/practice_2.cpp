// Younes.al@northeastern.edu
// Ali Younes 5/23/2025 CS3520 course
//
// Bug fixes summary:
// 1. Changed matrix size from [size+1][size+1] to fixed [3][3].  
// 2. Switched prompt from cin << to cout <<.  
// 3. Declared loop variable i inside the for loop.  
// 4. Fixed input indexing from Matrix[j][i] to Matrix[i][j].  
// 5. Updated display prototype to use int Matrix[3][3] and int size.  
// 6. Passed Matrix directly to display, not &Matrix.  
// 7. Fixed for-loop separators (used “;” instead of “,”).  
// 8. Fixed inner loop increment to j++, not i++.  
// 9. Added missing semicolon after cout << endl.

#include <iostream>
using namespace std;

// display now matches matrix type and size parameter
void display(int Matrix[3][3], int size);

int main() {
    int size = 3;
    // fixed: declare a 3x3 matrix, not size+1
    int Matrix[3][3];

    // fixed: use cout for prompt
    cout << "Enter 9 elements of the matrix:" << endl;

    // fixed: declare i here
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            // fixed: read into Matrix[i][j], not Matrix[j][i]
            cin >> Matrix[i][j];
        }
    }

    // fixed: pass Matrix, not &Matrix
    display(Matrix, size);
    return 0;
}

void display(int Matrix[3][3], int size) {
    // fixed: use semicolons in for loops
    for (int i = 0; i < size; i++) {
        // fixed: increment j, not i
        for (int j = 0; j < size; j++) {
            cout << Matrix[i][j] << " ";
        }
        // fixed: add missing semicolon
        cout << endl;
    }
}

