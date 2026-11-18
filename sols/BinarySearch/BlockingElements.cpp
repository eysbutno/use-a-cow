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
 
template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int& i : a) {
        cin >> i;
    }
    auto check = [&](ll mid) {
        set<pair<ll, int>> pos;
        vector<ll> dp(n + 1);
        pos.ins({0, n});
        dp[n] = 0;
        ll sum = 0;
        int ptr = n;
        for (int i = n - 1; i >= 0; i--) {
            while (sum > mid) {
                sum -= a[ptr - 1];
                pos.erase({dp[ptr], ptr});
                --ptr;
            }
            dp[i] = begin(pos) -> f + a[i];
            pos.ins({dp[i], i});
            sum += a[i];
        }
        sum = 0;
        for (int j = 0; j < n; j++) {
            if (sum <= mid && dp[j] <= mid) {
                return true;
            }
            sum += a[j];
        }
        return false;
    };
    ll low = 0, high = 1e14;
    while (low < high) {
        ll mid = low + (high - low) / 2;
        check(mid) ? high = mid : low = mid + 1;
    }
    cout << low << "\n";
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t; cin >> t;
    while (t--) solve();
}
/**
 * Binary search the final answer. 
 * Let dp[i] be the minimum cost to
 * have [i, n] be properly blocked off,
 * given that cell i is blocked. Then, we
 * can perform the following transition:
 * dp[i] = a[i] + min(dp_i+1->k), where k
 * is the last index where the suffix is 
 * <= the result. Then, if there's a possible
 * partition, we return true.
*/