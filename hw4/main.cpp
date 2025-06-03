// Tleis.al@northeastern.edu
// Ali Tleis
// Younes.al@northeastern.edu
// Ali Younes 6/3/2025
// CS3520 course

#include <iostream>
#include <vector>
#include <unordered_map>
#include "TeamBuilder.hpp"

int main() {
    std::string filename;
    std::cout << "Enter roster CSV filename: ";
    std::getline(std::cin, filename);

    std::vector<Student> allStudents;
    std::unordered_map<std::string, Student*> lookupByName;
    readRosterFromCSV(filename, allStudents, lookupByName);

    int mode = 0;
    std::cout << "Select team formation mode:\n";
    std::cout << "1: Honor student preferences first\n";
    std::cout << "2: Create skill-balanced teams\n";
    std::cout << "Enter 1 or 2: ";
    std::cin >> mode;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::vector<std::vector<Student*>> teams;
    if (mode == 1) {
        buildTeamsByPreference(allStudents, lookupByName, teams);
    } else {
        buildTeamsBySkillBalance(allStudents, teams);
    }

    computeAndPrintTeamScores(teams);
    writeTeamsToCSV(teams, "teams_output.csv");

    return 0;
}

