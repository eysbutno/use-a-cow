#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define f first 
#define s second 

const int N = 1e5 + 1;
const int LOG = 18;
vector<int> adj[N];
int st[N], ed[N], e[N], 
    up[LOG][N], dep[N], t;
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
    ed[node] = t - 1;
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    freopen("promote.in", "r", stdin);
    freopen("promote.out", "w", stdout);
    int n; cin >> n;
    vector<pii> p(n);
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        p[i - 1] = {x, i};
    }
    for (int i = 2; i <= n; i++) {
        int x; cin >> x;
        adj[x].push_back(i);
    }
    tour(1, 0);
    sort(all(p));
    reverse(all(p));
    FT<int> bit(n + 1);
    vector<int> ans(n + 1);
    for (auto& i : p) {
        ans[i.s] = bit.query(st[i.s], ed[i.s]);
        bit.update(st[i.s], 1);
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << '\n';
    }
}