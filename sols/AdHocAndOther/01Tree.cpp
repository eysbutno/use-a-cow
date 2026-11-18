#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define smin(a, b) a = min(a, b)
#define smax(a, b) a = max(a, b)
#define pb push_back
#define ins insert
#define f first 
#define s second 

void solve() {
    int n; cin >> n;
    vector<int> a(n), prev(n), nxt(n);
    for (int i = 0; i < n; i++ ){
        cin >> a[i];
        prev[i] = i - 1;
        nxt[i] = i + 1;
    }
    vector<int> ord(n);
    iota(all(ord), 0);
    sort(all(ord), [&](int x, int y) {
        return a[x] > a[y];
    });
    bool good = true;
    for (int i : ord) {
        int mx = -1;
        if (prev[i] != -1) {
            smax(mx, a[prev[i]]);
        }
        if (nxt[i] != n) {
            smax(mx, a[nxt[i]]);
        }
        if (a[i] > mx + 1 || (!a[i] && !mx)) {
            good = false; break;
        }
        if (prev[i] != -1) {
            nxt[prev[i]] = nxt[i];
        }
        if (nxt[i] != n) {
            prev[nxt[i]] = prev[i];
        }
    }
    cout << (good ? "YES" : "NO") << '\n';
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t; cin >> t;
    while (t--) solve();
}
/**
 * TASK: 01 Tree.
 * Algorithm:
 * Just continually delete pairs of leaves,
 * until you get the root node. If you can't
 * do so, then it's impossible.
*/