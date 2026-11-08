#include "Songs.h"
#include "Comparisons.h"
#include <vector>
#include <utility>
using namespace std;
void heapify(vector<Songs>& songs, int heapSize, int i, songCompare compare) {
    while (true) {
        int large = i;
        int leftchild= 2*i+1;
        int rightchild = 2*i+2;
        if (leftchild<heapSize&& compare(songs[large], songs[leftchild])) {
            large = leftchild;
        }
        if (rightchild<heapSize&& compare(songs[large], songs[rightchild])) {
            large = rightchild;
        }
        if (large==i){return;}
        swap(songs[i], songs[large]);
        i=large;
    }
}
void heapSort(vector<Songs>& songs, songCompare compare) {
    int n = static_cast<int>(songs.size());
    for (int i = n/2-1;i>=0; i--){heapify(songs, n, i, compare);}
    for (int end = n -1;end>0;end--) {
        swap(songs[0], songs[end]);
        heapify(songs, end, 0, compare);
    }
}