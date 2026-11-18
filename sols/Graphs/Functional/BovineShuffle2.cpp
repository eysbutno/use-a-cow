#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define all(x) begin(x), end(x)
#define ckmin(a, b) a = min(a, b)
#define ckmax(a, b) a = max(a, b)
#define pb push_back 
#define ins insert
#define f first 
#define s second

const int MAX = 1e5 + 1;
int nxt[MAX], vis[MAX];
vector<int> rev[MAX];
void dfs(int node) {
    vis[node] = true;
    for (int i : rev[node]) {
        if (!vis[i]) dfs(i);
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    freopen("shuffle.in", "r", stdin);
    freopen("shuffle.out", "w", stdout);
    int n; cin >> n;
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        nxt[i] = x;
        rev[x].pb(i);
    }
    int res = 0;
    auto process = [&](int node) {
        // find a node in the cycle.
        int a = nxt[node], 
            b = nxt[nxt[node]];
        while (a != b) {
            a = nxt[a];
            b = nxt[nxt[b]];
        }
        vector<int> proc;
        do {
            if (size(rev[b]) > 1) {
                proc.pb(b);
            }
            vis[b] = true;
            b = nxt[b];
            ++res;
        } while (a != b);
        for (int i : proc) {
            dfs(i);
        }
    };
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) process(i);
    }
    cout << res << '\n';
}
/**
 * Functional graph. If it's in
 * a cycle, it will always have 
 * a cow in it.
 * 
 * Each functional graph is a cycle
 * and some nodes attached to the end.
 * Do the stuff for each node in the cycle,
 * and mark all the tails as visited.
*/