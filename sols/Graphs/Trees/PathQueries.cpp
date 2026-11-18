#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define pb push_back
#define ins insert
#define f first 
#define s second 
    
const int N = 2e5 + 1;
vector<int> adj[N];
int st[N], ed[N], t;
template<class T> class FT {
    private:
        int sz;
        vector<T> pf;
    public:
        FT(int n) {
            sz = n + 1;
            pf.resize(n + 1);
        }
        T prefix(int idx) {
            ++idx; 
            T tot = 0;
            while (idx >= 1) {
                tot += pf[idx];
                idx -= idx & -idx;
            }
            return tot;
        }
        T query(int l, int r) {
            return prefix(r) - prefix(l - 1);
        }
        void update(int idx, T dx) {
            ++idx;
            while (idx <= sz) {
                pf[idx] += dx;
                idx += idx & -idx;
            }
        }
};
void tour(int node, int prev) {
    st[node] = t++;
    for (int i : adj[node]) {
        if (i != prev) {
            tour(i, node);
        }
    }
    ed[node] = t;
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n, q; cin >> n >> q;
    vector<ll> v(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
    }
    for (int i = 1; i < n; i++) {
        int x, y; 
        cin >> x >> y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    tour(1, -1);
    FT<ll> bit(n + 5);
    for (int i = 1; i <= n; i++) {
        bit.update(st[i], v[i]);
        bit.update(ed[i], -v[i]);
    }
    while (q--) {
        int t, s; 
        cin >> t >> s;
        if (t == 1) {
            ll x; cin >> x;
            bit.update(st[s], x - v[s]);
            bit.update(ed[s], v[s] - x);
            v[s] = x;
        } else {
            cout << bit.prefix(
                st[s]) << '\n';
        }
    }
}
/**
 * Updates means its PURQ.
 * Motivating question:
 * How to represent a path
 * with a Euler tour?
 * 
 * Answer:
 * For each node, add the current
 * node's value at the start of the
 * tour, and subtract it at the
 * end of the tour.
 * 
 * Why does this work?
 * Answer: If you subtract it at the
 * end of the tour, then all the paths
 * that would otherwise contain other subtrees
 * will no longer have that issue.
*/