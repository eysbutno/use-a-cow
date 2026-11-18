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
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n; cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        int x, y; cin >> x >> y;
        adj[--x].push_back(--y);
        adj[y].push_back(x);
    }
    vector<int> d(n), c(n);
    auto dfs = [&](int u, int p, auto&& dfs) -> void {
		// calculates: longest path, & # of longest paths
        d[u] = 0, c[u] = 1;
        for (int v : adj[u]) if (v != p) {
            dfs(v, u, dfs);
            if (smax(d[u], d[v] + 1)) {
                c[u] = c[v];
            } else if (d[v] + 1 == d[u]) {
                c[u] += c[v];
            }
        }
    }; dfs(0, -1, dfs);
    ll hard = 0, cnt = 1;
    auto dfs2 = [&](int u, int p, int pd, int pc, 
                    auto&& dfs2) -> void {
		// does the reroot, calculates the hardest
		// path with LCA at u, and the # of such paths
        vector<pair<ll, ll>> opt;
        if (u > 0 || sz(adj[u]) == 1) {
            opt.push_back({pd, pc});
        }
        for (int v : adj[u]) if (v != p) {
            opt.push_back({d[v] + 1, c[v]});
        }
        sort(all(opt), greater<>());
        if (sz(adj[u]) >= 3) { // can form nonzero path
            ll cur = opt[0].f * (opt[1].f + opt[2].f), 
               num = 0, ties = 0;
            for (auto [k, v] : opt) {
                if (k == opt[2].f) ties += v;
            }
            // case 1: all are distinct
            if (opt[0].f != opt[1].f &&
                opt[1].f != opt[2].f) {
                num = opt[1].s * ties;
            }
            // case 2: all are the same
            else if (opt[0].f == opt[1].f &&
                opt[1].f == opt[2].f) {
                num = ties * ties;
				for (auto [k, v] : opt) {
					if (k == opt[2].f) num -= v * v;
				}
				num /= 2; // don't want to overcount
            }
            // case 3: first two are the same
            else if (opt[0].f == opt[1].f) {
                num = (opt[0].s + opt[1].s) * ties;
            }
            // case 4: last two are the same
            else {
               	num = ties * ties;
				for (auto [k, v] : opt) {
					if (k == opt[2].f) num -= v * v;
				}
				num /= 2; // don't want to overcount
            }
            if (smax(hard, cur)) {
                cnt = num;
            } else if (hard == cur) {
                cnt += num;
            }
        }
        // processing parent dist & parent count
        ll l1 = 0, l2 = 0, cnt1 = 0, cnt2 = 0;
        for (auto [k, v] : opt) {
            // all paths will increase by len 1
            if (k + 1 > l1) {
                swap(l1, l2), swap(cnt1, cnt2);
                l1 = k + 1, cnt1 = v;
            } else if (k + 1 == l1) {
                cnt1 += v;
            } else if (k + 1 > l2) {
                l2 = k + 1, cnt2 = v;
            } else if (k + 1 == l2) {
                cnt2 += v;
            }
        }
        for (int v : adj[u]) if (v != p) {
            if (d[v] + 2 == l1) {
                (c[v] == cnt1) ? dfs2(v, u, l2, cnt2, dfs2) :
                            	 dfs2(v, u, l1, cnt1 - c[v], dfs2);
            } else {
                dfs2(v, u, l1, cnt1, dfs2);
            }
        }
    }; dfs2(0, -1, 0, 1, dfs2);
    cout << hard << ' ' << cnt << '\n';
}
/**
 * TASK: Hard Route (IZhO).
 * Main idea is as follows: 
 * Iterate over every "LCA" node x. Then, each
 * path will have the endpoints in two branches, 
 * and the furthest distance from another branch.
 * We only need to consider the three greatest distances.
 * Let these be a_1, a_2, a_3, a_1 >= a_2 >= a_3.
 * The optimal hardness will ALWAYS be a_1 * (a_2 + a_3).
 * Because of this, you can easily prove that our counting
 * strategy will never consider two vertices (u, v) twice.
*/