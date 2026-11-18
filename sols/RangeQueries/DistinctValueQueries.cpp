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
    int n, q; cin >> n >> q;
    vector<int> x(n);
    map<int, queue<int>> mp;
    for (int i = 0; i < n; i++) {
        cin >> x[i];
        mp[x[i]].push(i);
    }
    FT<int> bit(n + 5);
    for (auto& i : mp) {
        bit.update(i.s.front(), 1);
        i.s.pop();
    }
    vector<pair<pii, int>> queries(q);
    for (int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        queries[i] = {{--l, --r}, i};
    }
    sort(all(queries));
    vector<int> res(q);
    int prev = 0;
    for (auto& i : queries) {
        int l = i.f.f, r = i.f.s,
            id = i.s;
        set<int> fixed;
        for (int j = prev; j < l; j++) {
            if (fixed.count(x[j])) {
                continue;
            }
            while (size(mp[x[j]])) {
                int t = mp[x[j]].front();
                mp[x[j]].pop();
                if (t >= l) {
                    bit.update(t, 1);
                    break;
                }
            }
            fixed.ins(x[j]);
        }
        res[id] = bit.query(l, r);
        prev = l;
    }
    for (int i : res) {
        cout << i << '\n';
    }
}
/**
 * Sort queries by leftmost
 * occurence, and add/remove
 * when necessary. Use a BIT
 * to query.
*/