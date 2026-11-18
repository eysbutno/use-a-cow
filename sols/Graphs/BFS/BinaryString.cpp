#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define pb push_back
#define ins insert
#define f first 
#define s second 

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n, k; cin >> n >> k;
    const int TARG = (1 << k) - 1;
    auto inv = [&](int x, int y) {
        return ((x | y) == TARG) && 
                ((x & y) == 0);
    };
    vector<int> x(n), y(n);
    queue<pair<int, vector<int>>> st;
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
        if (x[i] == TARG) {
            st.push({i, {i}});
        }
    }
    vector<vector<int>> adj(n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (inv(y[i], x[j])) {
                adj[i].pb(j);
            }
            if (inv(x[i], y[j])) {
                adj[j].pb(i);
            }
        }
    }
    vector<int> ans;
    while (!st.empty()) {
        auto N = st.front(); st.pop();
        if (size(N.s) == n) {
            ans = N.s;
            break;
        }
        for (int i : adj[N.f]) {
            bool found = false;
            for (int j : N.s) {
                if (i == j) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                vector<int> temp = N.s;
                temp.pb(i);
                st.push({i, temp});
            }
        }
    }
    for (int i : ans) {
        cout << i + 1 << ' ';
    }
}
/**
 * Just a Proco problem I found interesting.
*/