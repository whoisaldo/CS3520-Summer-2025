// Tleis.al@northeastern.edu
// Ali Tleis
// Younes.al@northeastern.edu
// Ali Younes 6/3/2025
// CS3520 course

#include "TeamBuilder.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <climits>
#include <string>
#include <cctype>

// convert text levels to integers
static int textToSkill(const std::string& t) {
    std::string lower;
    for (char c : t) lower.push_back(std::tolower(c));
    if (lower == "beginner")     return 1;
    if (lower == "intermediate") return 2;
    if (lower == "advanced")     return 3;
    try {
        return std::stoi(t);
    } catch (...) {
        return 1;
    }
}

void readRosterFromCSV(const std::string& filename,
                       std::vector<Student>& allStudents,
                       std::unordered_map<std::string, Student*>& lookupByName) {
    std::ifstream fin(filename);
    if (!fin) return;

    std::string line;
    std::getline(fin, line);

    while (std::getline(fin, line)) {
        std::stringstream ss(line);
        std::string username, progStr, debugStr, designStr;
        std::string dontWantStr, wantStr;

        std::getline(ss, username, ',');
        std::getline(ss, progStr, ',');
        std::getline(ss, debugStr, ',');
        std::getline(ss, designStr, ',');
        std::getline(ss, dontWantStr, ',');
        std::getline(ss, wantStr, ',');

        Student s;
        s.username    = username;
        s.progSkill   = textToSkill(progStr);
        s.debugSkill  = textToSkill(debugStr);
        s.designSkill = textToSkill(designStr);

        {
            std::stringstream ss2(dontWantStr);
            std::string token;
            while (std::getline(ss2, token, ':')) {
                if (!token.empty()) s.dontWantList.push_back(token);
            }
        }
        {
            std::stringstream ss3(wantStr);
            std::string token;
            while (std::getline(ss3, token, ':')) {
                if (!token.empty()) s.wantList.push_back(token);
            }
        }

        allStudents.push_back(s);
        lookupByName[s.username] = &allStudents.back();
    }

    fin.close();
}

static int indexOfStudent(const std::vector<Student>& allStudents, const Student* ptr) {
    for (int i = 0; i < (int)allStudents.size(); ++i) {
        if (&allStudents[i] == ptr) return i;
    }
    return -1;
}

void buildTeamsByPreference(const std::vector<Student>& allStudents,
                            const std::unordered_map<std::string, Student*>& lookupByName,
                            std::vector<std::vector<Student*>>& teams) {
    int N = allStudents.size();
    std::vector<bool> assigned(N, false);
    teams.clear();

    for (int i = 0; i < N; ++i) {
        if (assigned[i]) continue;
        Student* me = const_cast<Student*>(&allStudents[i]);

        for (const auto& wantedName : me->wantList) {
            auto it = lookupByName.find(wantedName);
            if (it == lookupByName.end()) continue;
            Student* other = it->second;

            int j = indexOfStudent(allStudents, other);
            if (j < 0 || assigned[j]) continue;

            bool conflict = false;
            for (auto& x : me->dontWantList) {
                if (x == other->username) { conflict = true; break; }
            }
            if (conflict) continue;
            for (auto& x : other->dontWantList) {
                if (x == me->username) { conflict = true; break; }
            }
            if (conflict) continue;

            std::vector<Student*> team;
            team.push_back(me);
            team.push_back(other);
            assigned[i] = true;
            assigned[j] = true;

            for (int k = 0; k < N && (int)team.size() < 4; ++k) {
                if (assigned[k]) continue;
                Student* candidate = const_cast<Student*>(&allStudents[k]);

                bool canJoin = true;
                for (auto* member : team) {
                    for (auto& bad : member->dontWantList) {
                        if (bad == candidate->username) { canJoin = false; break; }
                    }
                    if (!canJoin) break;
                    for (auto& bad : candidate->dontWantList) {
                        if (bad == member->username) { canJoin = false; break; }
                    }
                    if (!canJoin) break;
                }
                if (canJoin) {
                    team.push_back(candidate);
                    assigned[k] = true;
                }
            }

            teams.push_back(team);
            break;
        }
    }

    for (int i = 0; i < N; ++i) {
        if (assigned[i]) continue;
        Student* me = const_cast<Student*>(&allStudents[i]);
        bool placed = false;

        for (auto& team : teams) {
            if ((int)team.size() >= 4) continue;

            bool conflict = false;
            for (auto* member : team) {
                for (auto& bad : member->dontWantList) {
                    if (bad == me->username) { conflict = true; break; }
                }
                if (conflict) break;
                for (auto& bad : me->dontWantList) {
                    if (bad == member->username) { conflict = true; break; }
                }
                if (conflict) break;
            }
            if (!conflict) {
                team.push_back(me);
                assigned[i] = true;
                placed = true;
                break;
            }
        }

        if (!placed) {
            std::vector<Student*> newTeam;
            newTeam.push_back(me);
            assigned[i] = true;
            teams.push_back(newTeam);
        }
    }
}

static bool compareBySkills(const Student& a, const Student& b) {
    if (a.progSkill != b.progSkill) return a.progSkill > b.progSkill;
    if (a.designSkill != b.designSkill) return a.designSkill > b.designSkill;
    return a.debugSkill > b.debugSkill;
}

void buildTeamsBySkillBalance(std::vector<Student>& allStudents,
                              std::vector<std::vector<Student*>>& teams) {
    int N = allStudents.size();
    std::sort(allStudents.begin(), allStudents.end(), compareBySkills);

    int numTeams = static_cast<int>(std::ceil(N / 4.0));
    teams.clear();
    teams.resize(numTeams);

    std::vector<bool> assigned(N, false);
    int teamIdx = 0;

    for (int i = 0; i < N; ++i) {
        if (assigned[i]) continue;
        if ((int)teams[teamIdx].size() >= 4) {
            teamIdx = (teamIdx + 1) % numTeams;
            --i;
            continue;
        }

        bool conflict = false;
        for (auto* member : teams[teamIdx]) {
            for (auto& bad : member->dontWantList) {
                if (bad == allStudents[i].username) { conflict = true; break; }
            }
            if (conflict) break;
            for (auto& bad : allStudents[i].dontWantList) {
                if (bad == member->username) { conflict = true; break; }
            }
            if (conflict) break;
        }
        if (!conflict) {
            teams[teamIdx].push_back(&allStudents[i]);
            assigned[i] = true;
            teamIdx = (teamIdx + 1) % numTeams;
        }
    }

    for (int i = 0; i < N; ++i) {
        if (assigned[i]) continue;
        Student* candidate = &allStudents[i];

        int bestTeam = -1;
        int lowestSum = INT_MAX;
        for (int t = 0; t < numTeams; ++t) {
            if ((int)teams[t].size() >= 4) continue;

            bool conflict = false;
            for (auto* member : teams[t]) {
                for (auto& bad : member->dontWantList) {
                    if (bad == candidate->username) { conflict = true; break; }
                }
                if (conflict) break;
                for (auto& bad : candidate->dontWantList) {
                    if (bad == member->username) { conflict = true; break; }
                }
                if (conflict) break;
            }
            if (conflict) continue;

            int sum = 0;
            for (auto* member : teams[t]) {
                sum += member->progSkill + member->designSkill + member->debugSkill;
            }
            if (sum < lowestSum) {
                lowestSum = sum;
                bestTeam = t;
            }
        }

        if (bestTeam >= 0) {
            teams[bestTeam].push_back(candidate);
            assigned[i] = true;
        } else {
            bool placed = false;
            for (int t = 0; t < numTeams; ++t) {
                if ((int)teams[t].size() == 3) {
                    teams[t].push_back(candidate);
                    assigned[i] = true;
                    placed = true;
                    break;
                }
            }
            if (!placed) {
                std::vector<Student*> newTeam;
                newTeam.push_back(candidate);
                assigned[i] = true;
                teams.push_back(newTeam);
            }
        }
    }
}

void computeAndPrintTeamScores(const std::vector<std::vector<Student*>>& teams) {
    for (int t = 0; t < (int)teams.size(); ++t) {
        int sumProg = 0, sumDebug = 0, sumDesign = 0;
        for (auto* s : teams[t]) {
            sumProg   += s->progSkill;
            sumDebug  += s->debugSkill;
            sumDesign += s->designSkill;
        }
        std::cout << "Team " << (t + 1)
                  << " Scores: { Programming = " << sumProg
                  << ", Debugging = " << sumDebug
                  << ", Design = " << sumDesign << " }\n";
    }
}

void writeTeamsToCSV(const std::vector<std::vector<Student*>>& teams,
                     const std::string& outputFilename) {
    std::ofstream fout(outputFilename);
    if (!fout) return;

    fout << "GroupNumber,Member1,Member2,Member3,Member4\n";
    for (int t = 0; t < (int)teams.size(); ++t) {
        fout << (t + 1);
        for (int j = 0; j < 4; ++j) {
            if (j < (int)teams[t].size()) {
                fout << "," << teams[t][j]->username;
            } else {
                fout << ",";
            }
        }
        fout << "\n";
    }

    fout.close();
}

