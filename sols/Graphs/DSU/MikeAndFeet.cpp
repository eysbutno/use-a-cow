#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define smin(a, b) a = min(a, b)
#define smax(a, b) a = max(a, b)
#define pb push_back
#define ins insert
#define f first 
#define s second 

struct DSU {
    vector<int> e;
    DSU(int n) { 
        e = vector<int>(n, -1); 
    }
    int get(int x) { 
        return e[x] < 0 ? x : e[x] = get(e[x]); 
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
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n; cin >> n;
    vector<bool> placed(n);
    priority_queue<pii> todo;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        todo.push({x, i});
    }
    vector<int> res(n + 1);
    int mx = 0;
    DSU dsu(n);
    while (!todo.empty()) {
        auto [h, v] = todo.top(); todo.pop();
        if (v > 0 && placed[v - 1]) {
            dsu.unite(v, v - 1);
        }
        if (v < n - 1 && placed[v + 1]) {
            dsu.unite(v, v + 1);
        }
        smax(mx, dsu.size(v));
        smax(res[mx], h);
        placed[v] = true;
    }
    for (int i = n - 1; i > 0; i--) {
        if (!res[i]) res[i] = res[i + 1];
    }
    for (int i = 1; i <= n; i++) {
        cout << res[i] << ' ';
    }
}
/**
 * Idea: Use DSU. Add elements
 * one by one.
 * 
 * (IK this doesn't use a stack,
 * but this is probably easier.)
*/