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
    int n, m, q; cin >> n >> m >> q;
    vector<ll> t(n + 1), occ(m + 1);
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        t[i] = (ll) m * occ[x] + x;
        ++occ[x];
    }
    sort(all(t));
    for (int i = 1; i <= n; i++) {
        t[i] += n - i;
    }
    auto query = [&](ll k) {
        ll res = k;
        if (t[n] >= k) {
            int idx = lower_bound(all(t), k) 
                    - begin(t);
            res += idx - n - 1;
        }
        res %= m;
        return (res - 1 + m) % m + 1;
    };
    while (q--) {
        ll k; cin >> k;
        cout << query(k) << '\n';
    }
}
/**
 * TASK: D. Irrigation (CF)
 * Main idea is as follows:
 * Rectangle is m width, and is arbitrarily
 * tall. Normally, you'd fill in bottom up,
 * left to right. But, some cells have already
 * been filled in. So, if we just know how
 * many cells have been placed before this cell
 * would have been, we know how much to adjust
 * this current cell.
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