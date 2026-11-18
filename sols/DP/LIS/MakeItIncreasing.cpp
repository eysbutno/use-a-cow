#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define f first 
#define s second 

template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
int main() {
	cin.tie(0) -> sync_with_stdio(0);
    int n, k; cin >> n >> k;
    vector<int> a(n + 2), b(k + 2);
    a[0] = -2e9, a[n + 1] = 2e9;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    b[0] = 0, b[k + 1] = n + 1;
    for (int i = 1; i <= k; i++) {
        cin >> b[i];
    }
    for (int i = 0; i <= n + 1; i++) {
        a[i] -= i;
    }
    for (int i = 1; i <= k + 1; i++) {
        if (a[b[i - 1]] > a[b[i]]) {
            cout << -1 << '\n';
            return 0;
        }
    }
    auto calc = [&](int l, int r, int mn, int mx){
        if (l > r) return 0; // invalid
        vector<int> lis;
        for (int i = l; i <= r; i++) {
            if (a[i] < mn) continue; // invalid
            if (a[i] > mx) continue; // invalid
            int idx = upper_bound(all(lis), a[i])
                    - begin(lis);
            if (idx == sz(lis)) {
                lis.push_back(a[i]);
            } else {
                lis[idx] = a[i];
            }
        }
        return sz(lis);
    };
    int tot = 0;
    for (int i = 1; i <= k + 1; i++) {
        int l = b[i - 1], r = b[i],
            lis = calc(l + 1, r - 1, a[l], a[r]);
        tot += (r - l - 1) - lis;
    }
    cout << tot << '\n';
}
/**
 * TASK: Make It Increasing (CF).
 * Subtract everything by its given index,
 * so that ties are allowed.
 * 
 * For each index, you now have to figure out
 * how to make the #s between b_i equal. The best
 * way to do this, (I THINK), is to find the longest
 * non-decreasing sequence starting at the left endpoint.
 * Then, you replace everything else.
 * 
 * More justification for why it would be the longest 
 * non-decreasing sequence: 
 * You will need to find some subsequence of numbers, within
 * said interval, that won't be changed. Naturally, you would want
 * to make such a subsequence as long as possible....
*/
/**
  * 1. Can a graph be constructed?
  * 2. How can we reuse information?
  * 3. Monotonicity? Concavity? Anything else?
  * 4. Prove/justify any observations.
  * 5. If there are 1e9+7 edge cases and it's
  *    impossible to implement, maybe it's not right.
  * 6. For math formulas, try rewriting them.
  * 7. Break down the problem, or maybe reframe it.
  * 8. Loop through common techniques... binary search?
  *    DP? DFS/BFS/Graphs? 
  * 9. If your idea is almost certainly right, try some
  *    optimization techniques. Small to large merging?
  *    Deleting unnecessary stuff? Using a set? IDK.
*/