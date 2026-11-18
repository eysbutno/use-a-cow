#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> nums(n);
    for (int &i : nums) cin >> i;
    vector<int> dp;
    for (int i : nums) {
        int pos = lower_bound(begin(dp), end(dp), i) - begin(dp);
        if (pos != size(dp)) {
            dp[pos] = i;
        } else {
            dp.push_back(i);
        }
    }
    cout << size(dp) << "\n";
}