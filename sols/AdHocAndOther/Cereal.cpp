#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    freopen("cereal.in", "r", stdin);
    freopen("cereal.out", "w", stdout);
    int n, m; cin >> n >> m;
    vector<vector<int>> pref(n);
    for (int i = 0; i < n; i++) {
        int f, s; cin >> f >> s;
        pref[i] = {f, s};
    }
    vector<int> taker(m + 1, INT_MAX); 
    vector<int> res(n);
    int cnt = 0;
    auto place = [&](int idx) {
        if (taker[pref[idx][0]] == INT_MAX) {
            taker[pref[idx][0]] = idx;
            return 1;
        }
        int dx = 1, dc = taker[pref[idx][0]];
        taker[pref[idx][0]] = idx;
        while (true) {
            if (taker[pref[dc][0]] < dc &&
                taker[pref[dc][1]] < dc) {
                dx--; break;
            }
            if (taker[pref[dc][0]] > dc) {
                int temp = taker[pref[dc][0]];
                taker[pref[dc][0]] = dc;
                dc = temp;
            } else if (taker[pref[dc][1]] > dc) {
                int temp = taker[pref[dc][1]];
                taker[pref[dc][1]] = dc;
                dc = temp;
            }
            if (dc == INT_MAX) break;
        }
        return dx;
    };
    for (int i = n - 1; i >= 0; i--) {
        cnt += place(i);
        res[i] = cnt;
    }
    for (int i : res) cout << i << '\n';
}
/*
Simualte the adding of cows (aka interpret
the problem backwards).

For each new cow we add, that cow automatically
will get whatever cereal it wants. We then
reroute all the cows that might have issues.
*/