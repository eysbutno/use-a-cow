#include <bits/stdc++.h>
using namespace std; 
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define pb push_back
#define f first 
#define s second 

struct DSU {
    vector<int> e;
    DSU(int n) { 
        e = vector<int>(n, -1); 
    }
    int get(int x) { 
        return e[x] < 0 ? x : 
            e[x] = get(e[x]); 
    }
    bool connected(int a, int b) {
        return get(a) == get(b); 
    }
    int size(int x) { 
        return -e[get(x)]; 
    }
    bool unite(int x, int y) {
        x = get(x), y = get(y);
        if (x == y) return false;
        if (e[x] > e[y]) swap(x, y);
        e[x] += e[y];
        e[y] = x;
        return true;
    }
};
void solve() {
    int n, p; 
    cin >> n >> p;
    vector<int> a(n), idx(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        idx[i] = i;
    }
    sort(begin(idx), end(idx),
        [&](int& x, int& y) {
        return a[x] < a[y];
    });
    DSU dsu(n);
    ll cost = 0;
    int rem = n - 1;
    auto process = [&](int idx) {
        int l = idx, r = idx;
        while (l - 1 >= 0 && a[l - 1] % a[idx] == 0 
            && dsu.unite(idx, l - 1)) {
            --l, --rem, cost += a[idx];
        }
        while (r + 1 < n && a[r + 1] % a[idx] == 0
            && dsu.unite(idx, r + 1)) {
            ++r, --rem, cost += a[idx];
        }
    };
    for (int i = 0; i < n; i++) {
        if (a[idx[i]] < p) {
            process(idx[i]);
        } else {
            break;
        }
    }
    cout << cost + (ll) (rem) * p << '\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
/*
Observation 1:
If the edge weight is going to be
greater than p, then the optimal
MST is not going to use that edge.

Reasoning:
If we think about creating a MST with Kruskals,
it's always going to ignore those edges because
the MST can be built with only P weight edges.

Observation 2:
Choosing the shortest edge
that connects two connected components
is always the best. (Duh.)

Observation 3:
If you select the minimum element,
there's never a reason to "bridge" over
that minimum element.

Reasoning:
The only scenario where it's optimal to do that is 
if all the elements to the leftare in one connected 
component, but on the right it's not the same (or vice versa).
But this shouldn't be the case for obvious reasons.

Observation 4:
If you process each index
in ascending order of associated value,
you always want to take as far right and
as far left as possible.

Reasoning:
Because we already established that you'll never need
to "jump" over the minimum value, it's logical that each
time you're just taking a contiguous subarray.
*/