#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define pb push_back
#define ins insert
#define f first 
#define s second 

const int MAX = 1.5e5 + 1;
vector<int> bad[4][MAX];
int c[4][MAX];
int dp[4][MAX];
int main() {
    vector<int> n(4);
    for (int& i : n) {
        cin >> i;
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < n[i]; j++) {
            cin >> c[i][j];
            if (i == 0) {
                dp[i][j] = c[i][j];
            }
        }
    }
    for (int i = 0; i < 3; i++) {
        int m; cin >> m;
        for (int j = 0; j < m; j++) {
            int x, y; cin >> x >> y;
            bad[i][--y].pb(--x);
        }
    }
    for (int i = 0; i < 3; i++) {
        multiset<int> s;
        for (int j = 0; j < n[i]; j++) {
            s.insert(dp[i][j]);
        }
        for (int j = 0; j < n[i + 1]; j++) {
            for (int k : bad[i][j]) {
                s.erase(s.find(dp[i][k]));
            }
            if (s.empty()) {
                dp[i + 1][j] = 2e9;
            } else {
                dp[i + 1][j] = c[i + 1][j] 
                    + *s.begin();
            }
            for (int k : bad[i][j]) {
                s.insert(dp[i][k]);
            }
        }
    }
    int res = 2e9;
    for (int i = 0; i < n[3]; i++) {
        res = min(res, dp[3][i]);
    }
    if (res >= 2e9) {
        res = -1;
    }
    cout << res << '\n';
}
/**
 * Just DP it. State transitions
 * are between the next meal
 * option.
*/