#include <iostream>
#include <vector>
#include <chrono>
#include <cstdio>

using namespace std;

// Static-like global variables to match Java's class fields
static int interpolationComparisons = 0;
static int binaryComparisons = 0;

int interpolationSearch(const vector<int>& arr, int key) {
    interpolationComparisons = 0;

    int low = 0;
    int high = arr.size() - 1;

    while (low <= high &&
           key >= arr[low] &&
           key <= arr[high]) {

        interpolationComparisons++;

        if (arr[low] == arr[high]) {
            if (arr[low] == key)
                return low;
            else
                return -1;
        }

        // Using long long to prevent integer overflow during multiplication
        int pos = low + static_cast<int>((static_cast<long long>(key - arr[low]) * (high - low)) 
                  / (arr[high] - arr[low]));

        if (arr[pos] == key) {
            return pos;
        }

        if (arr[pos] < key) {
            low = pos + 1;
        } else {
            high = pos - 1;
        }
    }

    return -1;
}

int binarySearch(const vector<int>& arr, int key) {
    binaryComparisons = 0;

    int low = 0;
    int high = arr.size() - 1;

    while (low <= high) {
        binaryComparisons++;

        int mid = low + (high - low) / 2;

        if (arr[mid] == key)
            return mid;

        if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}

int main() {
    vector<int> sizes = {1000, 5000, 10000, 50000, 100000};

    printf("%-10s %-15s %-15s %-18s %-18s\n",
           "Size",
           "IS Time(ms)",
           "BS Time(ms)",
           "IS Comparisons",
           "BS Comparisons");

    for (int size : sizes) {
        vector<int> arr(size);

        // Uniformly distributed sorted array
        for (int i = 0; i < size; i++) {
            arr[i] = i * 2;
        }

        int key = arr[size - 1]; // search last element

        // Interpolation Search timing
        auto startIS = chrono::high_resolution_clock::now();
        interpolationSearch(arr, key);
        auto endIS = chrono::high_resolution_clock::now();
        
        // Convert to duration and get milliseconds as double
        double isTime = chrono::duration<double, std::milli>(endIS - startIS).count();
        int isComp = interpolationComparisons;

        // Binary Search timing
        auto startBS = chrono::high_resolution_clock::now();
        binarySearch(arr, key);
        auto endBS = chrono::high_resolution_clock::now();

        double bsTime = chrono::duration<double, std::milli>(endBS - startBS).count();
        int bsComp = binaryComparisons;

        printf("%-10d %-15.4f %-15.4f %-18d %-18d\n",
               size,
               isTime,
               bsTime,
               isComp,
               bsComp);
    }

    return 0;
}