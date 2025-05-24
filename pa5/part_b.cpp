// Group Members:
// Younes.al@northeastern.edu    Ali Younes
// Tleis.A@northeastern.edu      Ali Tleis

#include <iostream>
#include <string>
using namespace std;

// Struct for individual episodes
struct tv_episode {
    char episode_name[30];        // Name of the episode (max 30 chars)
    int episode_number;           // Episode number within the season
    string episode_release_date;  // Release date as a string
    double episode_rating;        // Episode rating as a double
};

// Struct for TV series with seasons and episodes
struct tv_series {
    char* series_name;            // Pointer to series name string
    int first_release_year;       // Year series first released
    int first_release_month;      // Month series first released
    struct {
        int season_number;        // Season number
        tv_episode episodes[7];   // Array of 7 episodes per season
    } seasons[3];                 // Array of 3 seasons
};

int main() {
    // Declare a statically allocated TV series variable
    tv_series my_series;

    // Initialize basic series information
    my_series.series_name = (char*)"House";  
    my_series.first_release_year = 2004;
    my_series.first_release_month = 11;

    // Initialize all 3 seasons and their 7 episodes each
    for (int season = 0; season < 3; season++) {
        my_series.seasons[season].season_number = season + 1;  // Season 1, 2, 3

        for (int episode = 0; episode < 7; episode++) {
            // Set episode name like "Episode 1", "Episode 2", etc.
            snprintf(my_series.seasons[season].episodes[episode].episode_name, 30, "Episode %d", episode + 1);

            // Set episode number
            my_series.seasons[season].episodes[episode].episode_number = episode + 1;

            // Set a dummy release date string "2004-11-DD"
            my_series.seasons[season].episodes[episode].episode_release_date = 
                "2004-11-" + to_string(episode + 1 + (season * 7));

            // Set a sample rating from 7.0 up by 0.2 per episode
            my_series.seasons[season].episodes[episode].episode_rating = 7.0 + (episode * 0.2);
        }
    }

    // Print all data using array notation
    cout << "Series: " << my_series.series_name << endl;
    cout << "First Released: " << my_series.first_release_year << "-" << my_series.first_release_month << endl << endl;

    for (int season = 0; season < 3; season++) {
        cout << "Season " << my_series.seasons[season].season_number << ":" << endl;

        for (int episode = 0; episode < 7; episode++) {
            cout << "  Episode " << my_series.seasons[season].episodes[episode].episode_number
                 << " - " << my_series.seasons[season].episodes[episode].episode_name
                 << ", Release Date: " << my_series.seasons[season].episodes[episode].episode_release_date
                 << ", Rating: " << my_series.seasons[season].episodes[episode].episode_rating
                 << endl;
        }
        cout << endl;
    }

    return 0;
}

