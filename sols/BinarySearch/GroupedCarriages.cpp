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
template<class T> using pqg = priority_queue<
    T, vector<T>, greater<T>>;
int main() {
	cin.tie(0) -> sync_with_stdio(0);
    int n; cin >> n;
    vector<int> a(n), d(n);
    for (int &i : a) cin >> i;
    for (int &i : d) cin >> i;
    vector<vector<pii>> events(n);
    for (int i = 0; i < n; i++) {
        if (a[i] == 0) continue;
        int l = max(0, i - d[i]);
        events[l].push_back({i + d[i], a[i]});
    }
    auto fn = [&](int z) -> bool {
        pqg<pii> pq;
        for (int i = 0; i < n; i++) {
            int cur = z; // capacity
            for (pii j : events[i]) pq.push(j);
            while (cur > 0 && sz(pq)) {
                auto [f, s] = pq.top(); pq.pop();
                int use = min(s, cur);
                s -= use, cur -= use;
                if (s > 0) pq.push({f, s});
            }
            if (sz(pq) && pq.top().f <= i) {
                return false; // left one behind
            }
        }
        return pq.empty();
    };
    int low = 0, high = 1e9;
    while (low < high) {
        int mid = low + (high - low) / 2;
        fn(mid) ? high = mid : low = mid + 1;
    }
    cout << low << "\n";
}
/**
 * TASK: Grouped Carriages (CF).
 * Obviously, a greater value of z provides more
 * flexibility. So, we can binary search on z.
 * 
 * For each carriage, we can create a segment of 
 * possible allocations, from [i - d_i, to i + d_i].
 * Then, iterate left to right on each cell. We obviously
 * want to prioritize those with a "smaller" right endpoint,
 * so process those first.
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