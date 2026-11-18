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

bitset<1 << 20> dp[2];
vector<int> msks[1001];
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n, m; cin >> n >> m;
    vector<int> a(n), b(m);
    for (int& i : a) cin >> i;
    for (int& i : b) cin >> i; 
    for (int i = 0; i < (1 << m); i++) {
        int sum = 0;
        for (int j = 0; j < m; j++) {
            if (i >> j & 1) sum += b[j];
        }
        if (sum <= 1000) msks[sum].pb(i);
    }  
    for (int i : msks[a[0]]) {
        dp[0][i] = true;
    }
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < (1 << m); j++) {
            if (!dp[0][j]) continue;
            for (int k : msks[a[i]]) {
                if (!(j & k)) dp[1][j | k] = 1;
            }
        }     
        dp[0].reset();
        swap(dp[0], dp[1]);
    } 
    for (int i = 0; i < (1 << m); i++) {
        if (dp[0][i]) {
            cout << "YES" << '\n';
            return 0;
        }
    }
    cout << "NO" << '\n';
}
/**
 * NOTE: This solution is like, ridiculously
 * cheese because it relies on a bunch of optimizations
 * and is pretty easily hacked.
*/