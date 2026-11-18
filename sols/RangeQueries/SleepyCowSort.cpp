#include <bits/stdc++.h>
using namespace std;
using ll = long long;
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
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    freopen("sleepy.in", "r", stdin);
    freopen("sleepy.out", "w", stdout);
    int n; cin >> n;
    vector<int> p(n);
    for (int& i : p) {
        cin >> i;
    }
    int res = n - 1;
    for (int i = n - 2; i >= 0; i--) {
        if (p[i] < p[i + 1]) res = i;
        else break;
    }
    cout << res << '\n';
    FT<int> bit(n + 5);
    for (int i = res; i < n; i++) {
        bit.update(p[i], 1);
    }
    for (int i = 0; i < res; i++) {
        cout << res - i - 1 + bit.prefix(p[i]) 
            << (i != res - 1 ? ' ' : '\n');
        bit.update(p[i], 1);
    }
    return 0;
}