#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define pb push_back
#define f first 
#define s second 

template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
void solve() {
	int n; cin >> n;
	vector<ll> a(n + 2), d(n + 2);
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for (int i = 1; i <= n; i++) {
		cin >> d[i];
	}
	d[0] = INT64_MAX, d[n + 1] = INT64_MAX;
	// border cells, just ignore
	set<int> alive, cur;
	for (int i = 0; i < n + 2; i++) {
		alive.insert(i);
		cur.insert(i);
	}
	for (int i = 0; i < n; i++) {
		set<int> die, nCur;
		for (int j : cur) {
			auto it = alive.find(j);
			if (it == end(alive)) continue;
			int prv = *prev(it), nxt = *next(it);
			if (a[prv] + a[nxt] > d[j]) {
				die.insert(j);
				nCur.insert(prv);
				nCur.insert(nxt);
			}
		}
		for (int j : die) {
			alive.erase(j);
			nCur.erase(j);
		}
		cur = nCur;
		cout << sz(die) << ' ';
	}
	cout << '\n';
}
int main() {
	cin.tie(0) -> sync_with_stdio(0);
	int t; cin >> t;
	while (t--) solve();
}
/**
 * TASK: Berserk Monsters.
 * Main idea is that we only need to 
 * consider monsters that are on the
 * two sides of a monster that just died.
 * So, we can just abuse sets and get a
 * O(NlogN) solution.
 * 
 * (Man, this was a pain to implement.)
*/