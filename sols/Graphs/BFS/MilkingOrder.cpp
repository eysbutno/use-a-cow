#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define sz(x) (int) (x).size()
#define pb push_back 
#define ins insert
#define f first 
#define s second

const int M = 5e4;
vector<int> obs[M];
vector<int> res;
bool check(int n, int m, int mid) {
    res.clear();
    vector<set<int>> adj(n);
    vector<int> inDeg(n);
    for (int i = 0; i < mid; i++) {
        if (sz(obs[i]) <= 1) continue;
        for (int j = 1; j < sz(obs[i]); j++) {
            adj[obs[i][j - 1]].ins(obs[i][j]);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j : adj[i]) {
            ++inDeg[j];
        }
    }
    priority_queue<int> pq;
    for (int i = 0; i < n; i++) {
        if (!inDeg[i]) pq.push(-i);
    }
    while (!pq.empty()) {
        int u = -pq.top(); 
        pq.pop(), res.pb(u);
        for (int i : adj[u]) {
            --inDeg[i];
            if (!inDeg[i]) {
                pq.push(-i);
            }
        }
    }
    return (sz(res) == n);
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    freopen("milkorder.in", "r", stdin);
    freopen("milkorder.out", "w", stdout);
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int m; cin >> m;
        obs[i].resize(m);
        for (int j = 0; j < m; j++) {
            int x; cin >> x;
            obs[i][j] = --x;
        }
    }
    int low = 0, high = n;
    while (low < high) {
        int mid = (low + high + 1) / 2;
        if (check(n, m, mid)) {
            low = mid;
        } else {
            high = mid - 1;
        }
    }
    check(n, m, low);
    for (int i = 0; i < n; i++) {
        cout << res[i] + 1 << 
            (i != n - 1 ? ' ' : '\n');
    }
}
/**
 * Binary search the prefix.
 * 
 * Construct a graph between 
 * each adjacent cow, where
 * there's an edge between
 * cow p_i-1 and p_i. If you
 * can make a toposort, then
 * there's a valid ordering.
*/