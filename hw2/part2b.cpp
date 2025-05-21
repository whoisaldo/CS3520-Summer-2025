// Ali Younes – younes.al@northeastern.edu
//
// CS3520 Assignment 2 – Part 2b: Airline Reservations System Implementation

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <random>
#include <algorithm>
#include <cctype>
#include <iomanip>

using namespace std;

// plane dims
constexpr int ROWS = 12;
constexpr int COLS = 6;
const vector<char> COL_LETTERS = {'A','B','D','E','F','H'};

// seat state
enum Seat { EMPTY, TAKEN };

// global data
vector<vector<Seat>> seats(ROWS, vector<Seat>(COLS, EMPTY));
vector<vector<string>> names(ROWS, vector<string>(COLS, ""));

// random engine for auto-assign
static mt19937 gen(random_device{}());

// helper: read a full line of input
string readLine() {
    string line;
    getline(cin, line);
    return line;
}

// parse seatID like "B4" → (row, col)
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

// get class name from row index
string seatClass(int row) {
    if (row < 2)    return "First";
    if (row < 5)    return "Business";
    return "Economy";
}

// class ranges helpers
int classStartRow(char cls) {
    cls = toupper(cls);
    if (cls == 'F') return 0;
    if (cls == 'B') return 2;
    return 5;
}
int classEndRow(char cls) {
    cls = toupper(cls);
    if (cls == 'F') return 1;
    if (cls == 'B') return 4;
    return 11;
}

// welcome screen: ask P, E, or Q
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

// display seating chart
void displaySeatingChart() {
    cout << "\n    A   B   D   E   F   H\n";
    for (int r = 0; r < ROWS; ++r) {
        cout << setw(2) << (r+1) << " ";
        for (int c = 0; c < COLS; ++c) {
            char mark = (seats[r][c]==EMPTY ? ' ' : 'X');
            cout << "[" << mark << "] ";
        }
        cout << "\n";
    }
}

// save current state to file
void saveDataToFile() {
    ofstream out("seats.txt");
    for (int r=0; r<ROWS; ++r)
        for (int c=0; c<COLS; ++c)
            if (seats[r][c]==TAKEN)
                out << COL_LETTERS[c] << (r+1)
                    << ":" << names[r][c] << "\n";
}

// load state from file
void loadDataFromFile() {
    for (auto &row : seats) for (auto &s : row)    s = EMPTY;
    for (auto &row : names) for (auto &nm: row)  nm.clear();
    ifstream in("seats.txt");
    string line;
    while (getline(in,line)) {
        auto pos = line.find(':');
        auto sid = line.substr(0,pos);
        string nm = line.substr(pos+1);
        auto [r,c] = parseSeatID(sid);
        if (r>=0) { seats[r][c]=TAKEN; names[r][c]=nm; }
    }
}

// automatic seat choice
void automaticChooseSeat(const string& user) {
    cout<<"Automating seat for "<<user<<"...\n";
    cout<<"Enter class F/B or any other for Economy: ";
    string in=readLine(); char cls = in.empty()? 'E': toupper(in[0]);
    int start = classStartRow(cls), end = classEndRow(cls);
    uniform_int_distribution<> rowDist(start,end), colDist(0,COLS-1);
    bool assigned=false;
    for (int tries=0; tries<ROWS*COLS; ++tries) {
        int r=rowDist(gen), c=colDist(gen);
        if (seats[r][c]==EMPTY) {
            seats[r][c]=TAKEN;
            names[r][c]=user;
            cout<<"Assigned seat "<<COL_LETTERS[c]
                <<(r+1)<<" ("<<seatClass(r)<<")\n";
            saveDataToFile();
            assigned=true;
            break;
        }
    }
    if (!assigned) cout<<"Next flight leaves in 3 hours.\n";
}

// manual seat choice
void manualChooseSeat(const string& user) {
    while (true) {
        cout<<"Enter desired seat ID (e.g. B4): ";
        string sid=readLine(); auto [r,c]=parseSeatID(sid);
        if (r<0) { cout<<"Invalid seat ID. Try again.\n"; continue; }
        if (seats[r][c]==TAKEN) { cout<<"Seat taken. Choose another.\n"; continue; }
        seats[r][c]=TAKEN;
        names[r][c]=user;
        cout<<"Seat "<<sid<<" assigned to "<<user<<".\n";
        saveDataToFile();
        break;
    }
}

// change or cancel seat
void changeOrCancelSeat(const string& user) {
    cout<<"Type C to cancel or X to change: ";
    string in=readLine(); char op = toupper(in.empty()? ' ':in[0]);
    cout<<"Enter current seat ID: "; string oldID=readLine();
    auto [r,c]=parseSeatID(oldID);
    if (r<0 || names[r][c]!=user) { cout<<"No matching reservation.\n"; return; }
    if (op=='C') {
        seats[r][c]=EMPTY; names[r][c].clear();
        cout<<"Reservation cancelled.\n";
    } else if (op=='X') {
        seats[r][c]=EMPTY; names[r][c].clear();
        cout<<"Reservation freed. Now choose new seat manually.\n";
        manualChooseSeat(user);
    } else cout<<"Invalid option.\n";
    saveDataToFile();
}

// print boarding pass
void printBoardingPass(const string& user) {
    cout<<"Enter name or seat ID: "; string in=readLine();
    int rr=-1, cc=-1;
    if (in.size()>1 && isalpha(in[0]) && isdigit(in[1])) {
        tie(rr,cc)=parseSeatID(in);
    } else {
        for(int r=0;r<ROWS;++r)for(int c=0;c<COLS;++c)
            if (names[r][c]==in) { rr=r; cc=c; break; }
    }
    if (rr<0 || seats[rr][cc]==EMPTY) {
        cout<<"Seat Unassigned - No Boarding pass available. Try Again!\n";
        return;
    }
    cout<<"BOARDING PASS:\n";
    cout<<in<<", SEAT: "<<COL_LETTERS[cc]<<(rr+1)
        <<", Level: "<<seatClass(rr)<<" Class\n";
}

// print passenger manifest
void printManifest() {
    vector<pair<string,string>> list;
    for(int r=0;r<ROWS;++r) for(int c=0;c<COLS;++c)
        if (seats[r][c]==TAKEN)
            list.push_back({names[r][c],
                           string()+COL_LETTERS[c]+to_string(r+1)});
    cout<<"Sort by Seat (S), Name (N), or Class (C): ";
    char opt = toupper(readLine()[0]);
    if (opt=='N') {
        sort(list.begin(), list.end(),
             [](auto &a, auto &b){ return a.first < b.first; });
    } else if (opt=='S') {
        sort(list.begin(), list.end(),
             [](auto &a, auto &b){ return a.second < b.second; });
    }
    cout<<"MANIFEST:\n";
    for (auto &p: list)
        cout<<p.first<<" - "<<p.second<<"\n";
}

// reassign or cancel any seat (employee use)
void reassignOrCancelAnySeat() {
    cout<<"Type C to cancel or R to reassign: ";
    char op = toupper(readLine()[0]);
    cout<<"Enter seat ID: "; string sid=readLine();
    auto [r,c]=parseSeatID(sid);
    if (r<0 || seats[r][c]==EMPTY) {
        cout<<"No reservation there.\n"; return;
    }
    string user = names[r][c];
    seats[r][c]=EMPTY; names[r][c].clear();
    if (op=='C') cout<<"Cancelled "<<sid<<" for "<<user<<".\n";
    else if (op=='R') {
        cout<<"Reassigning for "<<user<<".\n";
        manualChooseSeat(user);
    } else cout<<"Invalid option.\n";
    saveDataToFile();
}

// passenger menu loop
void passengerMenu(const string& user) {
    while (true) {
        cout<<"\n1) Show chart  2) Auto-choose  3) Manual"
            <<"  4) Change/Cancel  5) Boarding Pass  6) Quit\n";
        cout<<"Select (1-6): "; char c = readLine()[0];
        if (c=='1') displaySeatingChart();
        else if (c=='2') automaticChooseSeat(user);
        else if (c=='3') manualChooseSeat(user);
        else if (c=='4') changeOrCancelSeat(user);
        else if (c=='5') printBoardingPass(user);
        else if (c=='6') break;
        else cout<<"Invalid.\n";
    }
}

// employee menu loop
void employeeMenu() {
    cout<<"Enter employee username: "; string u=readLine();
    cout<<"Enter password: "; string p=readLine();
    if (u!="admin" || p!="password") {
        cout<<"Auth failed.\n"; return;
    }
    loadDataFromFile();
    while (true) {
        cout<<"\nE) Show chart  M) Manifest  L) Load"
            <<"  S) Save  R) Reassign/Cancel  Q) Quit\n";
        cout<<"Select: "; char c=toupper(readLine()[0]);
        if (c=='E') displaySeatingChart();
        else if (c=='M') printManifest();
        else if (c=='L') loadDataFromFile();
        else if (c=='S') saveDataToFile();
        else if (c=='R') reassignOrCancelAnySeat();
        else if (c=='Q') break;
        else cout<<"Invalid.\n";
    }
}

int main() {
    while (true) {
        char t = welcomeAndLogin();
        if (t=='Q') { cout<<"Goodbye!\n"; break; }
        if (t=='P') {
            cout<<"Enter name: "; string name=readLine();
            passengerMenu(name);
        } else {
            employeeMenu();
        }
    }
    return 0;
}
