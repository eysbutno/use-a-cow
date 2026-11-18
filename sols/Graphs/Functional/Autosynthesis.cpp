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
void solve() {
    int n; cin >> n;
    vector<int> a(n), deg(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i], --a[i];
        ++deg[a[i]];
    }
    vector<int> res, col(n);
    vector<bool> seen(n);
    { // eliminate nodes not in the cycle.
        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (!deg[i]) q.push(i), col[i] = 1;
        }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            seen[u] = col[u] = 1;
            if (!seen[a[u]] && !(--deg[a[a[u]]])) {
                q.push(a[a[u]]);
            }
            seen[a[u]] = 1;
        }
    }
    { // process nodes in the cycle.
        for (int i = 0; i < n; i++) {
            if (seen[i]) continue;
            int ptr = a[i], cnt = 1;
            seen[i] = true;
            while (ptr != i) {
                if (cnt & 1) col[ptr] = 1;
                seen[ptr] = 1, ptr = a[ptr], ++cnt;
            }
            if (cnt & 1) {
                cout << -1 << "\n";
                return;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (col[i]) res.push_back(a[i]);
    }
    cout << sz(res) << "\n";
    for (int i : res) {
        cout << i + 1 << " ";
    }
    cout << "\n";
}
int main() {
	cin.tie(0) -> sync_with_stdio(0);
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * TASK: C. Autosynthesis (CF)
 * Problem Statement:
 * 1. Given an array a.
 * 2. Choose a series of indices, so that
 *    the indices you "circle" are identical
 *    to the set of remaining vertices.
 * 
 * Draw an edge between each index i, and index a[i].
 * 
 * Then, for each (x -> y), if one value of x is
 * uncircled, then y is circled. Otherwise,
 * y is uncircled.
 * 
 * So, we can remove all edges not in a cycle, and process
 * each cycle element.
*/
/**
  * 1. Can a graph be constructed?
  *    - Think of relations
  *    - If an explicit graph is given,
  *      think of "additions" you can make.
  * 2. How can we reuse information?
  *    - Like DP, but slightly more general.
  * 3. Prove/justify any observations.
  *    - At least, it should be easy mentally.
  * 4. For math formulas, try rewriting them.
  *    - Make it something easier to work with.
  * 5. Break down the problem, or maybe reframe it.
  *    - Can you make it into a simpler problem.
  * 6. Try multiple techniques.
  *    - DP, Greedy, Graph, etc.
*/