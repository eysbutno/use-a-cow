#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define all(x) begin(x), end(x)
#define ckmin(a, b) a = min(a, b)
#define ckmax(a, b) a = max(a, b)
#define pb push_back 
#define ins insert
#define f first 
#define s second
 
const int N = 2e5 + 1;
vector<int> adj[N];
int st[N], ed[N], timer;
template<class T> class FT {
    private:
        int sz;
        vector<T> arr;
    public:
        FT(int n) {
            sz = n + 1;
            arr.resize(n + 1);
        }
        T prefix(int idx) {
            ++idx; 
            T tot = 0;
            while (idx >= 1) {
                tot += arr[idx];
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
                arr[idx] += dx;
                idx += idx & -idx;
            }
        }
};
void tour(int node, int prev) {
    st[node] = timer++;
    for (int i : adj[node]) {
        if (i != prev) {
            tour(i, node);
        }
    }
    ed[node] = timer;
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n, q; 
    cin >> n >> q;
    vector<int> v(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
    }
    for (int i = 1; i < n; i++) {
        int x, y; 
        cin >> x >> y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    tour(1, 0);
    FT<ll> bit(n + 1);
    for (int i = 1; i <= n; i++) {
        bit.update(st[i], v[i]);
    }
    for (int i = 0; i < q; i++) {
        int t; cin >> t;
        if (t == 1) {
            int s, x;
            cin >> s >> x;
            bit.update(st[s], 
                x - v[s]);
            v[s] = x;
        } else {
            int s; cin >> s;
            cout << bit.query(st[s], ed[s] - 1)
                << '\n';
        }
    }
}