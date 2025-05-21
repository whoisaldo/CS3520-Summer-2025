// Ali Younes – younes.al@northeastern.edu
//
// CS3520 Assignment 2 – Part 2b: Airline Reservations System
// Implements passenger and employee menus, seat assignment, manifest, boarding passes, and file persistence.

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <random>
#include <algorithm>
#include <cctype>
#include <iomanip>

using namespace std;

// plane dimensions
constexpr int ROWS = 12;
constexpr int COLS = 6;
const vector<char> COL_LETTERS = {'A','B','D','E','F','H'};

// seat state enum
enum Seat { EMPTY, TAKEN };

// global seat map and names
vector<vector<Seat>> seats(ROWS, vector<Seat>(COLS, EMPTY));
vector<vector<string>> names(ROWS, vector<string>(COLS, ""));

// random engine for automatic assignment
static mt19937 gen(random_device{}());

// read a full line safely
string readLine() {
    string line;
    getline(cin, line);
    return line;
}

// parse a seatID like "B4" → (rowIndex, colIndex)
pair<int,int> parseSeatID(const string& seatID) {
    if (seatID.size() < 2) return {-1,-1};
    char colChar = toupper(seatID[0]);
    int col = find(COL_LETTERS.begin(), COL_LETTERS.end(), colChar)
              - COL_LETTERS.begin();
    int row = stoi(seatID.substr(1)) - 1;
    if (col < 0 || col >= COLS || row < 0 || row >= ROWS)
        return {-1,-1};
    return {row, col};
}

// return class name given row index
string seatClass(int row) {
    if (row < 2)    return "First";
    if (row < 5)    return "Business";
    return "Economy";
}

// helper to get start/end row for a class letter
int classStartRow(char cls) {
    cls = toupper(cls);
    if (cls=='F') return 0;
    if (cls=='B') return 2;
    return 5;
}
int classEndRow(char cls) {
    cls = toupper(cls);
    if (cls=='F') return 1;
    if (cls=='B') return 4;
    return 11;
}

// top‐level menu prompt
char welcomeAndLogin() {
    while (true) {
        cout << "\nSelect user type — Passenger (P), Employee (E), or Quit (Q): ";
        string in = readLine();
        if (in.empty()) continue;
        char c = toupper(in[0]);
        if (c=='P' || c=='E' || c=='Q') return c;
        cout << "Invalid input. Enter P, E, or Q.\n";
    }
}

// display full seating chart
void displaySeatingChart() {
    cout << "\n    A   B   D   E   F   H\n";
    for (int r=0; r<ROWS; ++r) {
        cout << setw(2) << (r+1) << " ";
        for (int c=0; c<COLS; ++c) {
            char mark = (seats[r][c]==EMPTY ? ' ' : 'X');
            cout << "[" << mark << "] ";
        }
        cout << "\n";
    }
}

// save taken seats and names to file
void saveDataToFile() {
    ofstream out("seats.txt");
    for (int r=0; r<ROWS; ++r) {
        for (int c=0; c<COLS; ++c) {
            if (seats[r][c]==TAKEN)
                out << COL_LETTERS[c] << (r+1)
                    << ":" << names[r][c] << "\n";
        }
    }
}

// load seats.txt into memory
void loadDataFromFile() {
    for (auto& row : seats)
        for (auto& s : row)
            s = EMPTY;
    for (auto& row : names)
        for (auto& nm : row)
            nm.clear();

    ifstream in("seats.txt");
    string line;
    while (getline(in,line)) {
        auto pos = line.find(':');
        string sid = line.substr(0,pos);
        string nm  = line.substr(pos+1);
        auto [r,c] = parseSeatID(sid);
        if (r>=0) {
            seats[r][c] = TAKEN;
            names[r][c] = nm;
        }
    }
}

// passenger: automatic seat assignment
void automaticChooseSeat(const string& user) {
    cout << "Automating seat for " << user << "...\n";
    cout << "Enter class F/B or any other for Economy: ";
    string in = readLine();
    char cls = in.empty() ? 'E' : toupper(in[0]);

    int start = classStartRow(cls), end = classEndRow(cls);
    uniform_int_distribution<> rowDist(start,end),
                               colDist(0,COLS-1);

    bool assigned = false;
    for (int tries=0; tries<ROWS*COLS; ++tries) {
        int r = rowDist(gen), c = colDist(gen);
        if (seats[r][c]==EMPTY) {
            seats[r][c] = TAKEN;
            names[r][c] = user;
            cout << "Assigned seat " 
                 << COL_LETTERS[c] << (r+1)
                 << " (" << seatClass(r) << ")\n";
            saveDataToFile();
            assigned = true;
            break;
        }
    }
    if (!assigned)
        cout << "Next flight leaves in 3 hours.\n";
}

// passenger: manual seat choice, rubric‐compliant
void manualChooseSeat(const string& user) {
    // 1) ask class
    cout << "Enter class F/B or any other for Economy: ";
    string in = readLine();
    char cls = in.empty() ? 'E' : toupper(in[0]);

    int start = classStartRow(cls);
    int end   = classEndRow(cls);

    // 2) list available seats in that class
    vector<string> avail;
    for (int r=start; r<=end; ++r) {
        for (int c=0; c<COLS; ++c) {
            if (seats[r][c]==EMPTY) {
                avail.push_back(string()+COL_LETTERS[c]+to_string(r+1));
            }
        }
    }
    if (avail.empty()) {
        cout << "Sorry, no available seats in that class.\n";
        return;
    }

    cout << "Available seats in " 
         << seatClass(start) << " class: ";
    for (auto &sid : avail) cout << sid << " ";
    cout << "\n";

    // 3) pick one of those
    while (true) {
        cout << "Enter desired seat ID (e.g. B4): ";
        string sid = readLine();
        if (find(avail.begin(), avail.end(), sid) == avail.end()) {
            cout << "Invalid or taken seat. Please choose from the list above.\n";
            continue;
        }
        auto [r,c] = parseSeatID(sid);
        seats[r][c] = TAKEN;
        names[r][c] = user;
        cout << "Seat " << sid << " assigned to " << user << ".\n";
        saveDataToFile();
        break;
    }
}

// passenger: change or cancel reservation
void changeOrCancelSeat(const string& user) {
    cout << "Type C to cancel or X to change: ";
    string in = readLine();
    char op = toupper(in.empty() ? ' ' : in[0]);

    cout << "Enter current seat ID: ";
    string oldID = readLine();
    auto [r,c] = parseSeatID(oldID);

    if (r<0 || names[r][c] != user) {
        cout << "No matching reservation.\n";
        return;
    }

    if (op=='C') {
        seats[r][c] = EMPTY;
        names[r][c].clear();
        cout << "Reservation cancelled.\n";
    }
    else if (op=='X') {
        seats[r][c] = EMPTY;
        names[r][c].clear();
        cout << "Reservation freed. Now choose new seat manually.\n";
        manualChooseSeat(user);
    }
    else {
        cout << "Invalid option.\n";
    }
    saveDataToFile();
}

// passenger: print boarding pass (handles duplicates/unassigned)
void printBoardingPass(const string& user) {
    cout << "Enter name or seat ID: ";
    string in = readLine();
    int rr=-1, cc=-1;

    // if input looks like a seat ID
    if (in.size()>1 && isalpha(in[0]) && isdigit(in[1])) {
        tie(rr,cc) = parseSeatID(in);
    } else {
        // gather all seats matching that name
        vector<string> matches;
        for (int r=0; r<ROWS; ++r){
            for (int c=0; c<COLS; ++c){
                if (names[r][c]==in) {
                    matches.push_back(string()+COL_LETTERS[c]+to_string(r+1));
                }
            }
        }
        if (matches.empty()) {
            cout << "Seat Unassigned - No boarding pass available.\n";
            return;
        }
        if (matches.size()>1) {
            // disambiguate
            cout << "Multiple seats found: ";
            for (auto &s : matches) cout << s << " ";
            cout << "\nEnter seat ID to print: ";
            string sid = readLine();
            tie(rr,cc) = parseSeatID(sid);
        } else {
            // exactly one match
            tie(rr,cc) = parseSeatID(matches[0]);
        }
    }

    if (rr<0 || seats[rr][cc]==EMPTY) {
        cout << "Seat Unassigned - No boarding pass available.\n";
        return;
    }

    // print it
    cout << "BOARDING PASS:\n"
         << in << ", SEAT: "
         << COL_LETTERS[cc] << (rr+1)
         << ", Level: " << seatClass(rr) << " Class\n";
}

// passenger menu loop
void passengerMenu(const string& user) {
    while (true) {
        cout << "\n1) Show chart  2) Auto-choose  3) Manual"
             << "  4) Change/Cancel  5) Boarding Pass  6) Quit\n";
        cout << "Select (1-6): ";
        char c = readLine()[0];

        if      (c=='1') displaySeatingChart();
        else if (c=='2') automaticChooseSeat(user);
        else if (c=='3') manualChooseSeat(user);
        else if (c=='4') changeOrCancelSeat(user);
        else if (c=='5') printBoardingPass(user);
        else if (c=='6') break;
        else             cout << "Invalid.\n";
    }
}

// employee: passenger manifest with Seat/Name/Class sorting
void printManifest() {
    vector<pair<string,string>> list;
    for (int r=0; r<ROWS; ++r)
        for (int c=0; c<COLS; ++c)
            if (seats[r][c]==TAKEN)
                list.push_back({names[r][c],
                                string()+COL_LETTERS[c]+to_string(r+1)});

    cout << "Sort by Seat (S), Name (N), or Class (C): ";
    char opt = toupper(readLine()[0]);

    if (opt=='N') {
        sort(list.begin(), list.end(),
             [](const pair<string,string>& a,
                const pair<string,string>& b){
                 return a.first < b.first;
             });
    }
    else if (opt=='S') {
        sort(list.begin(), list.end(),
             [](const pair<string,string>& a,
                const pair<string,string>& b){
                 return a.second < b.second;
             });
    }
    else if (opt=='C') {
        // group by class, then by seat
        vector<pair<string,string>> firstC, busC, econC;
        for (auto &p : list) {
            auto [r,c] = parseSeatID(p.second);
            if (r<2)      firstC.push_back(p);
            else if (r<5) busC.push_back(p);
            else          econC.push_back(p);
        }
        auto cmpSeat = [](auto &a, auto &b){
            return a.second < b.second;
        };
        sort(firstC.begin(), firstC.end(), cmpSeat);
        sort(busC.begin(),   busC.end(),   cmpSeat);
        sort(econC.begin(),  econC.end(),  cmpSeat);
        list.clear();
        list.insert(list.end(), firstC.begin(), firstC.end());
        list.insert(list.end(), busC.begin(),   busC.end());
        list.insert(list.end(), econC.begin(),  econC.end());
    }

    cout << "MANIFEST:\n";
    for (auto &p : list)
        cout << p.first << " - " << p.second << "\n";
}

// employee: reassign or cancel any seat
void reassignOrCancelAnySeat() {
    cout << "Type C to cancel or R to reassign: ";
    char op = toupper(readLine()[0]);

    cout << "Enter seat ID: ";
    string sid = readLine();
    auto [r,c] = parseSeatID(sid);

    if (r<0 || seats[r][c]==EMPTY) {
        cout << "No reservation there.\n";
        return;
    }
    string user = names[r][c];
    seats[r][c] = EMPTY;
    names[r][c].clear();

    if (op=='C') {
        cout << "Cancelled " << sid << " for " << user << ".\n";
    }
    else if (op=='R') {
        cout << "Reassigning for " << user << ".\n";
        manualChooseSeat(user);
    }
    else {
        cout << "Invalid option.\n";
    }
    saveDataToFile();
}

// employee menu loop
void employeeMenu() {
    cout << "Enter employee username: ";
    string u = readLine();
    cout << "Enter password: ";
    string p = readLine();
    if (u!="admin" || p!="password") {
        cout << "Auth failed.\n";
        return;
    }

    loadDataFromFile();
    while (true) {
        cout << "\nE) Show chart  M) Manifest  L) Load"
             << "  S) Save  R) Reassign/Cancel  Q) Quit\n";
        cout << "Select: ";
        char c = toupper(readLine()[0]);

        if      (c=='E') displaySeatingChart();
        else if (c=='M') printManifest();
        else if (c=='L') loadDataFromFile();
        else if (c=='S') saveDataToFile();
        else if (c=='R') reassignOrCancelAnySeat();
        else if (c=='Q') break;
        else             cout << "Invalid.\n";
    }
}

// program entry point
int main() {
    while (true) {
        char t = welcomeAndLogin();
        if (t=='Q') {
            cout << "Goodbye!\n";
            break;
        }
        if (t=='P') {
            cout << "Enter name: ";
            string name = readLine();
            passengerMenu(name);
        }
        else {
            employeeMenu();
        }
    }
    return 0;
}
