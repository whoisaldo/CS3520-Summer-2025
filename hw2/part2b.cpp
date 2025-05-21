// Ali Younes    – younes.al@northeastern.edu
// CS3520 Assignment 2 – Part 2b:
//   Airline Reservations System Implementation
//   Uses a 2D array (vector) for seats & names.
//   One function per rubric bullet.
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <random>
#include <algorithm>

using namespace std;

// Constants for plane dimensions
constexpr int ROWS = 12;
constexpr int COLS = 6;  // A,B,D,E,F,H

// Seat state
enum Seat { EMPTY, TAKEN };

// Global data structures
static vector<vector<Seat>> seats(ROWS, vector<Seat>(COLS, EMPTY));
static vector<vector<string>> names(ROWS, vector<string>(COLS, ""));

// Function prototypes (one per rubric item)
// 1) Welcome & login
char  welcomeAndLogin();

// 2) Passenger menu handlers
void passengerMenu(const string& passengerName);
void displaySeatingChart();
void manualChooseSeat(const string& passengerName);
void automaticChooseSeat(const string& passengerName);
void changeOrCancelSeat(const string& passengerName);
void printBoardingPass(const string& passengerName);

// 3) Employee menu handlers
void employeeMenu();
void printManifest();
void loadDataFromFile();
void saveDataToFile();
void reassignOrCancelAnySeat();

// 4) Helpers
pair<int,int> parseSeatID(const string& seatID);
string      seatClass(int row);
int         classStartRow(char cls);
int         classEndRow(char cls);

// Entry point
int main() {
    while (true) {
        char userType = welcomeAndLogin();
        if (userType == 'P') {
            // ask for name, then:
            string name;
            cout << "Enter your name: ";
            getline(cin, name);
            passengerMenu(name);
        }
        else if (userType == 'E') {
            employeeMenu();
        }
        else {
            // Quit
            break;
        }
    }
    return 0;
}
