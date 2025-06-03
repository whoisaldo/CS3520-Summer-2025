// Tleis.al@northeastern.edu
// Ali Tleis
// Younes.al@northeastern.edu
// Ali Younes 6/3/2025
// CS3520 course

#ifndef TEAMBUILDER_HPP
#define TEAMBUILDER_HPP

#include <string>
#include <vector>
#include <unordered_map>

// Student definition
struct Student {
    std::string username;
    int progSkill;        // 1 = beginner, 2 = intermediate, 3 = advanced
    int debugSkill;       // same scale
    int designSkill;      // same scale
    std::vector<std::string> wantList;     // usernames separated by ':'
    std::vector<std::string> dontWantList; // usernames separated by ':'
};

// Read CSV into allStudents and build lookupByName
void readRosterFromCSV(const std::string &filename,
                       std::vector<Student> &allStudents,
                       std::unordered_map<std::string, Student*> &lookupByName);

// Build teams honoring “want to work with” first
void buildTeamsByPreference(const std::vector<Student> &allStudents,
                            const std::unordered_map<std::string, Student*> &lookupByName,
                            std::vector<std::vector<Student*>> &teams);

// Build skill-balanced teams
void buildTeamsBySkillBalance(std::vector<Student> &allStudents,
                              std::vector<std::vector<Student*>> &teams);

// Print each team’s total skill scores
void computeAndPrintTeamScores(const std::vector<std::vector<Student*>> &teams);

// Write teams to a CSV file
void writeTeamsToCSV(const std::vector<std::vector<Student*>> &teams,
                     const std::string &outputFilename);

#endif // TEAMBUILDER_HPP

