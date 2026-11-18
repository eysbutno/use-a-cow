#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define ckmax(a, b) a = max(a, b)
#define ckmin(a, b) a = min(a, b)
#define pb push_back
#define ins insert
#define f first 
#define s second 

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
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    freopen("haircut.in", "r", stdin);
    freopen("haircut.out", "w", stdout);
    int n; cin >> n;
    FT<ll> bit(n + 5);
    vector<ll> res(n + 5);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        res[x + 1] += bit.query(x + 1, n + 1);
        bit.update(x, 1);
    }
    ll cnt = 0;
    for (int i = 0; i < n; i++) {
        cnt += res[i];
        cout << cnt << '\n';
    }
}
/**
 * ans[i] is, ironically enough,
 * monotonically increasing. 
 * 
 * We count inversions when adding
 * elements. Note that an inversion
 * for a given number can only exist
 * if the value j is x + 1, so we 
 * count inversions that way.
*/