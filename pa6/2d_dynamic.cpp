// Younes.al@northeastern.edu
// Ali Younes 5/23/2025 CS3520 course



// Fixed bugs summary:
// 1. Corrected malloc size for row pointers (should be int* not int).
// 2. Fixed for-loop syntax (comma to semicolon).
// 3. Corrected malloc size for each row (int, not int*).
// 4. Fixed array initialization expression (use proper pointer arithmetic).
// 5. Added missing semicolon after assignment.
// 6. Fixed inner loop limit for printing (use M, not N).
// 7. Used only * and [] operators as required for access and print.
// 8. Fixed memory deallocation (free each row pointer, not pointer arithmetic).
// 9. Added malloc error checks to prevent crashes.

#include <iostream>
#include <cstdlib>
using namespace std;

int main()
{
    int N = 3, M = 5;
    int i, j;

    // Allocate memory for N row pointers
    int **d_array = (int **)malloc(N * sizeof(int *));
    if (d_array == NULL) {
        cerr << "Memory allocation failed for rows" << endl;
        return 1;
    }

    // Allocate memory for each row with M columns
    for (i = 0; i < N; i++)
    {
        d_array[i] = (int *)malloc(M * sizeof(int));
        if (d_array[i] == NULL) {
            cerr << "Memory allocation failed for columns in row " << i << endl;
            return 1;
        }
    }

    // Initialize 2D array using pointer arithmetic
    cout << "Initializing array values!" << endl;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            // Correct way to access using * and [] only
            *( *(d_array + i) + j ) = i + j;
        }
    }

    // Print 2D array using only * and [] operators
    cout << "\nArray contents:\n";
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            cout << *(*(d_array + i) + j) << " ";
        }
        cout << "\n";
    }

    // Free allocated memory for each row
    for (i = 0; i < N; i++)
    {
        free(d_array[i]);
    }
    // Free the array of row pointers
    free(d_array);

    return 0;
}

