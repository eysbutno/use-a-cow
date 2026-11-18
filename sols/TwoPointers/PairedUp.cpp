#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

void setIO(string name = "") {
    ios_base::sync_with_stdio(0); cin.tie(0);
    if (name.size()) {
       freopen((name + ".in").c_str(), "r", stdin);
       freopen((name + ".out").c_str(), "w", stdout);
    }
}
int main() {
    setIO();
    int n; cin >> n;
    vector<pair<int, int>> cows;
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        cows.push_back({y, x});
    }
    sort(begin(cows), end(cows));
    int l = 0, r = cows.size() - 1, ans = 0;
    while (l < r) {
        int pairs = min(cows[l].s, cows[r].s);
        cows[l].s -= pairs, cows[r].s -= pairs;
        ans = max(cows[l].f + cows[r].f, ans);
        if (!cows[l].s) l++;
        if (!cows[r].s) r--;
    }
    cout << ans << "\n";
}