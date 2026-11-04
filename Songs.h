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
    double acousticness;
    double danceability;
    double energy;
    double instrumentalness;
    double liveness;
    double loudness;
    double speechiness;
    double tempo;
    double valence;
    int popularity;
};
#endif //COP_3530_PROJECT_2_SONGS_H
