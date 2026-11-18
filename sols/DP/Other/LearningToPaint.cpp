#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define f first 
#define s second 

template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
void solve() {
    int n, k; 
    cin >> n >> k;
    vector a(n, vector(n, 0LL));
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            cin >> a[i][j];
        }
    }
    vector<vector<ll>> dp(n);
    dp[0] = {0, a[0][0]};
    if (dp[0][0] < dp[0][1]) {
        swap(dp[0][0], dp[0][1]);
    }
    for (int i = 1; i < n; i++) {
        dp[i].reserve(k);
    }
    for (int i = 1; i < n; i++) {
        priority_queue<array<ll, 3>> pq;
        for (int j = i - 2; j >= -2; j--) {
            // add [j + 2, i] as a new segment.
            ll sum = (j < 0 ? 0 : dp[j][0]) + a[j + 2][i];
            pq.push({sum, j, 0});
        }
        pq.push({dp[i - 1][0], i - 1, 0});
        while (!pq.empty() && sz(dp[i]) < k) {
            auto [res, ind, ord] = pq.top(); pq.pop();
            dp[i].push_back(res);
            if (ind < 0 || ord + 1 >= sz(dp[ind])) {
                continue; // cannot propogate from here.
            }
            // propogate from this current indice.
            ll sum = (ind == i - 1 ? 0 : a[ind + 2][i])
                   + dp[ind][ord + 1];
            pq.push({sum, ind, ord + 1});
        }
    }
    for (int i = 0; i < k; i++) {
        cout << dp[n - 1][i] << " \n"[i == k - 1];
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; cin >> t;
    while (t--) solve();
}
/**
 * TASK: D. Learning to Paint (CF)
 * dp[i] = min(2^i, k) arrangements for [1, i].
 * 
 * NOTE: I was worried about possibly needing to account for duplicates,
 * because the same arrangement can appear in multiple dp[i]. HOWEVER,
 * I'm just being stupid.... because the segment you choose to color
 * also plays into the NEW arrangement... :clown:
*/