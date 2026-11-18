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
template <class T> class ST {
	private:
		const T DEF = -1e18;
		int len; vector<T> t;
	public:
		ST(int len) : len(len),
			t(len * 2, DEF) {}
		void set(int idx, T val) {
			idx += len;
			t[idx] = val;
			for (; idx > 1; idx /= 2) {
				t[idx / 2] = max(t[idx], t[idx ^ 1]);
			}
		}
		T query(int l, int r) {
			T res = DEF;
			for (l += len, r += len; l < r; l /= 2, r /= 2) {
				if (l & 1) smax(res, t[l++]);
				if (r & 1) smax(res, t[--r]);
			}
			return res;
		}
		T get(int idx) {
			return query(idx, idx + 1);
		}
};
void solve() {
	int n; cin >> n;
	vector<int> a(n + 1);
	map<ll, int> mp;
	ll pref = 0;
	for (int i = 1; i <= n; i++) {
		cin >> a[i], pref += a[i];
		mp[pref] = -1;
	}
	mp[0] = -1;
	int run = 0;
	for (auto &[k, v] : mp) {
		v = run++;
	}
	ST<ll> rmq1(run + 1), rmq2(run + 1);
	rmq1.set(mp[0], 0), rmq2.set(mp[0], 0);
	vector<ll> dp(n + 1, -1e18);
	vector<ll> zero(run + 1, -1e18);
	zero[mp[0]] = 0, pref = 0, dp[0] = 0;
	for (int i = 1; i <= n; i++) {
		pref += a[i];
		int idx = mp[pref];
		dp[i] = max(zero[idx], dp[i - 1] + 
					(a[i] > 0) - (a[i] < 0));
		smax(dp[i], i + rmq1.query(0, idx));
		smax(dp[i], rmq2.query(idx + 1, run + 1) - i);
		smax(zero[idx], dp[i]);
		if (rmq1.get(idx) < dp[i] - i) {
			rmq1.set(idx, dp[i] - i);
		}
		if (rmq2.get(idx) < dp[i] + i) {
			rmq2.set(idx, dp[i] + i);
		}
	}
	cout << dp[n] << '\n';
}
int main() {
	cin.tie(0) -> sync_with_stdio(0);
	int t = 1; cin >> t;
	while (t--) solve();
}
/**
 * Define dp[i] to be the maximum partition of the
 * prefix i. To efficiently transition, do the following:
 * 
 * Maintain two RMQs:
 * 1. This one is for when you want to have
 * a positive number being added to the segment.
 * This queries dp[i] - i.
 * 2. This queries when you want to minimize
 * the total "loss" from a negative segment.
 * This queries dp[i] + i.
*/