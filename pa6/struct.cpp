// Younes.al@northeastern.edu
// Ali Younes 5/23/2025 CS3520 course
//
// Bug fixes summary:
// 1. Added `using namespace std;` so cin/cout work without std::.
// 2. Changed `name = n;` to `c.name = n;` to assign input to the struct.
// 3. Fixed speed input: changed `cin << w;` to `cin >> w;`.
// 4. Fixed speed assignment: changed `c.speed = speed;` to `c.speed = w;`.
// 5. Fixed pointer member access: use `cPtr->name` instead of `cPtr.name`.
// 6. Corrected modelYear output: use `c.modelYear` and `cPtr->modelYear`.
// 7. Added missing `<<` and spaces in cout statements for proper formatting.
// 8. Changed `void main()` to `int main()` and added `return 0;`.
// 9. Removed unused `<string>` include.

#include <iostream>
using namespace std;

struct car {
    char* name;
    int modelYear;
    float speed;
};

int main() {
    char n[20];
    int a;
    float w;

    car c;
    car* cPtr = &c;

    cout << "What is your favorite car's name: ";
    cin >> n;
    c.name = n;  // assign input buffer to struct member

    cout << "When was it launched: ";
    cin >> a;
    c.modelYear = a;

    cout << "How much speed does it give: ";
    cin >> w;
    c.speed = w;

    // print using struct and pointer
    cout << "Car's name is " << c.name
         << ", and should be the same as " << cPtr->name << ".\n";

    cout << "Car's model year is " << c.modelYear
         << ", and should be the same as " << cPtr->modelYear << ".\n";

    cout << "Car's speed is " << c.speed
         << ", and should be the same as " << w << ".\n";

    return 0;
}

