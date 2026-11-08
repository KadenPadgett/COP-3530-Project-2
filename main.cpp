#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Browser.H>
#include <FL/fl_ask.H>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <stdexcept>
#include <chrono>
#include <cmath>
#include "Songs.h"
#include "Comparisons.h"
#include "LoadSongs.h"
using namespace std;

void mergeSort(vector<Songs>& songs, int left, int right, songCompare compare);
void heapSort(vector<Songs>& songs, songCompare compare);
struct AppData{
    vector<Songs>* songs;
    Fl_Choice* metricChoice;
    Fl_Choice* algorithmChoice;
    Fl_Choice* orderChoice;
    Fl_Input* numberInput;
    Fl_Input* minInput;
    Fl_Input* maxInput;
    Fl_Browser* results;
    Fl_Box* status;
    Fl_Box* performance;
};
songCompare getComparator(int choice){
    switch (choice){
        case 0: return byName;
        case 1: return byArtist;
        case 2: return byYear;
        case 3: return byPopularity;
        case 4: return byDuration;
        case 5: return byLoudness;
        case 6: return byEnergy;
        case 7: return byDanceability;
        case 8: return byTempo;
        case 9: return byAcousticness;
        case 10: return byInstrumentalness;
        case 11: return byLiveness;
        case 12: return bySpeechiness;
        case 13: return byValence;
        case 14: return byId;
        default: return byPopularity;
    }
}
double getMetricValue(const Songs& song, int choice){
    switch (choice){
        case 2: return song.year;
        case 3: return song.popularity;
        case 4: return song.duration_ms;
        case 5: return song.loudness;
        case 6: return song.energy;
        case 7: return song.danceability;
        case 8: return song.tempo;
        case 9: return song.acousticness;
        case 10: return song.instrumentalness;
        case 11: return song.liveness;
        case 12: return song.speechiness;
        case 13: return song.valence;
        default: return 0;
    }
}
bool isNumericMetric(int choice){
    return choice >= 2 && choice <= 13;
}
string formatDuration(int milliseconds){
    int totalSeconds = milliseconds / 1000;
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;
    ostringstream output;
    output << minutes << ":"<< setw(2) << setfill('0') << seconds;
    return output.str();
}
string getMetricName(int choice){
    const string names[] = {
        "Song Title",
        "Artist",
        "Year",
        "Popularity",
        "Duration",
        "Loudness",
        "Energy",
        "Danceability",
        "Tempo",
        "Acousticness",
        "Instrumentalness",
        "Liveness",
        "Speechiness",
        "Valence",
        "ID"
    };
    return names[choice];
}
bool parseNumber(const char* input, double& value){
    if (input[0] == '\0') {
        return false;
    }
    char* end;
    value = strtod(input, &end);
    if (end == input || *end != '\0' || !isfinite(value)){
        throw runtime_error("Please enter valid numeric filter values.");
    }
    return true;
}
void searchCallback(Fl_Widget*, void* data){
    AppData* app = static_cast<AppData*>(data);
    char* end;
    long n = strtol(app->numberInput->value(), &end, 10);
    if (app->numberInput->value()[0] == '\0' ||*end != '\0' || n <= 0) {
        fl_alert("Please enter a valid positive number.");
        return;
    }
    if (app->songs->empty()) {
        fl_alert("The music dataset is empty.");
        return;
    }
    int metric = app->metricChoice->value();
    int algorithm = app->algorithmChoice->value();
    int order = app->orderChoice->value();
    double minValue = 0;
    double maxValue = 0;
    bool hasMin = false;
    bool hasMax = false;
    try {
        hasMin = parseNumber(app->minInput->value(), minValue);
        hasMax = parseNumber(app->maxInput->value(), maxValue);
    }
    catch (const exception& e) {
        fl_alert("%s", e.what());
        return;
    }
    if ((hasMin || hasMax) && !isNumericMetric(metric)) {
        fl_alert("Range filtering requires a numeric attribute.");
        return;
    }
    if (hasMin && hasMax && minValue > maxValue) {
        fl_alert("Minimum value cannot exceed maximum value.");
        return;
    }
    vector<Songs> sortedSongs = *app->songs;
    if (hasMin || hasMax){
        vector<Songs> filteredSongs;
        for (const Songs& song : sortedSongs){
            double value = getMetricValue(song, metric);
            if ((!hasMin || value >= minValue) &&(!hasMax || value <= maxValue)) {
                filteredSongs.push_back(song);
            }
        }
        sortedSongs = move(filteredSongs);
    }
    if (sortedSongs.empty()){
        app->results->clear();
        app->status->copy_label("No songs match your selected filters.");
        app->performance->copy_label("No sorting performed.");
        app->status->redraw();
        app->performance->redraw();
        return;
    }
    songCompare compare = getComparator(metric);
    auto start = chrono::high_resolution_clock::now();
    if (algorithm == 0) {
        mergeSort(sortedSongs,0,static_cast<int>(sortedSongs.size()) - 1,compare);
    }
    else {
        heapSort(sortedSongs, compare);
    }
    auto finish = chrono::high_resolution_clock::now();
    double elapsedTime = chrono::duration<double, milli>(finish - start).count();
    if (order == 1){reverse(sortedSongs.begin(), sortedSongs.end());}
    app->results->clear();
    int count = static_cast<int>(min(n, static_cast<long>(sortedSongs.size())));
    for (int i = 0; i < count; i++){
        const Songs& song = sortedSongs[i];
        ostringstream output;
        output << i + 1 << ".  "<< song.name<< "  |  "<< song.artist<< "  |  ";
        if (metric == 0){
            output << "Song Title: " << song.name;
        }
        else if (metric == 1){
            output << "Artist: " << song.artist;
        }
        else if (metric == 14){
            output << "ID: " << song.id;
        }
        else if (metric == 4){
            output << "Duration: "<< formatDuration(song.duration_ms);
        }
        else {
            output << getMetricName(metric) << ": "<< fixed << setprecision(2)<< getMetricValue(song, metric);
        }
        app->results->add(output.str().c_str());
    }
    string message ="Displaying " + to_string(count) +" of " + to_string(sortedSongs.size()) +" matching songs.";
    app->status->copy_label(message.c_str());
    string algorithmName = (algorithm == 0) ? "Merge Sort" : "Heap Sort";
    ostringstream stats;
    stats << "Algorithm: " << algorithmName<< "  |  Songs sorted: " << sortedSongs.size()<< "  |  Songs displayed: " << count<< "  |  Sorting time: "<< fixed << setprecision(3)<< elapsedTime << " ms";
    app->performance->copy_label(stats.str().c_str());
    app->status->redraw();
    app->performance->redraw();
}
int main() {
    vector<Songs> songs;
    try {
        songs = loadSongs("Data/data.csv");
    }
    catch (const exception& e){
        fl_alert("Could not load dataset:\n%s", e.what());
        return 1;
    }
    Fl_Window window(900, 750, "MusicMetric");
    Fl_Box title(20, 15, 860, 45,"MusicMetric - Spotify Music Discovery");
    title.labelfont(FL_BOLD);
    title.labelsize(25);
    Fl_Box subtitle(20, 60, 860, 30,"Find songs based on their musical attributes");
    Fl_Box metricLabel(30, 125, 140, 30, "Sort by attribute:");
    Fl_Choice metricChoice(180, 125, 240, 35);
    metricChoice.add("Song Title");
    metricChoice.add("Artist");
    metricChoice.add("Year");
    metricChoice.add("Popularity");
    metricChoice.add("Duration");
    metricChoice.add("Loudness");
    metricChoice.add("Energy");
    metricChoice.add("Danceability");
    metricChoice.add("Tempo");
    metricChoice.add("Acousticness");
    metricChoice.add("Instrumentalness");
    metricChoice.add("Liveness");
    metricChoice.add("Speechiness");
    metricChoice.add("Valence");
    metricChoice.add("ID");
    metricChoice.value(5);
    Fl_Box algorithmLabel(470, 125, 140, 30, "Sorting algorithm:");
    Fl_Choice algorithmChoice(620, 125, 240, 35);
    algorithmChoice.add("Merge Sort");
    algorithmChoice.add("Heap Sort");
    algorithmChoice.value(0);
    Fl_Box numberLabel(30, 185, 140, 30, "Number of songs (N):");
    Fl_Input numberInput(180, 185, 240, 35);
    numberInput.value("10");
    Fl_Box orderLabel(470, 185, 140, 30, "Sorting order:");
    Fl_Choice orderChoice(620, 185, 240, 35);
    orderChoice.add("Ascending");
    orderChoice.add("Descending");
    orderChoice.value(1);
    Fl_Box minLabel(30, 235, 100, 30, "Minimum value:");
    Fl_Input minInput(140, 235, 130, 35);
    minInput.value("");
    Fl_Box maxLabel(300, 235, 100, 30, "Maximum value:");
    Fl_Input maxInput(410, 235, 130, 35);
    maxInput.value("");
    Fl_Button searchButton(620, 232, 240, 40,"Find Songs");
    Fl_Box resultsLabel(30, 295, 840, 30,"Search Results");
    resultsLabel.labelfont(FL_BOLD);
    resultsLabel.labelsize(18);
    Fl_Browser results(30, 335, 840, 300);
    Fl_Box status(30, 650, 840, 25,"Ready. Select your search options.");
    Fl_Box performance(30, 685, 840, 35,"Sorting statistics will appear here.");
    AppData app = {&songs,&metricChoice,&algorithmChoice,&orderChoice,&numberInput,&minInput,&maxInput,&results,&status,&performance
    };
    searchButton.callback(searchCallback, &app);
    window.end();
    window.show();
    return Fl::run();
}