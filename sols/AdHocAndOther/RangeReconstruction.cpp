#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define pb push_back
#define ins insert
#define f first 
#define s second 

int main() {
    int n; cin >> n;
    vector<vector<int>> arr(n);
    for (int i = 0; i < n; i++) {
        for (int j = n - i; j > 0; j--) {
            int r; cin >> r;
            arr[i].pb(r);
        }
    }
    reverse(begin(arr), end(arr));
    vector<int> res(n);
    auto check = [&](int idx) {
        for (int i = 1; i <= idx; i++) {
            int mn = 2e9, mx = -2e9;
            int pos = i;
            for (int j : arr[i]) {
                mn = min(mn, res[pos]);
                mx = max(mx, res[pos]);
                if (mx - mn != j) return false;
                --pos;
            }
        }
        return true;
    };
    for (int i = 1; i < n; i++) {
        res[i] = res[i - 1] + arr[i][1];
        if (!check(i)) {
            res[i] = res[i - 1] - arr[i][1];
        }
    }
    reverse(begin(res), end(res));
    for (int i = 1; i < n; i++) {
        cout << res[i - 1] << ' ';
    }
    cout << res.back() << '\n';
}
/**
 * Build backwards. Set a_n = 0.
 * For each new element, set a_n - 1
 * to a_n + r, or a_n - r.
 * 
 * (I thought of this, but then disregarded
 * it because I thought at some point there'd
 * be a point where there are two possible options,
 * then it wouldn't work.)
*/