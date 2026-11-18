#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define f first 
#define s second 

template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
void solve() {
    int n, m, k; cin >> n >> m >> k;
    vector<vector<int>> add(n + 1), del(n + 1);
    for (int i = 0; i < m; i++) {
        int l, r; cin >> l >> r;
        add[--l].push_back(i);
        del[r].push_back(i);
    }
    vector<int> disjoint(m);
    map<pii, int> joint;
    set<int> active;
    int dry = 0;
    for (int i = 0; i < n; i++) {
        // process additions and deletions.
        for (int j : add[i]) active.insert(j);
        for (int j : del[i]) active.erase(j);
        if (sz(active) == 1) {
            ++disjoint[*begin(active)];
        }   
        if (sz(active) == 2) {
            vector<int> a;
            for (int j : active) {
                a.push_back(j);
            }
            joint[{a[0], a[1]}]++;
        }
        if (sz(active) == 0) ++dry;
    }
    int m1 = 0, m2 = 0;
    for (int i : disjoint) {
        if (i > m1) {
            swap(m1, m2), m1 = i;
        } else if (i > m2) {
            m2 = i;
        }
    }
    int comb = 0;
    for (auto [k, v] : joint) {
        smax(comb, disjoint[k.f] + disjoint[k.s] + v);
    }
    cout << dry + max(comb, m1 + m2) << "\n";
}
int main() {
	cin.tie(0) -> sync_with_stdio(0);
    int t = 1; cin >> t;
    while (t--) solve();
}
/**
 * TASK: E1. Doremy's Drying Plan (Easy)
 * Premise of the problem: Remove two intervals to
 * maximize the space that is not covered by any given
 * interval.
 * 
 * Because it's only two intervals, there are two cases:
 * A. We choose two disjoint intervals, and delete them.
 * B. We choose two joint intervals, and delete them.
 * NOTE: For two joint intervals, you still need to consider
 * the "disjoint" parts that they cover.
*/