#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int knapsack(int capacity, const vector<int>& weights, const vector<int>& values) {
    int n = weights.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (weights[i - 1] <= w) {
                dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]],
                               dp[i - 1][w]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    return dp[n][capacity];
}

int main() {
    int n, capacity;
    cout << "Enter number of items: ";
    if (!(cin >> n) || n <= 0) {
        cout << "Invalid number of items.\n";
        return 1;
    }
    cout << "Enter knapsack capacity: ";
    if (!(cin >> capacity) || capacity < 0) {
        cout << "Invalid capacity.\n";
        return 1;
    }
    vector<int> weights(n), values(n);
    cout << "Enter weights of items: ";
    for (int i = 0; i < n; i++) {
        if (!(cin >> weights[i]) || weights[i] < 0) {
            cout << "Invalid weight.\n";
            return 1;
        }
    }
    cout << "Enter values of items: ";
    for (int i = 0; i < n; i++) {
        if (!(cin >> values[i]) || values[i] < 0) {
            cout << "Invalid value.\n";
            return 1;
        }
    }
    int maxValue = knapsack(capacity, weights, values);
    cout << "Maximum value in knapsack = " << maxValue << "\n";
    return 0;
}
