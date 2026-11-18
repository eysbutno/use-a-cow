    #include <bits/stdc++.h>
    using namespace std;
    using ll = long long;
    using pii = pair<int, int>;
    #define all(x) begin(x), end(x)
    #define sz(x) (int) (x).size()
    #define f first 
    #define s second 
     
    template<class T> bool smin(T& a, T b) {
        return b < a ? a = b, 1 : 0;
    }
    template<class T> bool smax(T& a, T b) {
        return b > a ? a = b, 1 : 0;
    }
    int main() {
        cin.tie(0) -> sync_with_stdio(0);
        int m, n; cin >> m >> n;
        vector<int> ord(n), p(n);
        for (int &i : p) {
            cin >> i;
        }
        bitset<5000> def;
        for (int i = 0; i < 5000; i++) {
            def[i] = true;
        }
        vector adj(n, def);
        iota(all(ord), 0);
        for (int i = 0; i < m; i++) {
            vector<int> r(n);
            for (int &j : r) {
                cin >> j;
            }
            sort(all(ord), [&](int x, int y) {
                return r[x] < r[y];
            });
            bitset<5000> cur;
            int lf = 0;
            while (lf < n) {
                int rt = lf;
                while (rt < n && r[ord[lf]] == r[ord[rt]]) {
                    adj[ord[rt]] &= cur;
                    ++rt;
                }
                while (lf < rt) {
                    cur[ord[lf]] = true;
                    ++lf;
                }
            }
        }
        /**
         * Graph will be acyclic, b/c ratings
         * must be strictly increasing.
        */
        vector<int> deg(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (adj[i][j]) ++deg[j];
            }
        }
        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (!deg[i]) q.push(i);
        }
        vector<ll> dp(n);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            dp[u] += p[u]; // best right now
            for (int v = 0; v < n; v++) {
                if (adj[u][v]) smax(dp[v], dp[u]);
                if (!(--deg[v])) q.push(v);
            }
        }
        cout << *max_element(all(dp)) << "\n";
    }
    /**
     * TASK: Walk the Runway (CF).
     * Construct a graph, where there's an
     * edge between models i -> j, if i can
     * come after. Then, DP.
     * (Bitset shenanigans are required for a 
     * not "insane" solution)
    */