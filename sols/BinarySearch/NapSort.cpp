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

void solve() {
	int n; cin >> n;
	vector<ll> a(n);
	for (ll& i : a) {
		cin >> i;
	}
	sort(all(a));
	auto check = [&](ll div) {
		ll diff = div, idx = 0;
		for (ll i = div; diff > 0; i += diff) {
			int loc = lower_bound(begin(a) + idx, end(a), i) 
					- begin(a);
			if (loc == n) break;
			--diff, idx = loc + 1; 
		}
		return idx == n;
	};
	ll low = 1, high = n;
	while (low < high) {
		int mid = (low + high) / 2;
		check(mid) ? high = mid : low = mid + 1;
	}
	ll rep = low * (low + 1) / 2;
	cout << min(a.back(), rep) << '\n';
}
int main() {
	cin.tie(0) -> sync_with_stdio(0);
	int t; cin >> t;
	while (t--) solve();
}
/**
 * So, we binary search on the least 
 * # of replacements Bessie can do, such
 * that the last element is replaced. Now,
 * the idea is to replace the indices Bessie
 * sorts with the time she inserts them.
 * So, if we can replace with our last indice
 * at location n - 1, then we can sort everything
 * in (indices bessie takes) * (idx she takes + 1) / 2
 * time.
*/