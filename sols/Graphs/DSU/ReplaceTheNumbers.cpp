#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define pb push_back
#define ins insert
#define f first 
#define s second 

struct DSU {
    vector<int> e;
    DSU(int n) { 
        e = vector<int>(n); 
        for (int i = 0; i < n; i++) {
            e[i] = i;
        }
    }
    void unite(int x, int y) {
        e[y] = e[x];
    }
} dsu(500'001);
int main() {
    int n; cin >> n;
    vector<int> t(n), x(n), y(n);
    for (int i = 0; i < n; i++) {
        cin >> t[i] >> x[i];
        if (t[i] == 2) {
            cin >> y[i];
        }
    }
    vector<int> res;
    for (int i = n - 1; i >= 0; i--) {
        if (t[i] == 1) {
            res.pb(dsu.e[x[i]]);
        } else {
            dsu.unite(y[i], x[i]);
        }
    }
    reverse(begin(res), end(res));
    for (int i : res) cout << i << ' ';
}
/**
 * Process the queries in reverse.
 * Operation 1:
 * Just push back the current number's
 * representative.
 * 
 * Operation 2:
 * Link y[i]'s representative
 * with x[i]'s representative,
 * so they both point to x[i]'s
 * representative.
*/