#ifndef COP_3530_PROJECT_2_SONGS_H
#define COP_3530_PROJECT_2_SONGS_H
#include <string>


class Songs {
    public:
    std::string id;
    std::string name;
    std::string artist;
    int duration_ms;
    int year;
    int acousticness;
    int danceability;
    int energy;
    int instrumentalness;
    int liveness;
    int loudness;
    int speechiness;
    int tempo;
    int valence;
    int popularity;

};
#endif //COP_3530_PROJECT_2_SONGS_H
