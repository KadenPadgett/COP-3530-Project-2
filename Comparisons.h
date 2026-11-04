//
// Created by kaden on 11/4/26.
//
#ifndef COP_3530_PROJECT_2_COMPARISONS_H
#define COP_3530_PROJECT_2_COMPARISONS_H

#include "Songs.h"

using songCompare = bool (*)(const Songs&, const Songs&);

inline bool byId(const Songs& a, const Songs& b) {
    return a.id < b.id;
}

inline bool byName(const Songs& a, const Songs& b) {
    return a.name < b.name;
}

inline bool byArtist(const Songs& a, const Songs& b) {
    return a.artist < b.artist;
}

inline bool byDuration(const Songs& a, const Songs& b) {
    return a.duration_ms < b.duration_ms;
}

inline bool byYear(const Songs& a, const Songs& b) {
    return a.year < b.year;
}

inline bool byPopularity(const Songs& a, const Songs& b) {
    return a.popularity < b.popularity;
}

inline bool byAcousticness(const Songs& a, const Songs& b) {
    return a.acousticness < b.acousticness;
}

inline bool byDanceability(const Songs& a, const Songs& b) {
    return a.danceability < b.danceability;
}

inline bool byEnergy(const Songs& a, const Songs& b) {
    return a.energy < b.energy;
}

inline bool byInstrumentalness(const Songs& a, const Songs& b) {
    return a.instrumentalness < b.instrumentalness;
}

inline bool byLiveness(const Songs& a, const Songs& b) {
    return a.liveness < b.liveness;
}

inline bool byLoudness(const Songs& a, const Songs& b) {
    return a.loudness < b.loudness;
}

inline bool bySpeechiness(const Songs& a, const Songs& b) {
    return a.speechiness < b.speechiness;
}

inline bool byTempo(const Songs& a, const Songs& b) {
    return a.tempo < b.tempo;
}

inline bool byValence(const Songs& a, const Songs& b) {
    return a.valence < b.valence;
}
#endif //COP_3530_PROJECT_2_COMPARISONS_H
