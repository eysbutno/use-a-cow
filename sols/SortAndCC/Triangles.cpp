#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
typedef long long ll;

const int MOD = 1e9 + 7;
struct Fence {
    ll bases, heights;
};
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    freopen("triangles.in", "r", stdin);
    freopen("triangles.out", "w", stdout);
    int n; cin >> n;
    vector<Fence> fences(n);
    unordered_map<int, vector<pair<int, int>>> xLocs, yLocs;
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        xLocs[x].push_back({y, i});
        yLocs[y].push_back({x, i});
    }
    for (auto i : xLocs) {
        int key = i.f, size = xLocs[key].size();
        sort(begin(xLocs[key]), end(xLocs[key]));
        ll sum = 0;
        for (int j = 1; j < size; j++) {
            sum += xLocs[key][j].f - xLocs[key][0].f;
        }
        fences[xLocs[key][0].s].heights = sum;
        for (int j = 1; j < size; j++) {
            sum += (xLocs[key][j].f - xLocs[key][j - 1].f)
                * (2 * j - size);
            fences[xLocs[key][j].s].heights = sum;
        }
    } 
    for (auto i : yLocs) {
        ll key = i.f, size = yLocs[key].size();
        sort(begin(yLocs[key]), end(yLocs[key]));
        ll sum = 0;
        for (int j = 1; j < size; j++) {
            sum += yLocs[key][j].f - yLocs[key][0].f;
        }
        fences[yLocs[key][0].s].bases = sum;
        for (int j = 1; j < size; j++) {
            sum += (yLocs[key][j].f - yLocs[key][j - 1].f)
                * (2 * j - size);
            fences[yLocs[key][j].s].bases = sum;
        }
    } 
    ll ans = 0;
    for (Fence& i : fences) {
        ans += ((i.bases % MOD) * (i.heights % MOD)) % MOD;
        ans %= MOD;
    }
    cout << ans << '\n';
}
/*
Treat each point as if it was the vertice of the right angle.
The sum of all the areas that you can form with this 
point is the sum of all the bases (with this point) *
the sum of all the heights. (if we have base lengths
x1, x2, x3, and heights y1, y2, y3, the sum is
(x1 + x2 + x3) * (y1 + y2 + y3) if you use FOIL)
*/