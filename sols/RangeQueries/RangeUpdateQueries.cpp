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
    SegTree sg(n + 1);
    vector<ll> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int a, b; ll u;
            cin >> a >> b >> u; --a;
            ll c1 = sg.query(a, a + 1),
                c2 = sg.query(b, b + 1);
            sg.set(a, c1 + u);
            sg.set(b, c2 - u);
        } else {
            int k; cin >> k;
            cout << arr[k - 1] + sg.query(0, k) 
                << '\n';
        }
    }
}