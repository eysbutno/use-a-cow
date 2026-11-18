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
	vector<int> a(n * 2);
	for (int i = 1; i < n * 2; i++) {
		cin >> a[i];
	}
	auto check = [&](int x) -> bool {
		// returns: median >= x.
		for (int i = 0; i < n; i++) {
			if ((a[n + i] >= x && a[n + i + 1] >= x) ||
				(a[n - i] >= x && a[n - i - 1] >= x)) {
				return true;
			}
			if ((a[n + i] < x && a[n + i + 1] < x) ||
				(a[n - i] < x && a[n - i - 1] < x)) {
				return false;
			}
		}
		return a[1] >= x;
	};
	int low = 1, high = n * 2 - 1;
	while (low < high) {
		int mid = (low + high + 1) / 2;
		check(mid) ? low = mid : high = mid - 1;
	}
	cout << low << '\n';
}
/**
 * TASK: Median Pyramid (Hard).
 * Binary search on the value of x, so
 * the "pyramid" is now just 0s and 1s.
 * 
 * Observation 1: Intervals of 0s and 1s persist
 * to the next row, until they "collide".
 * 
 * Observation 2: Closest interval of length >=
 * 2 dictates the answer.
 * Proof: If we iterate over length two intervals,
 * either everything will naturally collide until it
 * gets to the top, or smth. IDK.
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