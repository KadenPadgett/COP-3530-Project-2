//
// Created by kaden on 11/4/26.
//
#ifndef COP_3530_PROJECT_2_LOADSONGS_H
#define COP_3530_PROJECT_2_LOADSONGS_H

#include "Songs.h"
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

inline void parseRow(const std::string& line, std::vector<std::string>& values) {
    values.clear();
    std::string value;
    bool inQuotes = false;
    for (std::size_t i = 0; i < line.size(); ++i) {
        char ch = line[i];
        if (ch == '"') {
            if (inQuotes && i + 1 < line.size() && line[i + 1] == '"') {
                value += '"';
                ++i;
            } else {
                inQuotes = !inQuotes;
            }
        } else if (ch == ',' && !inQuotes) {
            values.push_back(value);
            value.clear();
        } else {
            value += ch;
        }
    }
    values.push_back(value);
}


inline std::vector<Songs> loadSongs(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Cannot open " + path);
    }
    std::vector<std::string> header;
    std::string line;
    std::getline(file, line);
    parseRow(line, header);
    auto column = [&](const std::string& name) {
        return std::find(header.begin(), header.end(), name) - header.begin();
    };
    const auto id = column("id");
    const auto name = column("name");
    const auto artists = column("artists");
    const auto duration_ms = column("duration_ms");
    const auto year = column("year");
    const auto acousticness = column("acousticness");
    const auto danceability = column("danceability");
    const auto energy = column("energy");
    const auto instrumentalness = column("instrumentalness");
    const auto liveness = column("liveness");
    const auto loudness = column("loudness");
    const auto speechiness = column("speechiness");
    const auto tempo = column("tempo");
    const auto valence = column("valence");
    const auto popularity = column("popularity");

    std::vector<Songs> songs;
    std::vector<std::string> row;
    while (std::getline(file, line)) {
        parseRow(line, row);
        Songs song;
        song.id = row[id];
        song.name = row[name];
        song.artist = row[artists];
        song.duration_ms = std::stoi(row[duration_ms]);
        song.year = std::stoi(row[year]);
        song.acousticness = std::stod(row[acousticness]);
        song.danceability = std::stod(row[danceability]);
        song.energy = std::stod(row[energy]);
        song.instrumentalness = std::stod(row[instrumentalness]);
        song.liveness = std::stod(row[liveness]);
        song.loudness = std::stod(row[loudness]);
        song.speechiness = std::stod(row[speechiness]);
        song.tempo = std::stod(row[tempo]);
        song.valence = std::stod(row[valence]);
        song.popularity = std::stoi(row[popularity]);
        songs.push_back(std::move(song));
        }
    return songs;
}


#endif //COP_3530_PROJECT_2_LOADSONGS_H

