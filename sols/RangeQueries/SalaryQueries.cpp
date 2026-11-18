#include <bits/stdc++.h>
using namespace std; 
using pii = pair<int, int>;
using ll = long long;
#define pb push_back
#define f first 
#define s second 

template <class T> class SegTree {
    private:
        const T DEF = 0;
        int len;
        vector<T> t;
    public:
        SegTree(int len) : len(len),
            t(len * 2, DEF) {}
        void set(int idx, T val) {
            idx += len;
            t[idx] = val;
            for (; idx > 1; idx /= 2) {
                t[idx / 2] = t[idx] + t[idx ^ 1];
            }
        }
        T query(int l, int r) {
            T res = 0;
            for (l += len, r += len; l < r; l /= 2, r /= 2) {
                if (l & 1) res += t[l++];
                if (r & 1) res += t[--r];
            }
            return res;
        }
        T get(int idx) {
            return query(idx, idx + 1);
        }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int n, q; cin >> n >> q;
    vector<int> init(n);
    vector<int> uniq;
    for (int i = 0; i < n; i++) {
        cin >> init[i];
        uniq.push_back(init[i]);
    }
    vector<pair<bool, pii>> queries(q);
    for (int i = 0; i < q; i++) {
        char c; int a, b;
        cin >> c >> a >> b;
        if (c == '?') {
            queries[i] = {1, {a, b}};
            uniq.push_back(a);
            uniq.push_back(b);
        } else {
            queries[i] = {0, {a, b}};
            uniq.push_back(b);
        }
    }
    sort(begin(uniq), end(uniq));
    uniq.erase(unique(begin(uniq), 
        end(uniq)), end(uniq));
    unordered_map<int, int> comp;
    int idx = 0;
    for (int i : uniq) {
        comp[i] = idx++;
    }
    SegTree<int> sg(idx);
    for (int i = 0; i < n; i++) {
        int idx = comp[init[i]];
        sg.set(idx, sg.get(idx) + 1);
    }
    for (auto& i : queries) {
        bool t = i.f;
        int a = i.s.f,
            b = i.s.s;
        if (t) {
            cout << sg.query(comp[a], 
                comp[b] + 1) << '\n';
        } else {
            int prev = comp[init[--a]],
                nxt = comp[b];
            sg.set(prev, sg.get(prev) - 1);
            sg.set(nxt, sg.get(nxt) + 1);
            init[a] = b;
        }
    }
}
/*
PURQ + CC
*/