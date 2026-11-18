#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define f first 
#define s second

const int MAX = 1e5 + 1;
set<int> mastered[MAX];
void solve() {
    int n, m; cin >> n >> m;
    vector<int> nums(n);
    for (int& i : nums) {
        cin >> i;
    }
    sort(begin(nums), end(nums));
    int l = 0, r = 0, ans = INT_MAX;
    unordered_map<int, int> masters;
    for (; l < n; l++) {
        for (; r < n; r++) {
            if (size(masters) >= m) {
                break;
            }
            // adding student r
            for (int i : mastered[nums[r]]) {
                if (i > m) break;
                masters[i]++;
            }
        }
        if (size(masters) < m) {
            cout << (ans != INT_MAX ?
                ans : -1) << '\n';
            return;
        }
        ans = min(ans, nums[r - 1] - nums[l]);
        for (int i : mastered[nums[l]]) {
            // removing student l
            if (i > m) break;
            masters[i]--;
            if (!masters[i]) {
                masters.erase(i);
            }
        }
    }
    if (ans == INT_MAX) cout << -1 << '\n';
    else cout << ans << '\n';
}
void build() {
    for (int i = 1; i < MAX; i++) {
        for (int j = i; j < MAX; j += i) {
            mastered[j].insert(i);
        }
    }
}
int main() {
    build();
    int t; cin >> t;
    while (t--) solve();
    return 0;
}
/*
For each student i, calculate all topics
j they are masters in.

In each test case, use the two pointers
method to have the minimum amount of
students if you start at student l.
I used a hashmap to keep track of what
topics have masters and which ones don't.
*/