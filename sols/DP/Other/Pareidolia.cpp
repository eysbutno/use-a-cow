#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define mp(a, b) make_pair(a, b)
#define f first 
#define s second 

pii dp[200001][7];
string b = "bessie";
pii operator+(pii p1, pii p2) {
    return make_pair(p1.f + p2.f, p1.s + p2.s);
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    string s; cin >> s;
    int n = s.length();
    s = " " + s; // 1 indexing
    vector<int> cost(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> cost[i];
    }
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= 7; j++) {
            dp[i][j] = {-1, 1e9};
        }
    }
    dp[0][0] = {0, 0};
    auto bet = [&](pii a, pii b) {
        return (a.f > b.f || (a.f == b.f && a.s < b.s));
    };
    auto opt = [&](pii a, pii b) {
        return (bet(a, b) ? a : b);
    };
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= 6; j++) {
            dp[i][j] = dp[i - 1][j] + mp(0, cost[i]);
            if (s[i] == b[j - 1]) {
                dp[i][j] = opt(dp[i][j], dp[i - 1][j - 1]);
            }
        }
        dp[i][0] = opt(dp[i - 1][0], dp[i][6] + mp(1, 0));
    }
    cout << dp[n][0].f << '\n'
        << dp[n][0].s << '\n';
}
/**
 * TASK: Pareidolia.
 * Maintain dp[i][j], where i is the index,
 * and j is the character that needs to be
 * processed (after this state).
 * 
 * (My god, I really can't implement.)
*/