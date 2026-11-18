#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = array<int, 2>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

template<class T> bool smax(T &a, T b) {
    return a < b ? a = b, 1 : 0;
}
template<class T> bool smin(T &a, T b) {
    return a > b ? a = b, 1 : 0;
}
void solve() {
    int n; cin >> n;
    vector<vector<int>> nxt(n + 1);
    fill(all(nxt), vector<int>{-1});
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i], --a[i];
        nxt[a[i]].push_back(i);
    }
    int res = 0, l = n, r = n;
    for (int i = n - 1; i >= 0; i--) {
        if (a[i] == l || a[i] == r) {
            res += (l != r);
            (a[i] == l ? r : l) = a[i];
        } else {
            (nxt[l].back() > nxt[r].back() ? l : r) = a[i];
            ++res;
        }
        nxt[a[i]].pop_back();
    }
    cout << res << "\n";
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * B1. Painting the Array I (CF)
 * Greedy strategy is as follows:
 * 1. If this current element has one element the same,
 *    then append this current one to the other subsequence.
 * 2. If this current element has both other ones as being the same,
 *    then arbitrarily append it somewhere.
 * 3. Otherwise, append it to the subsequence with the next
 *    occurence that is nearer.
 * I'm too unskilled to prove this works, but like, it probably works.
 * And I really don't wanna figure out a DP bash.
*/