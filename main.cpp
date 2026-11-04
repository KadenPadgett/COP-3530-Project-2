#include "LoadSongs.h"
#include "Comparisons.h"

void mergeSort(std::vector<Songs>& songs, int left, int right, songCompare compare);

int main() {
    // Example usage of the file read and merge sort usage. Can return the values in the song
    // vector after mergesort and it will be lowest to highest energy
    auto songs= loadSongs("Data/data.csv");
    if (songs.empty()) return 0;

    mergeSort(songs, 0, static_cast<int>(songs.size()) - 1, byEnergy);

}