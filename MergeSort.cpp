#include "Songs.h"
#include "Comparisons.h"
#include <vector>

void merge(std::vector<Songs>& songs, int left, int mid, int right, songCompare compare) {
    int leftSize = mid - left + 1;
    int rightSize = right - mid;

    std::vector<Songs> leftSongs(leftSize);
    std::vector<Songs> rightSongs(rightSize);

    for (int i = 0; i < leftSize; i++) {
        leftSongs[i] = songs[left + i];
    }

    for (int j = 0; j < rightSize; j++) {
        rightSongs[j] = songs[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < leftSize && j < rightSize) {
        if (compare(leftSongs[i], rightSongs[j])) {
            songs[k++] = leftSongs[i++];
        } else {
            songs[k++] = rightSongs[j++];
        }
    }

    while (i < leftSize) {
        songs[k++] = leftSongs[i++];
    }

    while (j < rightSize) {
        songs[k++] = rightSongs[j++];
    }
}

void mergeSort(std::vector<Songs>& songs, int left, int right, songCompare compare) {
    if (left >= right) {
        return;
    }
    int mid = left + (right - left) / 2;

    mergeSort(songs, left, mid, compare);
    mergeSort(songs, mid + 1, right, compare);

    merge(songs, left, mid, right, compare);
}