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
	int n; cin >> n;	
	stack<pii> mn, mx, itvs;
	ll res = 0, cur = 0;
	auto del = [&](int l, int r) -> void {
		// delete the interval of [l, r]
		while (sz(itvs)) {
			auto [f, s] = itvs.top();
			if (s >= l) {
				// intervals are not disjoint
				itvs.pop(), cur -= s - f + 1;
				if (f < l) {
					// can still keep this part
					itvs.push({f, l - 1});
					cur += l - f;
				}
			} else {
				break; // intervals are disjoint
			}
		}
	};
	auto add = [&](int l, int r) -> void {
		// add the interval of [l, r] to answer
		del(l, r); // in case of duplicates
		itvs.push({l, r}); // adding to itvs
		cur += r - l + 1;
	};
	for (int i = 0; i < n; i++) {
		int p; cin >> p;
		int ns = -1, nl = -1;
		while (sz(mn) && mn.top().f > p) {
			mn.pop(); // mono-decreasing
		}
		if (sz(mn)) ns = mn.top().s;
		while (sz(mx) && mx.top().f < p) {
			mx.pop(); // mono-increasing
		}
		if (sz(mx)) nl = mx.top().s;
		mx.push({p, i}), mn.push({p, i});
		add(nl + 1, i), del(ns + 1, i);
		res += cur;
	}
	cout << res << '\n';
}
/**
 * TASK: E. Max to the Right of Min.
 * For every endpoint, count the # of "good"
 * segments. We explicitly maintain the intervals
 * of good endpoints. This interval does not change
 * all that much when forcing this current endpoint.
 * Let NS be the nearest element that's smaller, and NL
 * the nearest element that's bigger. Then, we only
 * need to update the following:
 * 1. [ns + 1, i] is no longer suitable, because i is the
 * minpos value, so there can be no suitable intervals here.
 * 2. [nl + 1, i] is now suitable, because i is maxpos on all
 * of these intervals.
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