#include <bits/stdc++.h>
using namespace std;
#define f first 
#define s second

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    freopen("diamond.in", "r", stdin);
    freopen("diamond.out", "w", stdout);
    int n, k; cin >> n >> k;
    vector<int> nums(n);
    for (int& i : nums) cin >> i;
    sort(begin(nums), end(nums));
    int l = 0, r = 0;
    vector<int> before(n), after(n);
    while (l < n && r < n) {
        if (nums[r] - nums[l] <= k) {
            int range = r - l + 1; 
            before[r] = max(before[r], range);
            after[l] = max(after[l], range);
            r++;
        } else {
            l++;
        }
    }
    int ans = 0, less = 0;
    for (int i = 1; i < n; i++) {
        less = max(less, before[i - 1]);
        ans = max(ans, less + after[i]);
    }
    cout << ans << '\n';
}