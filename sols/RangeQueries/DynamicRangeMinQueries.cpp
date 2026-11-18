#include <bits/stdc++.h>
using namespace std; 
using pii = pair<int, int>;
using ll = long long;
#define pb push_back
#define f first 
#define s second 

template <class T> class SegTree {
    private:
        const T DEF = 2e9;
        vector<T> t;
        int len;
    public:
        SegTree(int len) : len(len),
            t(len * 2, DEF) {}
        void set(int idx, T val) {
            idx += len;
            t[idx] = val;
            for (; idx > 1; idx /= 2) {
                t[idx / 2] = min(t[idx], t[idx ^ 1]);
            }
        }
        T query(int l, int r) {
            T res = 2e9;
            for (l += len, r += len; l < r; l /= 2, r /= 2) {
                if (l & 1) res  = min(res, t[l++]);
                if (r & 1) res = min(res, t[--r]);
            }
            return res;
        }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int n, q; cin >> n >> q;
    SegTree<int> sg(n);
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