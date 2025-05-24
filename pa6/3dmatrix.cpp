// Younes.al@northeastern.edu
// Ali Younes 5/23/2025 CS3520 course

// Bug fixes summary:
// 1. Removed fixed macro SIZE, now taking size input from user.
// 2. Replaced 3D static array with a dynamically allocated 1D array for easy traversal.
// 3. Implemented update_3d to fill the flattened array with user input.
// 4. Changed display_1d to use a single loop and iterator, printing addresses and values.
// 5. Added const qualifier to display_1d matrix parameter to prevent modification.
// 6. Properly allocated and deallocated dynamic memory with new/delete[].

#include <iostream>
using namespace std;

// Function prototypes
void update_3d(double* matrix, int size);
void display_1d(const double* matrix, int size);

int main() {
    int size;
    cout << "Enter size of 3D matrix: ";
    cin >> size;

    // Allocate memory for size^3 elements (flattened 3D array)
    double* matrix = new double[size * size * size]();

    // Initialize matrix elements from user input
    update_3d(matrix, size);

    // Display elements and their addresses using a single loop
    display_1d(matrix, size);

    // Free allocated memory
    delete[] matrix;

    return 0;
}

// Fill matrix elements by reading from user (flattened array)
void update_3d(double* matrix, int size) {
    cout << "Enter " << size * size * size << " elements for the 3D matrix:\n";
    for (int i = 0; i < size * size * size; i++) {
        cin >> matrix[i];
    }
}

// Display matrix elements and addresses using a single iterator, without modifying matrix
void display_1d(const double* matrix, int size) {
    int total = size * size * size;
    for (int i = 0; i < total; i++) {
        cout << "Address: " << (matrix + i) << ", Value: " << matrix[i] << "\n";
    }
}

