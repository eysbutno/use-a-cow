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
    freopen("circlecross.in", "r", stdin);
    freopen("circlecross.out", "w", stdout);
    int n; cin >> n;
    vector<int> loc(n + 1, -1);
    FT<int> bit(n * 2 + 5);
    int res = 0;
    for (int i = 0; i < n * 2; i++) {
        int x; cin >> x;
        if (loc[x] == -1) {
            bit.update(i, 1);
            loc[x] = i;
        } else {
            res += bit.query(loc[x] + 1, i);
            bit.update(loc[x], -1);
        }
    }
    cout << res << '\n';
}
/**
 * Say we have each cow
 * start at a_i and end
 * at b_i. There is only
 * an intersection between
 * two cows i and j if 
 * a_i < b_i and b_i > b_j.
 * 
 * Implementation Note:
 * To find the # of "active" pairs
 * in between a cow and their end
 * location, update the start location
 * to be 1 when they're active and
 * 0 when they're inactive.
*/