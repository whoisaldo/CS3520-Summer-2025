/*
 * Q4 – Find and Replace
 *
 * 1. Read a paragraph from the keyboard.
 * 2. Prompt user for a word or sentence to find.
 * 3. Find all occurrences: count them and record starting indices.
 * 4. Reverse the search string and replace every occurrence.
 * 5. Print both the original and the modified paragraph.
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    // 1. Read paragraph
    cout << "Enter a paragraph:\n";
    string paragraph;
    getline(cin, paragraph);

    // 2. Prompt for the search string
    cout << "Enter word or sentence to find: ";
    string target;
    getline(cin, target);

    // 3. Locate all occurrences
    vector<size_t> positions;
    size_t pos = 0;
    while ((pos = paragraph.find(target, pos)) != string::npos) {
        positions.push_back(pos);
        pos += target.length();
    }

    // Report count and starting indices
    cout << "\nFound " << positions.size() << " occurrence";
    if (positions.size() != 1) cout << "s";
    cout << " at positions: ";
    for (size_t idx : positions) {
        cout << idx << " ";
    }
    cout << "\n";

    // 4. Build the replacement by reversing the target
    string replacement = target;
    reverse(replacement.begin(), replacement.end());

    // Perform the replacements
    string modified = paragraph;
    pos = 0;
    while ((pos = modified.find(target, pos)) != string::npos) {
        modified.replace(pos, target.length(), replacement);
        pos += replacement.length();
    }

    // 5. Output original vs. modified
    cout << "\nOriginal paragraph:\n" << paragraph << "\n";
    cout << "\nModified paragraph:\n" << modified << "\n";

    return 0;
}
