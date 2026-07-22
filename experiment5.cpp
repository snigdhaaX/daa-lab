#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

int comparison_count = 0;

// divide and conquer function
pair<int, int> minMaxDC(const vector<int> &arr, int low, int high)
{
    // Base case: single element
    if (low == high)
    {
        return {arr[low], arr[low]};
    }

    // Base case: two elements
    if (high == low + 1)
    {
        comparison_count++;
        if (arr[low] < arr[high])
            return {arr[low], arr[high]};
        else
            return {arr[high], arr[low]};
    }

    // Divide
    int mid = (low + high) / 2;

    pair<int, int> left = minMaxDC(arr, low, mid);
    pair<int, int> right = minMaxDC(arr, mid + 1, high);

    // Conquer
    comparison_count++;
    int overallMin = (left.first < right.first) ? left.first : right.first;

    comparison_count++;
    int overallMax = (left.second > right.second) ? left.second : right.second;

    return {overallMin, overallMax};
}

// Naive method
void minMaxNaive(const vector<int> &arr, int &mn, int &mx, int &comps)
{
    mn = arr[0];
    mx = arr[0];
    comps = 0;

    for (int i = 1; i < arr.size(); i++)
    {
        comps++;
        if (arr[i] < mn)
            mn = arr[i];

        comps++;
        if (arr[i] > mx)
            mx = arr[i];
    }
}

int main()
{
    srand(time(0));

    // Demonstration on small array
    vector<int> arr = {3, 1, 7, 4, 9, 2, 8, 5, 6, 0};

    comparison_count = 0;
    pair<int, int> result = minMaxDC(arr, 0, arr.size() - 1);
    int dc_comps = comparison_count;

    int mn, mx, naive_comps;
    minMaxNaive(arr, mn, mx, naive_comps);

    cout << "Array: [";
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i];
        if (i != arr.size() - 1)
            cout << ", ";
    }
    cout << "]" << endl;

    cout << "Min: " << result.first << ", Max: " << result.second << endl;
    cout << "D&C Comparisons: " << dc_comps << endl;
    cout << "Naive Comparisons: " << naive_comps << endl;

    // Performance Analysis
    cout << endl;
    cout << left << setw(8) << "Size"
         << setw(12) << "DC Comps"
         << setw(14) << "Naive Comps"
         << "Formula 3n/2-2" << endl;

    cout << "--------------------------------------------------------" << endl;

    vector<int> sizes = {10, 100, 1000, 10000};

    for (int size : sizes)
    {
        vector<int> testArr(size);

        for (int i = 0; i < size; i++)
            testArr[i] = rand() % 10000 + 1;

        comparison_count = 0;
        result = minMaxDC(testArr, 0, testArr.size() - 1);
        int dc = comparison_count;

        minMaxNaive(testArr, mn, mx, naive_comps);

        int formula = (3 * size) / 2 - 2;

        cout << left << setw(8) << size
             << setw(12) << dc
             << setw(14) << naive_comps
             << formula << endl;
    }

    return 0;
}
