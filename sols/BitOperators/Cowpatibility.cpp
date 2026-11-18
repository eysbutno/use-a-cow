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
const int N = 2e5;
vector<int> adj[N];
int v[N];
void solve() {
    int n, m; cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    for (int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        adj[--x].pb(--y);
    }
}
int main() {
	cin.tie(0) -> sync_with_stdio(0);
    int t; cin >> t;
    while (t--) solve();
}
/**
 * TASK: Transitive Graph.
 * OK, for very obvious reasons we can't
 * just directly construct the graph. No 
 * brainer.
*/
/* Stuff to look for:
	* Overflow, OOB.
	* Corner Cases.
	* Do something, stay organized!
	* WRITE STUFF!
	* THINK OF MULTIPLE APPROACHES
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