#include <bits/stdc++.h>
using namespace std;
 
int knapsack(vector<int> val, vector<int> wt, int cap) {
    vector<int> dp(cap + 1); 
    for (int i = 0; i < val.size(); i++) {
        for (int j = cap; j >= wt[i]; j--) {
            dp[j] = max(dp[j], val[i] + dp[j - wt[i]]);
        }
    }
    return dp[cap];
}
int main() {
    int n, x; cin >> n >> x;
    vector<int> h(n + 1), s(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    cout << knapsack(s, h, x) << "\n";
}