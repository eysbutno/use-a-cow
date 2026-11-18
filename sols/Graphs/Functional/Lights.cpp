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
    int n; cin >> n;
    vector<bool> on(n);
    for (int i = 0; i < n; i++) {
        char c; cin >> c;
        if (c == '1') on[i] = 1;
    }
    vector<int> a(n), deg(n);
    for (int& i : a) {
        cin >> i, ++deg[--i];
    }
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (!deg[i]) q.push(i);
    }
    vector<int> res;
    vector<bool> vis(n);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (on[u]) {
            on[u] = !on[u];
            on[a[u]] = !on[a[u]];
            res.push_back(u);
        }
        if (--deg[a[u]] == 0) {
            q.push(a[u]);
        }
    }  
    fill(all(vis), false);
    bool bad = false;
    auto process = [&](int u) {
        vector<int> cycle = {u};
        int ptr = a[u], cnt = on[u];
        while (ptr != u) {
            cycle.push_back(ptr);
            if (on[ptr]) ++cnt;
            vis[ptr] = true;
            ptr = a[ptr];
        }
        map<int, int> con;
        for (int i : cycle) {
            con[i] = on[i];
        }
        vis[u] = true;
        if (cnt & 1) {
            bad = true;
            return;
        }
        vector<vector<int>> s(2);
        for (int i = 0; i < 2; i++) {
            int p1 = u, p2 = a[u];
            map<int, int> tmp = con;
            if (i > 0) {
                tmp[u] = !tmp[u];
                tmp[a[u]] = !tmp[a[u]];
                s[i].push_back(u);
            }
            while (p1 != p2) {
                if (tmp[p2]) {
                    tmp[p2] = !tmp[p2];
                    tmp[a[p2]] = !tmp[a[p2]];
                    s[i].push_back(p2);
                }
                p2 = a[p2];
            }
        }
        if (sz(s[0]) > sz(s[1])) {
            for (int i : s[1]) {
                res.push_back(i);
            }
        } else {
            for (int i : s[0]) {
                res.push_back(i);
            }
        }
    };
    for (int i = 0; i < n; i++) {
        if (!vis[i] && on[i]) {
            process(i);
        }
    }
    if (bad) {
        cout << -1 << '\n';
        return;
    }
    cout << sz(res) << '\n';
    for (int i : res) {
        cout << i + 1 << ' ';
    }
    cout << '\n';
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t; cin >> t;
    while (t--) solve();
}
/**
 * Create a graph where index i
 * goes to index a_i, so it's a 
 * functional graph with one cycle
 * per component. Basically, if i is 
 * changed, a_i is forcefully changed.
 * 
 * For each component, we first adjust
 * all the "tails" in the cycle. Then,
 * we adjust the cycle.
*/