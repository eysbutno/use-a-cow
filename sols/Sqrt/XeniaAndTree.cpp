#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = array<int, 2>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

template<class T> bool smax(T &a, T b) {
    return a < b ? a = b, 1 : 0;
}
template<class T> bool smin(T &a, T b) {
    return a > b ? a = b, 1 : 0;
}
template<class T> struct RMQ {
    int n, log2dist;
    vector<vector<T>> st;
    void init(vector<T> &v) {
        n = static_cast<int>(v.size());
        log2dist = __lg(n) + 1;
        st.resize(log2dist);
        st[0] = v;
        for (int i = 1; i < log2dist; i++) {
            st[i].resize(n - (1 << i) + 1);
            for (int j = 0; j + (1 << i) <= n; j++) {
                st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
            }
        }
    }
    /** @return minimum on [l, r] */
    T query(int l, int r) {
        int i = __lg(r - l + 1);
        return min(st[i][l], st[i][r - (1 << i) + 1]);
    }
};
struct LCA {
    const int n;
    const vector<vector<int>> &adj;
    RMQ<array<int, 2>> rmq;
    vector<int> tin, et, dep;
    int timer = 0;
    void dfs(int u, int p) {
        tin[u] = timer;
        et[timer++] = u;
        for (int v : adj[u]) {
            if (v == p) continue;
            dep[v] = dep[u] + 1;
            dfs(v, u);
            et[timer++] = u;
        }
    }
    LCA(int _n, vector<vector<int>> &_adj) 
        : n(_n), adj(_adj), tin(n), et(2 * n), dep(n) {
        dfs(0, -1);
        vector<array<int, 2>> arr(2 * n);
        for (int i = 0; i < 2 * n; i++) {
            arr[i] = {dep[et[i]], et[i]};
        }
        rmq.init(arr);
    }
    int query(int a, int b) {
        if (tin[a] > tin[b]) swap(a, b);
        return rmq.query(tin[a], tin[b])[1];
    }
    int dist(int a, int b) {
        return dep[a] + dep[b] - 2 * dep[query(a, b)];
    }
};
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n, q; cin >> n >> q;
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    LCA tree(n, adj);
    vector<bool> on(n);
    on[0] = true;
    vector<int> sp, buf;
    const int b = sqrt(q);
    const auto process = [&]() -> void {
        sp = vector<int>(n, -1);
        queue<pii> q;
        for (int i = 0; i < n; i++) {
            if (on[i]) q.push({i, 0});
        }
        while (!q.empty()) {
            auto [u, t] = q.front(); q.pop();
            if (sp[u] != -1) continue;
            sp[u] = t;
            for (int v : adj[u]) {
                if (sp[v] == -1) q.push({v, t + 1});
            }
        }
        buf.clear();
    };
    const auto upd = [&]() -> void {
        int x; cin >> x;
        on[--x] = true;
        buf.push_back(x);
    };
    const auto qry = [&]() -> void {
        int v; cin >> v;
        int res = sp[--v];
        if (res == -1) res = 1e9;
        for (int i : buf) {
            smin(res, tree.dist(i, v));
        }
        cout << res << "\n";
    };
    for (int i = 0; i < q; i++) {
        if (i % b == 0) process();
        int t; cin >> t;
        t == 1 ? upd() : qry();
    }
}
/**
 * Maintain a sqrt(q) buffer of vertices.
 * Once the buffer is full, recalculate all the
 * distances. Then, for all the queries that haven't
 * been answered inside this buffer, brute force the answer
 * with the distances and the nodes inside the buffer.
*/