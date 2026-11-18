#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define smin(a, b) a = min(a, b)
#define smax(a, b) a = max(a, b)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define pb push_back 
#define ins insert
#define f first 
#define s second

const int N = 1e5;
vector<int> adj[N];
int dp[N];
bool dfs(int u, int p, int k) {
    vector<int> lens;
    for (int i : adj[u]) {
        if (i != p) {
            if (!dfs(i, u, k)) {
                return false;
            }
            lens.pb(dp[i] + 1);
        }
    }
    int og = sz(lens);
    if (sz(lens) % 2 != 1) {
        lens.pb(0);
    }
    sort(all(lens));
    auto check = [&](int mid) {
        int l = 0, r = sz(lens) - 1;
        while (l < r) {
            if (l == mid) {
                ++l;
            } else if (r == mid) {
                --r;
            } else {
                if (lens[l] + lens[r] < k) {
                    return false;
                }
                ++l, --r;
            }
        }
        return true;
    };
    int low = 0, high = sz(lens) - 1;
    while (low < high) {
        int mid = (low + high + 1) / 2;
        if (check(mid)) low = mid;
        else high = mid - 1;
    }
    if (!check(low)) {
        return false;
    }
    if (sz(lens)) {
        dp[u] = lens[low];
    } else {
        dp[u] = 0;
    }
    if (u == 0) {
        return ((og % 2 && dp[u] >= k)
                || (og % 2 == 0));
    }
    return true;
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    freopen("deleg.in", "r", stdin);
    freopen("deleg.out", "w", stdout);
    int n; cin >> n;
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        --x, --y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    int low = 1, high = n - 1;
    while (low < high) {
        int mid = (low + high + 1) / 2;
        if (dfs(0, -1, mid)) low = mid;
        else high = mid - 1;
        fill(dp, dp + n, 0);
    }
    cout << low << '\n';
}
/**
 * Problem: Delegation (Plat)
 * Observations:
 * 1. A larger K provides strictly
 * less flexibility. So, we can
 * binary search the value of K.
 * 
 * Maintain dp[i], where dp[i] is
 * the length of the longest unpaired
 * path.
 * 
 * Binary search the max path that
 * does not need to be paired for
 * each scenario.
*/