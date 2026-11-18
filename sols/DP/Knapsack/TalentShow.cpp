#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define pb push_back
#define ins insert
#define f first 
#define s second 

const ll LINF = 1e18;
template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
int wt[250], tal[250];
bool check(int y, int n, int w) {
    vector<ll> dp(w + 1, -LINF);
    dp[0] = 0;
    for (int i = 0; i < n; i++) {
        ll cont = 1000LL * tal[i] - (ll) y * wt[i];
        for (int j = w; j >= 0; j--) {
            int fut = min(w, j + wt[i]);
            if (dp[j] != -LINF) {
                smax(dp[fut], dp[j] + cont);
            }
        }
    }
    return dp[w] >= 0;
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    freopen("talent.in", "r", stdin);
    freopen("talent.out", "w", stdout);
    int n, w; cin >> n >> w;
    int ratio = 0;
    for (int i = 0; i < n; i++) {
        cin >> wt[i] >> tal[i];
        smax(ratio, (tal[i] + wt[i] - 1) / wt[i]);
    }
    int low = 0, high = 1000 * ratio;
    while (low < high) {
        int mid = (low + high + 1) / 2;
        check(mid, n, w) ? low = mid : high = mid - 1;
    }
    cout << low << '\n';
}
/**
 * TASK: Talent Show.
 * Observation 1:
 * For a given result x, we just need 
 * to make sure the following inequalities
 * are satisfied:
 * Sum (i in S) (1000T_i - 1000xW_i) >= 0
 * Sum (i in S) W_i >= w.
 * Note that we binary search on 1000x.
 * 
 * Also, once we reach a weight >= w, we
 * don't need to keep track of the EXACT weight,
 * rather the new possible value of the 
 * "talent adjusted score". This is because
 * any weight above or equal the threshold
 * is valid.
*/