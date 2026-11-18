#include <bits/stdc++.h>
using namespace std; 
using pii = pair<int, int>;
using ll = long long;
#define pb push_back
#define f first 
#define s second 

struct SegTree {
    int len;
    vector<ll> t;
    SegTree(int n) {
        len = n;
        t.resize(n * 2);
    }
    void set(int idx, ll val) {
        idx += len;
        t[idx] = val;
        for (; idx > 1; idx /= 2) {
            t[idx / 2] = t[idx] + t[idx ^ 1];
        }
    }
    ll query(int l, int r) {
        ll res = 0;
        for (l += len, r += len; l < r; l /= 2, r /= 2) {
            if (l & 1) res += t[l++];
            if (r & 1) res += t[--r];
        }
        return res;
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int n, q; cin >> n >> q;
    SegTree sg(n);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        sg.set(i, x);
    }
    while (q--) {
        int t, x, y; 
        cin >> t >> x >> y;
        if (t == 1) {
            sg.set(x - 1, y);
        } else {
            cout << sg.query(x - 1, y) 
                << '\n';
        }
    }
}