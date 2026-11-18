#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define f first 
#define s second

void solve() {
    int n; cin >> n;
    vector<pair<pair<int, 
        int>, int>> fr(n);
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        fr[i] = {{a, b}, i};
    }
    sort(begin(fr), end(fr), 
        [&](auto& x, auto& y) {
        return x.f.f < y.f.f;
    });
    vector<int> low(n), idx(n);
    low[0] = fr[0].f.s;
    idx[0] = fr[0].s;
    for (int i = 1; i < n; i++) {
        if (fr[i].f.s < low[i - 1]) {
            low[i] = fr[i].f.s;
            idx[i] = fr[i].s;
        } else {
            low[i] = low[i - 1];
            idx[i] = idx[i - 1];
        }
    }
    auto getIdx = [&](int v) {
        pair<pair<int, int>, int> 
            target = {{v, 0}, 0};
        return lower_bound(begin(fr), 
            end(fr), target,
            [&](auto& x, auto& y) {
            return x.f.f < y.f.f;
        }) - begin(fr) - 1;
    };
    vector<int> res(n);
    for (int i = 0; i < n; i++) {
        int h = fr[i].f.f,
            w = fr[i].f.s,
            id = fr[i].s;
        int pos = getIdx(w);
        // diff positions
        if (pos >= 0 && pos < n
            && low[pos] < h) {
            res[id] = idx[pos] + 1;
            continue;
        }
        pos = getIdx(h);
        if (pos >= 0 && pos < n
            && low[pos] < w) {
            res[id] = idx[pos] + 1;
            continue;
        }
        res[id] = -1;
    }
    for (int i : res) cout << i << ' ';
    cout << '\n';
}
int main() {
    int t; cin >> t;
    while (t--) solve();
}
/*
WE BALL I ACTUALLY SOLVED A
PROBLEM BY MYSELF FOR ONCE!!!

The algorithm idea is to
sort the list by h value,
and then maintain an array
of the lowest w value
for a given prefix of elements.
Do some magic, and it works. Yay!
*/