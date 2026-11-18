#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define pb push_back
#define ins insert
#define f first 
#define s second 

template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
void solve() {
    int n, m; cin >> n >> m;
    vector<array<int, 2>> a(n);
    vector<int> b(m);
    for (int i = 0; i < n; i++) {
        cin >> a[i][0], a[i][1] = i;
    }
    sort(all(a), greater<>());
    for (int& i : b) cin >> i;
    vector mn(m, vector<int>(n, n + 1));
    for (int i = 0; i < m; i++) {
        for (int r = 0; r < n; r++) {
            int l = r + 1 - (b[i] + a[r][0] - 1) / a[r][0];
            if (l >= 0) smin(mn[i][l], r + 1);
        }
        for (int j = n - 2; j >= 0; j--) {
            smin(mn[i][j], mn[i][j + 1]);
        }
    }
    vector<int> dp(1 << m, n + 1),
                p(1 << m, -1);
    dp[0] = 0; // start at prefix 0
    for (int i = 1; i < (1 << m); i++) {
        for (int j = 0; j < m; j++) {
            if (i >> j & 1) {
                int msk = i ^ (1 << j);
                if (dp[msk] < n && smin(dp[i], mn[j][dp[msk]])) {
                    p[i] = j; // last project taken
                }
            }
        }
    }
    const int FULL = (1 << m) - 1;
    if (dp[FULL] <= n) {
        cout << "YES" << '\n';
        vector res(m, vector<int>());
        int cur = FULL ^ (1 << p[FULL]), 
            prv = FULL;
        while (prv > 0) {
            for (int i = dp[cur]; i < dp[prv]; i++) {
                res[p[prv]].push_back(a[i][1] + 1);
            }
            swap(cur, prv);
            cur = prv ^ (1 << p[prv]);
        }
        for (int i = 0; i < m; i++) {
            cout << sz(res[i]) << ' ';
            for (int j : res[i]) {
                cout << j << ' ';
            }
            cout << '\n';
        }
    } else {
        cout << "NO" << '\n';
    }
}
int main() {
	cin.tie(0) -> sync_with_stdio(0);
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * TASK: Team Leader (CF).
 * Claim: Each project should take a range of
 * programmers, assuming the programmers are sorted. 
 * Proof: Let a be the weakest programmer, and let b
 * be the strongest. If b is not connected to the range,
 * then you can swap b with a weaker programmer because
 * the lower bound does not change.
 * 
 * Let dp[mask] be the shortest suffix
 * of (descending) programmers, to have
 * that mask of projects covered. Then,
 * we have the following state transition:
 * dp[mask | (1 << k)] = mn[k][dp[mask]].
 * mn[i][j] = minimum position to satisfy
 * range i, if j is the starting point.
*/
/**
  * Make observations.
  * Try out various techniques in your head.
  * See if there are some "restrictions" that you
  * can place, to limit it to a set of states. This
  * often makes life a million times easier!
  * Actually do something and don't just stare at
  * the screen....!
*/
/*
const int MOD = 1e9 + 7;
template<class T> void add(T& a, T b) {
	a += b, a %= MOD;
}
template<class T> void sub(T& a, T b) {
	a > b ? a -= b : a -= b, a += MOD;
}
template<class T> void mul(T& a, T b) {
	a = (a * b) % MOD;
}
*/