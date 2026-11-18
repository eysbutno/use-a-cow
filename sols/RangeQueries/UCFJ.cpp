#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = array<int, 2>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
namespace SegmentTree {
    template <typename F>
    void forRange(int lf, int rt, F f) {
        for (; lf < rt; lf >>= 1, rt >>= 1) {
            if (lf & 1) f(lf++);
            if (rt & 1) f(--rt);
        }
    } 
    int log2(int x) {
        return 31 - __builtin_clz(x);
    }
    template <typename F>
    void forParents(int p, bool dir, F f) {
        const int lvls = log2(p);
        for (int i = 1; i <= lvls; ++i) {
            f(p >> (!dir ? lvls - i + 1 : i));
        }
    }
    template<class T, class U>
    void update(int l, int r, T apply, U pull) {
        forRange(l, r, apply);
        forParents(l, true, pull);
        forParents(r - 1, true, pull);
    }
    template<class T, class U>
    void query(int l, int r, T push, U apply) {
        forParents(l, false, push);
        forParents(r - 1, false, push);
        forRange(l, r, apply);
    }
}
void solve() {
    int n; cin >> n;
    vector<int> lz(n);
    vector<array<ll, 2>> t(n << 1);
    for (int i = 0; i < n; i++) {
        t[i + n][1] = 1;
    }
    for (int i = n - 1; i >= 1; i--) {
        t[i][1] = t[i << 1][1] + t[i << 1 | 1][1];
    }
    const auto pull = [&](int idx) -> void {
        t[idx][0] = t[idx << 1][0] + t[idx << 1 | 1][0];
        t[idx][1] = t[idx << 1][1] + t[idx << 1 | 1][1];
        t[idx][0] += lz[idx] * t[idx][1];
    };
    const auto apply = [&](int idx, int amt) -> void {
        t[idx][0] += t[idx][1] * amt;
        if (idx < n) lz[idx] += amt;
    };
    const auto push = [&](int idx) -> void {
        apply(idx << 1, lz[idx]);
        apply(idx << 1 | 1, lz[idx]);
        lz[idx] = 0;
    };
    const auto upd = [&](int l, int r, int amt) -> void {
        SegmentTree::update(n + l, n + r, 
            [&](int ind) { apply(ind, amt); }, pull);
    };
    const auto qry = [&](int l, int r) -> ll {
        ll res = 0;
        SegmentTree::query(n + l, n + r, push, 
            [&](int ind) { res += t[ind][0]; });
        return res;
    };
    const auto del = [&](int idx) -> void {
        t[idx + n] = {0, 0};
        SegmentTree::forParents(idx + n, true, pull);
    };
    ll res = 0;
    vector<int> lst(n, -1), prv(n);
    for (int i = 0; i < n; i++) {
        int b; cin >> b; --b;
        res += qry(lst[b] + 1, n);
        if (lst[b] >= 0) {
            upd(prv[lst[b]] + 1, lst[b], -1);
            del(lst[b]);
        }
        upd(lst[b] + 1, i, 1);
        prv[i] = lst[b], lst[b] = i;
    }
    cout << res << "\n";
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * TASK: United Cows of Farmer John (USACO)
 * Let these indices be a, b, c. Iterate over c.
 * Count the # of valid a's, such that a > prev[b[c]].
 * 
 * After processing this current c value, we can treat this
 * index as a possible value of b. So, we just increment the
 * range [prev[b[c]] + 1, r - 1], as these left endpoints can
 * now use this value of b. Note that we also have to make sure to
 * get rid of the "previous" same element, if there is one. We have
 * to undo the previous operation, for this one. 
 * 
 * (Also, we need to make sure to "deactivate" the previous same index,
 * so that endpoints that are not "good" cannot be added to).
*/