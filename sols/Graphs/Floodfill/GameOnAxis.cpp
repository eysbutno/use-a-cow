#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = array<int, 2>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

template<class T> bool smax(T &a, T b) {
    return a < b ? a = b, 1 : 0;
}
template<class T> bool smin(T &a, T b) {
    return a > b ? a = b, 1 : 0;
}
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    vector<vector<int>> g(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i], a[i] += i;
        if (0 <= a[i] && a[i] < n) {
            g[a[i]].push_back(i);
        }
    }
    int unseen = n;
    vector<int> sub(n);
    auto dfs = [&](int u, auto&& dfs) -> void {
        sub[u] = 1, --unseen;
        for (int v : g[u]) {
            dfs(v, dfs);
            sub[u] += sub[v];
        }
    };
    for (int i = 0; i < n; i++) {
        if (a[i] < 0 || a[i] >= n) {
            dfs(i, dfs);
        }
    }
    ll res = 0;
    if (sub[0] > 0) {
        int ptr = 0;
        while (ptr >= 0 && ptr < n) {
            res -= sub[ptr] + unseen;
            ptr = a[ptr];
        }
        res += 1LL * (2 * n + 1) * n;
    } else {
        int ptr = 0, sz = 0;
        vector<bool> vis(n);
        while (!vis[ptr]) {
            vis[ptr] = true, ++sz;
            ptr = a[ptr];
        }
        res = 1LL * sz * (2 * n + 1 - unseen);
    }
    cout << res << "\n";
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; cin >> t;
    while (t--) solve();
}
/**
 * Construct a functional graph... Then, DFS on all the 
 * states that can reach an ending. Note that, strictly by
 * the way the graph is structured, that the "reversed" graph
 * starting at an ending is strictly a directed rooted tree.
 * 
 * Case 1: You cannot reach an ending state right now.
 * In this case, you just need to choose one cycle node to
 * change, so that it redirects to an invalid position.
 * 
 * Case 2: You can reach an ending state right now.
 * Counting the # of ways you can reach a "good" ending state
 * is a lot harder than counting the ways you can't reach a good
 * "ending" state. Go on the path, from 1 to the end. From this node,
 * note that we strictly cannot go to the following nodes:
 * 1. Any node that was not visited by our DFS.
 * 2. Any node that can go into this current node.
*/