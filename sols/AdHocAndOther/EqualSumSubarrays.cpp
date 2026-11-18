#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define mp(x, y) make_pair(x, y)
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
    vector<ll> a(n);
    for (ll& i : a) {
        cin >> i;
    }
    vector<pair<ll, pii>> sub;
    for (int i = 0; i < n; i++) {
        ll tot = 0;
        for (int j = i; j < n; j++) {
            tot += a[j];
            sub.pb({tot, {i, j}});
        }
    }
    sort(all(sub));
    auto inside = [&](pair<ll, pii> itv, int i) {
        return itv.s.f <= i && itv.s.s >= i;
    };
    for (int i = 0; i < n; i++) {
        ll res = INT64_MAX;
        for (int j = 1; j < sz(sub); j++) {
            if (inside(sub[j - 1], i) != inside(sub[j], i)) {
                smin(res, abs(sub[j - 1].f - sub[j].f));
            }
        }
        cout << res << '\n';
    }
}
/**
 * TASK: Equal Sum Subarrays.
 * Observation 1: The answer is just
 * the minimum difference between subarrays
 * including an index i, and subarrays excluding
 * an index i.
*/