#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

// Function to calculate the total cost of a given route
int calculateCost(const vector<vector<int>>& graph, const vector<int>& path) {
    int cost = 0;
    for (size_t i = 0; i < path.size() - 1; i++) {
        cost += graph[path[i]][path[i + 1]];
    }
    // Return to starting point
    cost += graph[path.back()][path[0]];
    return cost;
}

int main() {
    int n;
    cout << "Enter number of cities: ";
    if (!(cin >> n) || n <= 1) {
        cerr << "Invalid number of cities. Must be > 1.\n";
        return 1;
    }

    vector<vector<int>> graph(n, vector<int>(n));
    cout << "Enter the cost matrix (" << n << "x" << n << "):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!(cin >> graph[i][j]) || graph[i][j] < 0) {
                cerr << "Invalid input. Costs must be non-negative integers.\n";
                return 1;
            }
        }
    }

    // Create a list of cities excluding the starting city (0)
    vector<int> cities;
    for (int i = 1; i < n; i++) {
        cities.push_back(i);
    }

    int minCost = numeric_limits<int>::max();
    vector<int> bestPath;

    // Try all permutations of the cities
    do {
        vector<int> currentPath = {0}; // Start from city 0
        currentPath.insert(currentPath.end(), cities.begin(), cities.end());
        int currentCost = calculateCost(graph, currentPath);

        if (currentCost < minCost) {
            minCost = currentCost;
            bestPath = currentPath;
        }
    } while (next_permutation(cities.begin(), cities.end()));

    // Output the best path and cost
    cout << "\nMinimum cost: " << minCost << "\nPath: ";
    for (int city : bestPath) {
        cout << city << " -> ";
    }
    cout << bestPath[0] << "\n"; // Return to start

    return 0;
}
