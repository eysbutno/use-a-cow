#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define f first 
#define s second

const int MAX = 2501;
ll pf[MAX][MAX];
struct Cow {
    ll id, x, y;
};
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n; cin >> n;
    vector<Cow> cows(n);
    vector<pair<int, int>> locs(n);
    for (int i = 0; i < n; i++) {
        ll x, y; cin >> x >> y;
        cows[i] = {i, x, y};
    }
    sort(begin(cows), end(cows), [&](Cow x, Cow y) {
        return x.x < y.x;
    });
    for (int i = 0; i < n; i++) {
        locs[cows[i].id].f = i + 1;
    }
    sort(begin(cows), end(cows), [&](Cow x, Cow y) {
        return x.y < y.y;
    });
    for (int i = 0; i < n; i++) {
        locs[cows[i].id].s = i + 1;
    }
    for (auto i : locs) {
        pf[i.f][i.s] = 1;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            pf[i][j] += pf[i - 1][j] + pf[i][j - 1]
                - pf[i - 1][j - 1];
        }
    }
    ll ans = n + 1;
    for (int c1 = 0; c1 < n; c1++) {
        for (int c2 = c1 + 1; c2 < n; c2++) {
            auto l1 = locs[c1], l2 = locs[c2];
            int x1 = l1.f, x2 = l2.f, y1 = l1.s, y2 = l2.s;
            int minx = min(x1, x2), maxx = max(x1, x2),
                miny = min(y1, y2), maxy = max(y1, y2);
            int above = pf[maxx][n] - pf[maxx][maxy];
            if (minx != 0) {
                above -= pf[minx - 1][n] - pf[minx - 1][maxy];
            }
            int below;
            if (min(y1, y2) == 0) {
                below = 0;
            } else {
                below = pf[maxx][miny - 1];
                if (minx != 0) below -= pf[minx - 1][miny - 1];
            }
            ans += (ll) (above + 1) * (below + 1);
        }
    }
    cout << ans << '\n';
}
/*
Create a 2d prefix sum of (coordinate compressed) cows.
There will always be n + 1 subsets by default, because
there will always be a subsets with one cow, or a subset
with no cows. In order to calculate all the possible rectangles
(and subsets), you have to calculate all the possible rectangles
in a given pair of x and y coordinates. You do this by finding all 
the points above and below a rectangle formed by two cows,
and then adding (above + 1) * (below + 1) to the answer.
*/