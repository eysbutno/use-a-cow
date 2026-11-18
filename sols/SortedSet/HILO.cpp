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
int main() {
	int n; cin >> n;
	vector<int> a(n), mp(n + 1);
	for (int i = 0; i < n; i++) {
		cin >> a[i], mp[a[i]] = i;
	}
	vector<int> dx(n + 1);
	map<int, int> seen;
	for (int i = 0; i < n; i++) {
		int v = a[i];
		// transition from x = v - 1 to x = v
		// we assert that v goes from LO to HI.
		auto it = seen.upper_bound(v);
		if (it != end(seen)) {
			if (it == begin(seen) || 
				it -> s > prev(it) -> s) {
				++dx[v];
			}
		}
		if (mp[v - 1] > mp[v]) --dx[v];
		seen[v] = i;
	}
	int res = 0;
	for (int i : dx) {
		res += i, cout << res << '\n';
	}
}
/**
 * TASK: HILO (USACO 2021 Gold).
 * How many HILOs occur for a given index
 * x is closely tied to the changes that 
 * happen once position x goes from being
 * a HI to being a LO.
 * 
 * Case 1: The # of HILOs increases by 1.
 * This happens when there exists some previous
 * index j where p[j] > p[k]. We add one to
 * the answer if this p[j] is the minimal, or
 * if this index j is the "closest" to our index i.
 * 
 * Case 2 (not necessarily separate): 
 * The previous number v - 1 comes after 
 * the number v. Then, because that previously
 * was a HILO, we need to subtract 1.
*/