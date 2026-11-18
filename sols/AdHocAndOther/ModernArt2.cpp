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

const int INF = 1e9;
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    freopen("art2.in", "r", stdin);
    freopen("art2.out", "w", stdout);
    int n; cin >> n;
    vector<int> c(n), st(n + 1, INF), 
        ed(n + 1, -INF);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        smin(st[c[i]], i);
        smax(ed[c[i]], i);
    }
    stack<int> s;
    int res = 0;
    for (int i = 0; i < n; i++) {
        if (c[i] == 0) {
            if (sz(s)) {
                cout << -1 << '\n';
                return 0;
            } else {
                continue;
            }
        }
        if (i == st[c[i]]) {
            s.push(c[i]);
        }
        if (s.top() != c[i]) {
            cout << -1 << '\n';
            return 0;
        }
        smax(res, sz(s));
        if (i == ed[c[i]]) {
            s.pop();
        }
    }
    cout << res << '\n';
}
/**
 * TASK: Modern Art 2.
 * Observations:
 * 1. The question is asking
 * how many overlapping intervals
 * must have been painted.
 * 2. There's only an overlap when
 * one required "interval" covers
 * another.
 * 3. Each interval must be contained
 * COMPLETELY within another interval.
*/