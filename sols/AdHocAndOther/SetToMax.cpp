#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define ckmin(a, b) a = min(a, b)
#define ckmax(a, b) a = max(a, b)
#define pb push_back
#define ins insert
#define f first 
#define s second 

void solve() {
    int n; cin >> n;
    vector<int> a(n), b(n);
    for (int& i : a) {
        cin >> i;
    }
    for (int& i : b) {
        cin >> i;
    }
    vector<bool> ok(n);
    for (int i = 0; i < 2; i++) {
        deque<int> s;
        for (int j = 0; j < n; j++) {
            while (!s.empty() && s.back() < a[j]) {
                s.pop_back();
            }
            s.push_back(a[j]);
            while (!s.empty() && s.front() > b[j]) {
                s.pop_front();
            }
            if (!s.empty() && s.front() == b[j]) {
                ok[j] = true;
            }
        }       
        reverse(begin(a), end(a));
        reverse(begin(b), end(b));
        reverse(begin(ok), end(ok));
    }
    for (int i = 0; i < n; i++) {
        if (!ok[i]) {
            cout << "NO" << '\n';
            return;
        }
    }
    cout << "YES" << '\n';
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t; cin >> t;
    while (t--) solve();
}
/**
 * Instead of manually performing
 * the operations, try to see if
 * it's possible to make a series of
 * operations that will work.
 * 
 * Perform two sweeps: L -> R, and R -> L.
 * In each sweep, maintain a deque of
 * possible locations.
 * 
 * (Stack also works; deque just easier to
 * implement for this problem)
 * 
 * Deque logic:
 * Pop any recent elements that are too small.
 * Pop back elements that are too big.
 * 
 * The deque will be monotonic for obvious reasons.
*/