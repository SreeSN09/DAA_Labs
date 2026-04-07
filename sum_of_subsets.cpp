#include <iostream>
#include <vector>
using namespace std;

void findSubsets(vector<int>& nums, int target, vector<int>& subset, int index, int currentSum) {
    if (currentSum == target) {
        cout << "{ ";
        for (int num : subset) cout << num << " ";
        cout << "}" << endl;
        return;
    }
    if (index >= nums.size() || currentSum > target) return;
    subset.push_back(nums[index]);
    findSubsets(nums, target, subset, index + 1, currentSum + nums[index]);
    subset.pop_back();
    findSubsets(nums, target, subset, index + 1, currentSum);
}

int main() {
    int n, target;
    cout << "Enter number of elements: ";
    if (!(cin >> n) || n <= 0) {
        cout << "Invalid input.\n";
        return 1;
    }
    vector<int> nums(n);
    cout << "Enter elements: ";
    for (int i = 0; i < n; i++) {
        if (!(cin >> nums[i])) {
            cout << "Invalid input.\n";
            return 1;
        }
    }
    cout << "Enter target sum: ";
    if (!(cin >> target)) {
        cout << "Invalid input.\n";
        return 1;
    }
    vector<int> subset;
    cout << "Subsets with sum " << target << " are:\n";
    findSubsets(nums, target, subset, 0, 0);
    return 0;
}
