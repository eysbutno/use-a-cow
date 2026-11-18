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

const int MOD = 1e9 + 7;
template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
template<class T> void add(T& a, T b) {
    a += b, a %= MOD;
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    vector<int> dp(n), inDeg(n);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        --x, --y;
        adj[x].pb(y);
        inDeg[y]++;
    }
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (!inDeg[i]) q.push(i);
    }
    dp[0] = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i : adj[u]) {
            --inDeg[i], add(dp[i], dp[u]);
            if (!inDeg[i]) q.push(i);
        }
    }
    cout << dp.back() << '\n';
}
/**
 * The only variation you can
 * have, is in the way you pick 
 * the child node.
*/