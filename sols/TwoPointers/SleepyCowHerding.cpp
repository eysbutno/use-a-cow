#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    freopen("herding.in", "r", stdin);
    freopen("herding.out", "w", stdout);
    int n; cin >> n;
    vector<int> locs(n);
    for (int& i : locs) cin >> i;
    sort(begin(locs), end(locs));
    int r = 0, cnt = 0, dist = 0;
    for (int l = 0; l < n; l++) {
        for (; r < n; r++) {
            if (locs[r] - locs[l] + 1 > n) {
                --r; break;
            }
        }
        if (r == n) --r;
        int res = r - l + 1, dx = locs[r] - locs[l] + 1;
        if (res > cnt || (res == cnt && cnt == n - 1
            && dist == n - 1 && dx != dist)) {
            cnt = res, dist = dx;
        }
    }
    if (cnt == n - 1 && cnt == dist) {
        cout << 2 << '\n';
    } else {
        cout << n - cnt << '\n';
    }
    cnt = 0;
    for (int i = 1; i < n; i++) {
        cnt += locs[i] - locs[i - 1] - 1;
    }
    cout << cnt - min(locs[1] - locs[0] - 1,
        locs[n - 1] - locs[n - 2] - 1);
}