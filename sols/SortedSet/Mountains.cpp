#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define pb push_back
#define ins insert
#define f first 
#define s second 

const int N = 2e3;
set<int> edp[N];
int main() {
	cin.tie(0) -> sync_with_stdio(0);
    int n; cin >> n;
    vector<int> h(n);
    for (int& i : h) {
        cin >> i;
    }
    auto valid = [&](int i, int j, int k) {
        return ((ll) (h[j] - h[i]) * (k - i) <= 
                (ll) (h[k] - h[i]) * (j - i));
    };
    int tot = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (edp[i].empty()) {
                edp[i].insert(j);
            } else {
                if (valid(i, *edp[i].rbegin(), j)) {
                    edp[i].insert(j);
                }
            }
        }
        tot += sz(edp[i]);
    }
    int q; cin >> q;
    while (q--) {
        int x, y; cin >> x >> y; 
        --x, h[x] += y;
        for (int i = 0; i < x; i++) {
            tot -= sz(edp[i]);
            auto it = edp[i].upper_bound(x);
            while (it != end(edp[i])) {
                if (valid(i, x, *it)) {
                    break;
                } else {
                    int prv = *it;
                    it = edp[i].erase(it);
                }
            }
            it = prev(edp[i].lower_bound(x));
            if (valid(i, *it, x)) {
                edp[i].insert(x);
            }
            tot += sz(edp[i]);
        }
        tot -= sz(edp[x]), edp[x].clear();
        for (int i = x + 1; i < n; i++) {
            if (edp[x].empty()) {
                edp[x].insert(i);
            } else {
                if (valid(x, *edp[x].rbegin(), i)) {
                    edp[x].insert(i);
                }
            }
        }
        tot += sz(edp[x]);
        cout << tot << '\n';
    }
}
/**
 * TASK: Mountains (USACO Gold).
 * Store each possible right endpoint
 * for each possible left endpoint.
 * 
 * Observation 1:
 * The slope from i to an endpoint is 
 * monotonically increasing.
 * 
 * Proof: If the slope of the current
 * right endpoint wasn't greater than
 * the previous one, it wouldn't be visible.
 * 
 * With this observation, you can quickly
 * do updates in Nlog(N) amortized time.
*/