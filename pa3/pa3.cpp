/*
Author: Ali Younes , Ali Tleis


Pseudocode:
1. Open the input file "input.txt"
2. Read each line:
   - Split the line by commas
   - Convert each token to double
   - Store all values in a 1D vector
3. Determine the total number of values
4. Compute smallest square size >= total for 2D vector
   - Create 2D vector of size n x n, fill values row by row
   - Pad remaining cells with 0.0
5. Compute smallest cube size >= total for 3D array
   - Create 3D array of size n x n x n, fill layer by layer
   - Pad remaining cells with 0.0
6. Implement write_2d_vector:
   - Accepts 2D vector, writes to "2DVector.txt" with aligned formatting
7. Implement write_3d_array:
   - Accepts 3D array and its dimensions, writes to "3DArray.txt"
8. Print sum of all values to the screen
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

// Function to write the 2D vector to a file
void write_2d_vector(const vector<vector<double>>& vec2d, const string& filename) {
    ofstream fout(filename);
    for (const auto& row : vec2d) {
        for (const auto& val : row) {
            fout << fixed << setprecision(1) << val << " ";
        }
        fout << "\n";
    }
    fout.close();
}

// Function to write the 3D array to a file
void write_3d_array(double*** arr3d, int d1, int d2, int d3, const string& filename) {
    ofstream fout(filename);
    for (int i = 0; i < d1; ++i) {
        for (int j = 0; j < d2; ++j) {
            for (int k = 0; k < d3; ++k) {
                fout << fixed << setprecision(1) << arr3d[i][j][k] << " ";
            }
            fout << "\n";
        }
        fout << "\n"; // separate layers
    }
    fout.close();
}

// Helper to find the smallest square dimension ≥ total
int square_root_ceiling(int total) {
    int n = 1;
    while (n * n < total) ++n;
    return n;
}

// Helper to find the smallest cube dimension ≥ total
int cube_root_ceiling(int total) {
    int n = 1;
    while (n * n * n < total) ++n;
    return n;
}

int main() {
    ifstream fin("input.txt");
    if (!fin) {
        cerr << "Error: input.txt not found.\n";
        return 1;
    }

    vector<double> values;
    string line;
    double sum = 0.0;

    // Step 1: Read and parse all values
    while (getline(fin, line)) {
        stringstream ss(line);
        string token;
        while (getline(ss, token, ',')) {
            double val = stod(token);
            values.push_back(val);
            sum += val;
        }
    }
    fin.close();

    int total = values.size();

    // Step 2: 2D vector setup
    int side2D = square_root_ceiling(total);
    vector<vector<double>> vec2d(side2D, vector<double>(side2D, 0.0));

    for (int i = 0; i < total; ++i) {
        int row = i / side2D;
        int col = i % side2D;
        vec2d[row][col] = values[i];
    }

    // Step 3: 3D array setup
    int side3D = cube_root_ceiling(total);
    double*** arr3d = new double**[side3D];
    for (int i = 0; i < side3D; ++i) {
        arr3d[i] = new double*[side3D];
        for (int j = 0; j < side3D; ++j) {
            arr3d[i][j] = new double[side3D];
            for (int k = 0; k < side3D; ++k) {
                arr3d[i][j][k] = 0.0;
            }
        }
    }

    for (int i = 0; i < total; ++i) {
        int x = i / (side3D * side3D);
        int y = (i / side3D) % side3D;
        int z = i % side3D;
        arr3d[x][y][z] = values[i];
    }

    // Step 4: Write outputs
    write_2d_vector(vec2d, "2DVector.txt");
    write_3d_array(arr3d, side3D, side3D, side3D, "3DArray.txt");

    // Step 5: Print sum
    cout << fixed << setprecision(1);
    cout << "Sum of all numbers: " << sum << endl;

    // Clean up 3D array
    for (int i = 0; i < side3D; ++i) {
        for (int j = 0; j < side3D; ++j) {
            delete[] arr3d[i][j];
        }
        delete[] arr3d[i];
    }
    delete[] arr3d;

    return 0;
}

