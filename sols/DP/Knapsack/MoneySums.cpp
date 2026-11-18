#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> coins(n);
    int sum = 0;
    for (int &i : coins) {
        cin >> i; sum += i;
    }
    vector<bool> dp(sum + 1);
    dp[0] = 1;
    for (int i : coins) {
        for (int j = sum; j >= i; j--) {
            if (dp[j - i]) dp[j] = 1;
        }
    }
    vector<int> nums;
    for (int i = 1; i <= sum; i++) {
        if (dp[i]) nums.push_back(i);
    }
    cout << nums.size() << "\n";
    for (int i : nums) cout << i << " ";
}
/*
Type: Knapsack DP
Algorithm: 
Add the coins one by one. If a
coin's col was visited, then
append it to a vector.
*/