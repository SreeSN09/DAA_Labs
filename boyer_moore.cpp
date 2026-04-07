#include <iostream>
#include <string>
#include <vector>
#include <algorithm> 

#define NO_OF_CHARS 256 // ASCII character set size

using namespace std;


void badCharHeuristic(const string &pattern, vector<int> &badChar) {
    int m = pattern.size();
    // Initialize all occurrences as -1
    fill(badChar.begin(), badChar.end(), -1);

    // Fill the actual value of last occurrence of a character
    for (int i = 0; i < m; i++) {
        badChar[(unsigned char)pattern[i]] = i;
    }
}

// Boyer–Moore search using bad character heuristic
void boyerMooreSearch(const string &text, const string &pattern) {
    int n = text.size();
    int m = pattern.size();

    if (m == 0) {
        cout << "Pattern is empty. Nothing to search.\n";
        return;
    }
    if (n == 0) {
        cout << "Text is empty. No matches found.\n";
        return;
    }

    vector<int> badChar(NO_OF_CHARS);
    badCharHeuristic(pattern, badChar);

    int shift = 0; // shift of the pattern with respect to text
    bool found = false;

    while (shift <= (n - m)) {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[shift + j])
            j--;

        // If the pattern is present at current shift
        if (j < 0) {
            cout << "Pattern found at index " << shift << "\n";
            found = true;

            shift += (shift + m < n) ? m - badChar[(unsigned char)text[shift + m]] : 1;
        } else {
          
            shift += max(1, j - badChar[(unsigned char)text[shift + j]]);
        }
    }

    if (!found) {
        cout << "No match found.\n";
    }
}

int main() {
    string text, pattern;

    cout << "Enter text: ";
    getline(cin, text);

    cout << "Enter pattern: ";
    getline(cin, pattern);

    boyerMooreSearch(text, pattern);

    return 0;
}
