#include <bits/stdc++.h>
using namespace std;
#define f first 
#define s second

int main() {
	freopen("reduce.in", "r", stdin);
	freopen("reduce.out", "w", stdout);
	int n; cin >> n;
	vector<pair<int, int>> locs(n);
	for (auto& i : locs) {
		cin >> i.f >> i.s;
	}
	set<pair<int, int>> pts;
	sort(begin(locs), end(locs),
		[&](auto& x, auto& y) {
		if (x.f == y.f) return x.s < y.s;
		return x.f < y.f;
	});
	for (int i = 0; i < 4; i++) {
		pts.insert(locs[i]);
		pts.insert(locs[n - 1 - i]);
	}
	sort(begin(locs), end(locs),
		[&](auto& x, auto& y) {
		if (x.s == y.s) return x.f < y.f;
		return x.s < y.s;
	});
	for (int i = 0; i < 4; i++) {
		pts.insert(locs[i]);
		pts.insert(locs[n - 1 - i]);
	}
	int res = 2e9, sz = size(pts);
	vector<pair<int, int>> opts(begin(pts), end(pts));
	auto check = [&](int c1, int c2, int c3) {
		set<pair<int, int>> st = pts;
		st.erase(opts[c1]);
		st.erase(opts[c2]);
		st.erase(opts[c3]);
		vector<pair<int, int>> aft(begin(st), end(st));
		int dx = aft[size(aft) - 1].f - aft[0].f;
		sort(begin(aft), end(aft), 
			[&](auto& x, auto& y) {
			return x.s < y.s;
		});
		int dy = aft[size(aft) - 1].s - aft[0].s;
		return dx * dy;
	};
	for (int i = 0; i < sz; i++) {
		for (int j = i + 1; j < sz; j++) {
			for (int k = j + 1; k < sz; k++) {
				res = min(res, check(i, j, k));
			}
		}
	}
	cout << res << '\n';
}
/*
Brute force the cows that
are removed out of the set 
of the first & last 3 cows
when sorted by row & col.
*/