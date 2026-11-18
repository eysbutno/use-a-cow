#include <bits/stdc++.h>
using namespace std;
#define ll long long

void solve() {
    int n, m; cin >> n >> m; --m;
    vector<ll> nums(n), pf(n);
    ll running = 0;
    for (int i = 0; i < n; i++) {
        cin >> nums[i]; 
        running += nums[i];
        pf[i] = running;
    }
    ll mid = pf[m];
    int cnt = 0;
    priority_queue<ll> vals;
    for (int i = m; i >= 0; i--) {
        while (mid > pf[i]) {
            mid -= vals.top();
            vals.pop(); ++cnt;
        }
        if (nums[i] > 0) {
            vals.push(nums[i] * 2);
        }
    }
    mid = pf[m];
    while (!vals.empty()) vals.pop();
    for (int i = m + 1; i < n; i++) {
        if (nums[i] < 0) {
            vals.push(nums[i] * -2);
        }
        while (mid > pf[i]) {
            mid -= vals.top();
            vals.pop(); 
            ++cnt;
        }
    }
    cout << cnt << '\n';
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int t; cin >> t;
    while (t--) solve();
}