#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define sz(x) (int) (x).size()
#define pb push_back 
#define ins insert
#define f first 
#define s second

template<class T> class FT {
    private:
        int sz; vector<T> pf;
    public:
        FT(int n) {
            sz = n + 1, pf.resize(n + 1);
        }
        T get(int idx) {
            ++idx; 
            T tot = 0;
            while (idx >= 1) {
                tot += pf[idx];
                idx -= idx & -idx;
            }
            return tot;
        }
        T query(int l, int r) {
            return get(r) - get(l - 1);
        }
        void update(int idx, T dx) {
            ++idx;
            while (idx <= sz) {
                pf[idx] += dx;
                idx += idx & -idx;
            }
        }
};
const int N = 751;
const int MOD = 1e9 + 7;
int grid[N][N], val[N][N];
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    freopen("hopscotch.in", "r", stdin);
    freopen("hopscotch.out", "w", stdout);
    int n, m, k; cin >> n >> m >> k;
    vector<map<int, int>> mp(k + 1);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> grid[i][j];
            mp[grid[i][j]][j] = -1;
        }
    }
    for (int i = 1; i <= k; i++) {
        int running = 0;
        for (auto [j, v] : mp[i]) {
            mp[i][j] = ++running;
        }
    }
    FT<ll> col(m + 5);
    vector<FT<ll>> cont(k + 1, FT<ll>(0));
    for (int i = 1; i <= k; i++) {
        cont[i] = FT<ll>(sz(mp[i]) + 1);
    }
    vector<ll> vals(m + 1);
    for (int i = 1; i <= n; i++) {
        for (int j = m; j >= 1; j--) {
            if (i == 1 && j == 1) {
                cont[grid[i][j]].update(1, 1);
                col.update(1, 1);
                continue;
            }
            int id = grid[i][j];
            ll cur = col.get(j - 1);
            ll exc = cont[id].get(mp[id][j] - 1);
            cur = (cur - exc + MOD) % MOD;
            col.update(j, cur);
            cont[id].update(mp[id][j], cur);
            vals[j] = cur;
        }
    }
    cout << vals[m] << '\n';
}
/**
 * NOTE: This code compiles fine on
 * USACO and on USACO Guide IDE, but
 * segfaults on my computer because
 * apparently it can't delete the FTs.
**/