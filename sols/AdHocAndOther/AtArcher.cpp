#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define pb push_back
#define ins insert
#define f first 
#define s second 

struct Update {
	ll t, dx, p, c;
	bool operator<(const Update& other) const {
		return (t == other.t) ? dx > other.dx : t > other.t;
	}
};
int main() {
	cin.tie(0) -> sync_with_stdio(0);
	ll n, m, d; cin >> n >> m >> d;
	vector<ll> r(m + 1), s(m);
	for (ll& i : r) cin >> i;
	for (ll& i : s) cin >> i;
	vector<ll> LOCS;
	s.pb(0), r.pb(1e18);
	for (int i = 1; i <= m + 1; i++) {
		LOCS.pb(-r[i]), LOCS.pb(r[i]);
	}
	sort(all(LOCS));
	auto score = [&](ll loc) {
		loc = abs(loc);
		int idx = lower_bound(all(r), loc) - begin(r);
		if (idx == 0) return s[0];
		return s[idx - 1];
	};
	auto nxt = [&](ll loc) {
		ll nw = *lower_bound(all(LOCS), loc);
		if (nw == loc && nw < 0) nw = *upper_bound(all(LOCS), loc); 
		if (nw > 0) ++nw;
		return nw;
	};
	const ll st = (ll) -(n * d) / 2;
	ll cur = 0, res = 0;
	priority_queue<Update> q;
	for (int i = 0; i < n; i++) {
		ll pos = st + (ll) d * i;
		ll sc = score(pos), fut = nxt(pos);
		q.push({fut - pos, score(fut) - sc, pos, fut});
		cur += sc, res = cur;
	}
	while (!q.empty()) {
		auto [t, dx, p, c] = q.top(); q.pop();
		if (t > d) break;
		cur += dx, res = max(res, cur);
		ll fut = nxt(c), sc = score(fut);
		q.push({t + fut - c, sc - score(c), c, fut});
	}
	cout << res << '\n';
}
/**
 * TASK: AtArcher.
 * By doing some mathy math, we find that
 * our first arrow should lie in the following
 * interval:
 * [-(n * d) / 2, -(n * d) + d].
 * 
 * So, to solve this problem, you simply maintain
 * a sliding window and "update" whenever one arrow
 * goes into another range.
 * 
 * Time Complexity: Tough to judge, but it's linear,
 * with maybe a log factor. At the very least, there's
 * super strong amortization.
*/