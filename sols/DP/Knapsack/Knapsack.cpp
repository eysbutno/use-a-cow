#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define pb push_back
#define ins insert
#define f first 
#define s second 
    
template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
ll dp[2001], cnt[2001];
map<int, int> wt[2001];
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int s, n; cin >> s >> n;
    for (int i = 0; i < n; i++) {
        int v, w, k; cin >> v >> w >> k;
        wt[w][v] += k, cnt[w] += k;
    }
    for (int i = 1; i <= s; i++) {
        while (cnt[i] > s / i) {
            int dx = cnt[i] - (s / i);
            auto [k, v] = *begin(wt[i]);
            if (dx >= v) {
                cnt[i] -= v;
                wt[i].erase(k);
            } else {
                wt[i][k] -= dx;
                cnt[i] = 0;
            }
        }
    }
    for (int i = 1; i <= s; i++) {
        for (int j = s; j >= 0; j--) {
            ll cnt = 0, sum = 0;
            auto it = end(wt[i]);
            while (it != begin(wt[i])) {
                it = prev(it);
                auto [k, v] = *it;
                bool done = false;
                for (int l = 0; l < v; l++) {
                    ++cnt, sum += k;
                    if (j - i * cnt < 0) {
                        done = true; break;
                    }
                    smax(dp[j], sum + dp[j - i * cnt]);
                }
                if (done) break;
            }
        }
    }
    cout << dp[s] << '\n';
}
/**
 * The "quintessential" knapsack. 
 * Given a capacity, a weight, and
 * a lot of items. Note that you wouldn't
 * use this algorithm if N was small, and
 * S was big.
*/