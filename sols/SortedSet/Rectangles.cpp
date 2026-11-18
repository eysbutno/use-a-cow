#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define pb push_back
#define ins insert
#define f first 
#define s second 

// const int MOD = 1e9 + 7;
template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
void solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> g(n, vector<int>(m));
    vector<deque<pii>> q(m);
    auto add = [&](int idx, int col) {
        if (q[idx].empty()) {
            q[idx].push_back({col, 1});
            return;
        }
        auto [k, v] = q[idx].back();
        if (k == col) q[idx].back().s++;
        else q[idx].push_back({col, 1});
    };
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> g[i][j];
            add(j, g[i][j]);
        }
    }
    ll res = 0;
    auto process = [&](int l, int r) {
        set<int> borders;
        borders.ins(l - 1), borders.ins(r + 1);
        vector<int> ord(r - l + 1);
        iota(all(ord), l);
        sort(all(ord), [&](int x, int y) {
            return q[x].front().s < q[y].front().s;
        });
        for (int i : ord) {
            auto it = borders.lower_bound(i);
            int lb = *prev(it), rb = *it;
            res += (ll) (rb - i) * (i - lb) * q[i].front().s;
            borders.ins(i);
        }
    };
    for (int i = 0; i < n; i++) {
        int l = 0, r = 0;
        while (l < m && r < m) {
            while (r < m && g[i][r] == g[i][l]) {
                ++r;
            }
            process(l, r - 1);
            l = r;
        }
        for (int j = 0; j < m; j++) {
            auto [k, v] = q[j].front();
            if (v == 1) q[j].pop_front();
            else q[j].front().s--;
        }
    }
    cout << res << '\n';
}
int main() {
	cin.tie(0) -> sync_with_stdio(0);
    int t; cin >> t;
    while (t--) solve();
}
/**
 * TASK: Rectangles.
 * Idea: Fix the lower row. For each contiguous
 * sequence of same integered things, process them.
 * 
 * For each column-"continuation" pair things, sort them
 * based on their counts. Then, try adding each one in, one
 * by one. You can create a rectangle w/ your own height within
 * the left and right boundaries, if that kinda makes sense.
 * 
 * After that, you do some mathy math and add "border points", to
 * do the mathy math correct.
*/