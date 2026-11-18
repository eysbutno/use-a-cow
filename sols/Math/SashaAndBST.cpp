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
const int MOD = 998244353;
const int N = 5e5 + 1;
ll fact[N], invFact[N];
ll expo(ll x, ll n) {
    x %= MOD;
    ll res = 1;
    while (n > 0) {
        if (n % 2) res = res * x % MOD;
        x = x * x % MOD;
        n >>= 1;
    }
    return res;
}
ll inv(ll x) {
    return expo(x, MOD - 2);
}
ll binom(int n, int k) {
    return (fact[n] * invFact[k] % MOD * 
            invFact[n - k]) % MOD;
}
void buildMathArray() {
    fact[0] = 1, invFact[0] = 1;
    for (int i = 1; i < N; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
        invFact[i] = inv(fact[i]);
    }
}
void solve() {
	int n, c; cin >> n >> c;
	vector<array<int, 2>> adj(n);
	vector<int> val(n);
	for (int i = 0; i < n; i++) {
		int l, r, w;
		cin >> l >> r >> w;
		adj[i] = {--l, --r};
		val[i] = w;
	}
	vector<int> ord = {1};
	auto dfs = [&](int u, auto&& dfs) -> void {
		if (u < 0) return;
		dfs(adj[u][0], dfs);
		ord.push_back(val[u]);
		dfs(adj[u][1], dfs);
	}; dfs(0, dfs);
	ord.push_back(c);
	ll res = 1;
	int cur = 0, lb = -1, rb = -1;
	auto process = [&]() {
		ll mult = invFact[cur];
		int dx = rb - lb;
		for (int i = dx + 1; i <= dx + cur; i++) {
			mult *= i, mult %= MOD;
		}
		res *= mult, res %= MOD;
	};
	for (int i : ord) {
		if (i == -1) {
			++cur;
		} else if (cur == 0) {
			lb = i;
		} else {
			rb = i, process();
			lb = i, rb = i, cur = 0;
		}
	}
	cout << res << '\n';
}
int main() {
	cin.tie(0) -> sync_with_stdio(0);
	buildMathArray();
	int t = 1; cin >> t;
	while (t--) solve();
}
/**
 * TASK: Sasha and BST (CF).
 * Observation 1:
 * The inorder traversal of a BST prints
 * out the vertices in SORTED ORDER.
 * 
 * Man, I really suck at AP CS. Anyways,
 * then just stars and bars it.
 * 
 * Formula for multiplication:
 * Call rb - lb dx. Then, multiply answer by:
 * (len + dx, choose len).
 * This can be rewritten as:
 * ((dx + 1) * (dx + 2)...(dx + len)) / len!
 * (Note that sum of len is bounded by N)
*/
/**
  * Make observations.
  * Try out various techniques in your head.
  * See if there are some "restrictions" that you
  * can place, to limit it to a set of states. This
  * often makes life a million times easier!
  * Actually do something and don't just stare at
  * the screen....!
*/
/*
const int MOD = 1e9 + 7;
template<class T> void add(T& a, T b) {
	a += b, a %= MOD;
}
template<class T> void sub(T& a, T b) {
	a > b ? a -= b : a -= b, a += MOD;
}
template<class T> void mul(T& a, T b) {
	a = (a * b) % MOD;
}
*/