#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define f first 
#define s second

void solve() {
	int n; cin >> n;
	vector<int> p(n + 1), d(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> p[i]; p[i] /= 100;
	}
	sort(begin(p), end(p));
	reverse(begin(p) + 1, end(p));
	for (int i = 0; i < 2; i++) {
		int x, a; cin >> x >> a;
		for (int j = 1; a * j <= n; j++) {
			d[a * j] += x;
		}
	}
	ll k; cin >> k;
	auto check = [&](int mid) {
		ll tot = 0;
		vector<int> b(mid + 1);
		for (int i = 1; i <= mid; i++) {
			b[i] = d[i];
		}
		sort(begin(b), end(b));
		reverse(begin(b) + 1, end(b));
		for (int i = 1; i <= mid; i++) {
			tot += p[i] * b[i];
		}
		return tot >= k;
	};
	int low = 0, high = n, ans = -1;
	while (low < high) {
        int mid = low + (high - low) / 2;
        if (check(mid)) {
			high = mid;
		} else {
			low = mid + 1;
		}
    }
	if (check(low)) ans = low;
	cout << ans << '\n';
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	int t; cin >> t;
	while (t--) solve();
}
/*
Binary search your answer.
*/