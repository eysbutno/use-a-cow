#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define pb push_back
#define ins insert
#define f first 
#define s second 

void solve() {
    int n; cin >> n;
    int mx = 0, ans = 0;
    for (int i = 1; i <= n; i++) {
        int c; cin >> c;
        mx = max(mx, c);
        if (mx == i) ++ans;
    }
    cout << ans << '\n';
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t; cin >> t;
    while (t--) solve();
}
/**
 * For any index i, 1 <= i <= n, 
 * if the maximum from the prefix
 * 1 to i is i, then there has to be
 * another connected component there.
 * The reason is because from the prefix
 * 1 to i, if the max is that, then everything
 * in that prefix (after the last update) will
 * connect to said element.
*/