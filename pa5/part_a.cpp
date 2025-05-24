// Group Members:
// Younes.al@northeastern.edu    Ali Younes
// Tleis.A@northeastern.edu      Ali Tleis

#include <iostream>
#include <string>
using namespace std;

// Define the episode struct as given in the assignment
struct tv_episode {
    char episode_name[30];      // Name of the episode (max 30 chars)
    int episode_number;         // Episode number in the season
    string episode_release_date; // Release date as a string
    double episode_rating;      // Rating of the episode
};

// Define the tv series struct
struct tv_series {
    char* series_name;          // Pointer to the series name string
    int first_release_year;     // Year the series first released
    int first_release_month;    // Month the series first released
    // Define an anonymous struct for seasons with 7 episodes each
    struct {
        int season_number;      // Season number
        tv_episode episodes[7]; // Array of 7 episodes for the season
    } seasons[3];               // Array of 3 seasons
};

int main() {
    // Declare a statically allocated tv_series variable
    tv_series my_series;

    // Just a simple confirmation message that the struct was declared
    cout << "TV series struct declared successfully." << endl;

    return 0;
}

