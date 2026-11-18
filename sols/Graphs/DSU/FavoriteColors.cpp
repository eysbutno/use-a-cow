#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define sz(x) (int) (x).size()
#define pb push_back
#define ins insert
#define f first 
#define s second 

const int N = 2e5 + 1;
set<int> adj[N], rev[N];
int par[N], res[N];
int get(int x) {
    return par[x] < 0 ? x : par[x] = get(par[x]);
}
void merge(int a, int b) {
    if (sz(adj[a]) < sz(adj[b])) {
        swap(a, b);
    }
    par[b] = a;
    for (int i : adj[b]) {
        rev[i].erase(b);
        rev[i].ins(a);
        adj[a].ins(i);
    }
    for (int i : rev[b]) {
        rev[a].ins(i);
        adj[i].ins(a);
        adj[i].erase(b);
    }
    adj[b].clear(), rev[b].clear();
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    freopen("fcolor.in", "r", stdin);
    freopen("fcolor.out", "w", stdout);
    int n, m; cin >> n >> m;
    fill(par, par + n + 1, -1);
    for (int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        adj[x].ins(y), rev[y].ins(x);
    }
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (sz(adj[i]) > 1) q.push(i);
    }
    while (!q.empty()) {
        int u = q.front(); 
        q.pop(), u = get(u);
        while (sz(adj[u]) > 1) {
            int a = *begin(adj[u]),
                b = *rbegin(adj[u]);
            merge(a, b);
        }
        if (sz(adj[*begin(adj[u])]) > 1) {
            q.push(*begin(adj[u]));
        }
    }
    int color = 0;
    for (int i = 1; i <= n; i++) {
        if (!res[get(i)]) res[get(i)] = ++color;
        cout << res[get(i)] << '\n';
    }
}
/**
 * TASK: Favorite Colors.
 * Merge each cow that must have the
 * same favorite color into a component,
 * and keep on merging until each cow
 * only has one other group of cows who
 * admires them. Once that's done, you
 * can freely assign colors.
 * 
 * IMPLEMENTATION: Use BFS. Basically,
 * start from each cow that has >= 2 
 * admirers, and BFS to each other cow 
 * group and merge those components.
 * 
 * Note that when merging, we can freely 
 * delete the edges that are to cows that
 * no longer exist.
*/