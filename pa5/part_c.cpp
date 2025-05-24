// Group Members:
// Younes.al@northeastern.edu    Ali Younes
// Tleis.A@northeastern.edu      Ali Tleis

#include <iostream>
#include <string>
using namespace std;

// Episode struct as before
struct tv_episode {
    char episode_name[30];
    int episode_number;
    string episode_release_date;
    double episode_rating;
};

// Season struct dynamically allocated now
struct season {
    int season_number;
    tv_episode* episodes;  // Pointer to dynamically allocated array of episodes
};

// TV series struct with dynamic seasons
struct tv_series {
    char* series_name;
    int first_release_year;
    int first_release_month;
    season* seasons_ptr;   // Pointer to dynamically allocated array of seasons
    int num_seasons;
};

int main() {
    // Dynamically allocate tv_series on the stack (not a pointer for simplicity)
    tv_series my_series;

    // Initialize basic info
    my_series.series_name = (char*)"House";
    my_series.first_release_year = 2004;
    my_series.first_release_month = 11;
    my_series.num_seasons = 3;

    // Dynamically allocate array of seasons
    my_series.seasons_ptr = new season[my_series.num_seasons];

    // For each season, dynamically allocate 7 episodes and initialize data
    for (int i = 0; i < my_series.num_seasons; i++) {
        my_series.seasons_ptr[i].season_number = i + 1;

        // Allocate episodes dynamically
        my_series.seasons_ptr[i].episodes = new tv_episode[7];

        for (int j = 0; j < 7; j++) {
            // Initialize episode name using snprintf for char array
            snprintf(my_series.seasons_ptr[i].episodes[j].episode_name, 30, "Episode %d", j + 1);

            my_series.seasons_ptr[i].episodes[j].episode_number = j + 1;

            // Release date string example
            my_series.seasons_ptr[i].episodes[j].episode_release_date =
                "2004-11-" + to_string(j + 1 + (i * 7));

            // Example rating increasing by 0.2 per episode
            my_series.seasons_ptr[i].episodes[j].episode_rating = 7.0 + (j * 0.2);
        }
    }

    // Print the data using pointer and arrow notation
    cout << "Series: " << my_series.series_name << endl;
    cout << "First Released: " << my_series.first_release_year << "-" << my_series.first_release_month << endl << endl;

    for (int i = 0; i < my_series.num_seasons; i++) {
        cout << "Season " << my_series.seasons_ptr[i].season_number << ":" << endl;

        for (int j = 0; j < 7; j++) {
            cout << "  Episode " << my_series.seasons_ptr[i].episodes[j].episode_number
                 << " - " << my_series.seasons_ptr[i].episodes[j].episode_name
                 << ", Release Date: " << my_series.seasons_ptr[i].episodes[j].episode_release_date
                 << ", Rating: " << my_series.seasons_ptr[i].episodes[j].episode_rating
                 << endl;
        }
        cout << endl;
    }

    // Free dynamically allocated memory
    for (int i = 0; i < my_series.num_seasons; i++) {
        delete[] my_series.seasons_ptr[i].episodes;  // Delete each episodes array
    }
    delete[] my_series.seasons_ptr;  // Delete seasons array

    return 0;
}

