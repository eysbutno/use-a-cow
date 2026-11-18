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
    freopen("bphoto.in", "r", stdin);
    freopen("bphoto.out", "w", stdout);
    int n; cin >> n;
    FT<int> bit(n + 2);
    vector<pii> cws(n);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        cws[i] = {x, i + 1};
    }
    sort(all(cws), greater<pii>());
    int res = 0;
    for (auto& i : cws) {
        int l = bit.query(0, i.s - 1);
        int r = bit.query(i.s + 1, n + 1);
        if (l > r * 2 || r > l * 2) {
            ++res;
        }
        bit.update(i.s, 1);
    }
    cout << res << '\n';
}
/**
 * Add the cows in one by, in
 * decreasing order. Use a BIT.
*/