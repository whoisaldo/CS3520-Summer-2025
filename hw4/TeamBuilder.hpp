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

struct Student {
    std::string username;
    int progSkill;        // 1 = beginner, 2 = intermediate, 3 = advanced
    int debugSkill;       // same scale
    int designSkill;      // same scale
    std::vector<std::string> wantList;     // usernames separated by ':'
    std::vector<std::string> dontWantList; // usernames separated by ':'
};

void readRosterFromCSV(const std::string& filename,
                       std::vector<Student>& allStudents,
                       std::unordered_map<std::string, Student*>& lookupByName);

void buildTeamsByPreference(const std::vector<Student>& allStudents,
                            const std::unordered_map<std::string, Student*>& lookupByName,
                            std::vector<std::vector<Student*>>& teams);

void buildTeamsBySkillBalance(std::vector<Student>& allStudents,
                              std::vector<std::vector<Student*>>& teams);

void computeAndPrintTeamScores(const std::vector<std::vector<Student*>>& teams);

void writeTeamsToCSV(const std::vector<std::vector<Student*>>& teams,
                     const std::string& outputFilename);

#endif // TEAMBUILDER_HPP

