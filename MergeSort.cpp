#pragma once
#include <vector>

void merge(std::vector<int>& songs, int left, int mid, int right) {
    int leftSize = mid - left + 1;
    int rightSize = right - mid;

    std::vector<int> leftSongs(leftSize);
    std::vector<int> rightSongs(rightSize);

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
        if (leftSongs[i] <= rightSongs[j]) {
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

void mergeSort(std::vector<int>& songs, int left, int right) {
    if (left >= right) {
        return;
    }
    int mid = left + (right - left) / 2;

    mergeSort(songs, left, mid);
    mergeSort(songs, mid + 1, right);

    merge(songs, left, mid, right);
}