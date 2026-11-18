#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define ckmax(a, b) a = max(a, b)
#define ckmin(a, b) a = min(a, b)
#define sz(x) (int) (x).size()
#define pb push_back
#define ins insert
#define f first 
#define s second 

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
const int MOD = 1e9 + 7;
int main() {
    int n; cin >> n;    
    map<int, int> mp;
    vector<int> x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
        mp[x[i]] = -1;
    }
    int run = 0;
    for (auto& i : mp) {
        i.s = ++run;
    }
    for (int i = 0; i < n; i++) {
        x[i] = mp[x[i]];
    }
    FT<ll> bit(run + 5);
    ll res = 0;
    for (int i : x) {
        ll cur = (bit.prefix(i - 1) + 1) % MOD;
        res += cur, res %= MOD;
        bit.update(i, cur);
    }
    cout << res << '\n';
}