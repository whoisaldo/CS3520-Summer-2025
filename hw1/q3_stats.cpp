/*
 * Q3 – Statistics from a Paragraph
 *
 * Reads a paragraph, prints it, then computes:
 *  1. Total number of words
 *  2. Total vowels and consonants
 *  3. Number of words with exactly two vowels
 *  4. Number of words containing any of: ! . , ; " ' ? $
 * 
 * Then:
 *  5. Prompts user for a word‑length L, counts words of length <= L
 *     (excluding punctuation in the length)
 *  6. Picks a random R ∈ [3,9], and counts words of length < R
 *     (including punctuation in the length)
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <random>
using namespace std;

// helper: is vowel?
bool isVowel(char c) {
    c = tolower(static_cast<unsigned char>(c));
    return c=='a'||c=='e'||c=='i'||c=='o'||c=='u';
}

// strip punctuation from word for length calculation
string stripPunct(const string &w) {
    string out;
    for (char c: w) {
        if (isalnum(static_cast<unsigned char>(c))) out += c;
    }
    return out;
}

int main() {
    // 1. Read paragraph
    cout << "Enter a paragraph:\n";
    string paragraph;
    getline(cin, paragraph);

    // 2. Print it neatly
    cout << "\nYou entered:\n" << paragraph << "\n\n";

    // 3. Tokenize into words
    istringstream iss(paragraph);
    vector<string> words;
    string token;
    while (iss >> token) {
        words.push_back(token);
    }

    // 4. Count total words
    int totalWords = static_cast<int>(words.size());

    // 5. Count vowels & consonants in whole paragraph
    int vowelCount = 0, consonantCount = 0;
    for (char c: paragraph) {
        if (isalpha(static_cast<unsigned char>(c))) {
            if (isVowel(c)) ++vowelCount;
            else ++consonantCount;
        }
    }

    // 6. Words with exactly two vowels
    int twoVowelWords = 0;
    for (auto &w: words) {
        int v=0;
        for (char c: w) if (isVowel(c)) ++v;
        if (v==2) ++twoVowelWords;
    }

    // 7. Words containing any of the eight punctuation marks
    const string marks = "!.,;\"'?$";
    int punctWords = 0;
    for (auto &w: words) {
        for (char c: w) {
            if (marks.find(c)!=string::npos) {
                ++punctWords;
                break;
            }
        }
    }

    // 8. Prompt user for length L (exclude punctuation in length)
    int L;
    cout << "Enter a word length (L): ";
    cin  >> L;
    int countLE = 0;
    for (auto &w: words) {
        string clean = stripPunct(w);
        if (static_cast<int>(clean.size()) <= L) ++countLE;
    }

    // 9. Generate random R in [3,9], include punctuation in length
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(3,9);
    int R = dist(gen);
    int countLT = 0;
    for (auto &w: words) {
        if (static_cast<int>(w.size()) < R) ++countLT;
    }

    // 10. Print all stats
    cout << "\nStatistics:\n"
         << "Total words: " << totalWords << "\n"
         << "Vowels:      " << vowelCount << "\n"
         << "Consonants:  " << consonantCount << "\n"
         << "Words w/ exactly 2 vowels: " << twoVowelWords << "\n"
         << "Words w/ punctuation:      " << punctWords << "\n"
         << "Words length ≤ " << L << ":        " << countLE << "\n"
         << "Random R = " << R 
         << "; words length < R: " << countLT << "\n";

    return 0;
}
