#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

// ---------------- Naive Search ----------------
pair<vector<int>, int> naiveSearch(const string &text, const string &pattern) {
    int n = text.length();
    int m = pattern.length();

    if (m > n)
        return {{}, 0};

    vector<int> matches;
    int comparisons = 0;

    for (int i = 0; i <= n - m; i++) {
        int j = 0;

        while (j < m) {
            comparisons++;

            if (text[i + j] != pattern[j])
                break;

            j++;
        }

        if (j == m)
            matches.push_back(i);
    }

    return {matches, comparisons};
}

// ---------------- Compute LPS ----------------
vector<int> computeLPS(const string &pattern) {
    int m = pattern.length();
    vector<int> lps(m, 0);

    int len = 0;
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0)
                len = lps[len - 1];
            else {
                lps[i] = 0;
                i++;
            }
        }
    }

    return lps;
}

// ---------------- KMP Search ----------------
pair<vector<int>, int> kmpSearch(const string &text, const string &pattern) {
    int n = text.length();
    int m = pattern.length();

    if (m > n)
        return {{}, 0};

    vector<int> lps = computeLPS(pattern);
    vector<int> matches;

    int comparisons = 0;
    int i = 0, j = 0;

    while (i < n) {
        comparisons++;

        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            matches.push_back(i - j);
            j = lps[j - 1];
        }
        else if (i < n && pattern[j] != text[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }

    return {matches, comparisons};
}

// ---------------- Rabin-Karp ----------------
pair<vector<int>, int> rabinKarp(const string &text, const string &pattern, int q = 101) {
    int n = text.length();
    int m = pattern.length();

    if (m > n)
        return {{}, 0};

    const int d = 256;

    int h = 1;
    for (int i = 0; i < m - 1; i++)
        h = (h * d) % q;

    int pHash = 0, tHash = 0;

    vector<int> matches;
    int comparisons = 0;

    for (int i = 0; i < m; i++) {
        pHash = (d * pHash + pattern[i]) % q;
        tHash = (d * tHash + text[i]) % q;
    }

    for (int s = 0; s <= n - m; s++) {

        if (pHash == tHash) {
            bool flag = true;

            for (int k = 0; k < m; k++) {
                comparisons++;

                if (text[s + k] != pattern[k]) {
                    flag = false;
                    break;
                }
            }

            if (flag)
                matches.push_back(s);
        }

        if (s < n - m) {
            tHash = (d * (tHash - text[s] * h) + text[s + m]) % q;

            if (tHash < 0)
                tHash += q;
        }
    }

    return {matches, comparisons};
}

// ---------------- Random String ----------------
string randomString(int length) {
    string chars = "ABCD";
    string s;

    for (int i = 0; i < length; i++)
        s += chars[rand() % 4];

    return s;
}

// ---------------- Print Vector ----------------
void printVector(const vector<int> &v) {
    cout << "[";

    for (size_t i = 0; i < v.size(); i++) {
        cout << v[i];

        if (i != v.size() - 1)
            cout << ", ";
    }

    cout << "]";
}

// ---------------- Main ----------------
int main() {

    srand(0);   // Fixed seed for reproducible output

    string text = "AABAACAADAABAABA";
    string pattern = "AABA";

    cout << "Text: " << text << endl;
    cout << "Pattern: " << pattern << endl;

    auto naive = naiveSearch(text, pattern);
    auto kmp = kmpSearch(text, pattern);   // Fixed typo
    auto rk = rabinKarp(text, pattern);

    cout << "\nNaive -> Matches at: ";
    printVector(naive.first);
    cout << ", Comparisons: " << naive.second << endl;

    cout << "KMP -> Matches at: ";
    printVector(kmp.first);
    cout << ", Comparisons: " << kmp.second << endl;

    cout << "RK -> Matches at: ";
    printVector(rk.first);
    cout << ", Comparisons: " << rk.second << endl;

    // Performance Comparison
    string textLarge = randomString(10000);

    vector<string> patterns = {
        "AB",
        "ABCD",
        "ABCDAB",
        "ABCDABCD"
    };

    cout << "\n";
    cout << setw(12) << "Pattern"
         << setw(10) << "Naive"
         << setw(10) << "KMP"
         << setw(10) << "RK" << endl;

    cout << string(42, '-') << endl;

    for (const string &p : patterns) {

        auto n = naiveSearch(textLarge, p);
        auto k = kmpSearch(textLarge, p);
        auto r = rabinKarp(textLarge, p);

        cout << setw(12) << p
             << setw(10) << n.second
             << setw(10) << k.second
             << setw(10) << r.second
             << endl;
    }

    return 0;
}
