// Ali Younes – younes.al@northeastern.edu
//
// CS3520 Assignment 2 – Part 2b:
// Airline Reservations System Implementation

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <random>
#include <algorithm>
#include <cctype>

using namespace std;

// plane dimensions
constexpr int ROWS = 12;
constexpr int COLS = 6;  // seats A, B, D, E, F, H

// seat state
enum Seat { EMPTY, TAKEN };

// global seat map and passenger names
static vector<vector<Seat>> seats(ROWS, vector<Seat>(COLS, EMPTY));
static vector<vector<string>> names(ROWS, vector<string>(COLS, ""));

// helper to get a full line of input
static string readLine() {
    string line;
    getline(cin, line);
    return line;
}

// welcome screen: ask P, E, or Q
char welcomeAndLogin() {
    while (true) {
        cout << "\nSelect user type — Passenger (P), Employee (E), or Quit (Q): ";
        string input = readLine();
        if (input.empty()) continue;
        char choice = toupper(input[0]);
        if (choice == 'P' || choice == 'E' || choice == 'Q') {
            return choice;
        }
        cout << "Invalid input. Please enter P, E, or Q.\n";
    }
}

// passenger flow
void passengerMenu(const string& passengerName);
void displaySeatingChart();
void manualChooseSeat(const string& passengerName);
void automaticChooseSeat(const string& passengerName);
void changeOrCancelSeat(const string& passengerName);
void printBoardingPass(const string& passengerName);

// employee flow
void employeeMenu();
void printManifest();
void loadDataFromFile();
void saveDataToFile();
void reassignOrCancelAnySeat();

// utilities
pair<int,int> parseSeatID(const string& seatID);
string seatClass(int row);
int classStartRow(char cls);
int classEndRow(char cls);

int main() {
    while (true) {
        char userType = welcomeAndLogin();
        if (userType == 'Q') {
            cout << "Goodbye!\n";
            break;
        } else if (userType == 'P') {
            cout << "Enter your name: ";
            string name = readLine();
            passengerMenu(name);
        } else {  // 'E'
            employeeMenu();
        }
    }
    return 0;
}
// Ali Younes – younes.al@northeastern.edu
//
// CS3520 Assignment 2 – Part 2b:
// Airline Reservations System Implementation

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <random>
#include <algorithm>
#include <cctype>

using namespace std;

// plane dimensions
constexpr int ROWS = 12;
constexpr int COLS = 6;  // seats A, B, D, E, F, H

// seat state
enum Seat { EMPTY, TAKEN };

// global seat map and passenger names
static vector<vector<Seat>> seats(ROWS, vector<Seat>(COLS, EMPTY));
static vector<vector<string>> names(ROWS, vector<string>(COLS, ""));

// helper to get a full line of input
static string readLine() {
    string line;
    getline(cin, line);
    return line;
}

// welcome screen: ask P, E, or Q
char welcomeAndLogin() {
    while (true) {
        cout << "\nSelect user type — Passenger (P), Employee (E), or Quit (Q): ";
        string input = readLine();
        if (input.empty()) continue;
        char choice = toupper(input[0]);
        if (choice == 'P' || choice == 'E' || choice == 'Q') {
            return choice;
        }
        cout << "Invalid input. Please enter P, E, or Q.\n";
    }
}

// passenger flow
void passengerMenu(const string& passengerName);
void displaySeatingChart();
void manualChooseSeat(const string& passengerName);
void automaticChooseSeat(const string& passengerName);
void changeOrCancelSeat(const string& passengerName);
void printBoardingPass(const string& passengerName);

// employee flow
void employeeMenu();
void printManifest();
void loadDataFromFile();
void saveDataToFile();
void reassignOrCancelAnySeat();

// utilities
pair<int,int> parseSeatID(const string& seatID);
string seatClass(int row);
int classStartRow(char cls);
int classEndRow(char cls);

int main() {
    while (true) {
        char userType = welcomeAndLogin();
        if (userType == 'Q') {
            cout << "Goodbye!\n";
            break;
        } else if (userType == 'P') {
            cout << "Enter your name: ";
            string name = readLine();
            passengerMenu(name);
        } else {  // 'E'
            employeeMenu();
        }
    }
    return 0;
}

