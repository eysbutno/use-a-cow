#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define pb push_back
#define ins insert
#define f first 
#define s second 

const int K = 12;
const int N = 500;
const int INF = 1e9;
int dist[K + 1][N][N];
char grid[N][N];
array<int, 3> f[K + 1];
int dp[1 << K][K], opt[1 << K];
template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
void calcDist(int n, int k) {
    int dr[]{1, -1, 0, 0}, dc[]{0, 0, -1, 1};
    auto valid = [&](int r, int c) {
        return (r >= 0 && r < n &&
                c >= 0 && c < n &&
                grid[r][c] != '#');
    };
    for (int it = 0; it <= k; it++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dist[it][i][j] = INF;
            }
        }
        priority_queue<array<int, 3>> pq;
        pq.push({0, f[it][0], f[it][1]});
        dist[it][f[it][0]][f[it][1]] = 0;
        while (!pq.empty()) {
            auto [t, r, c] = pq.top(); pq.pop();
            if (dist[it][r][c] != -t) continue;
            t *= -1, t += (int) (grid[r][c] == '+');
            for (int i = 0; i < 4; i++) {
                int r1 = r + dr[i], c1 = c + dc[i];
                if (valid(r1, c1) && smin(dist[it][r1][c1], t)) {
                    pq.push({-t, r1, c1});
                }
            }
        }
    }
}
int dx(int a, int b) {
    return dist[a][f[b][0]][f[b][1]];
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n, k, m; cin >> n >> k >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }
    for (int i = 0; i < k; i++) {
        int r, c, w; 
        cin >> r >> c >> w;
        f[i] = {--r, --c, w};
    }
    f[k] = {0, 0, 0};
    calcDist(n, k);
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < (1 << k); j++) {
            dp[j][i] = INF;
        }
        dp[1 << i][i] = dx(i, k);
    }
    for (int i = 0; i < (1 << k); i++) {
        for (int e1 = 0; e1 < k; e1++) {
            if (!(i >> e1 & 1)) continue;
            for (int e2 = 0; e2 < k; e2++) {
                if (!(i >> e2 & 1)) continue;
                smin(dp[i][e1], dp[i ^ (1 << e1)][e2] + dx(e1, e2));
            }
        }
    }
    fill(opt, opt + (1 << k), INF);
    for (int i = 0; i < (1 << k); i++) {
        ll sum = 0;
        for (int j = 0; j < k; j++) {
            if (i >> j & 1) sum += f[j][2];
        }
        if (sum > m) continue;
        for (int j = 0; j < k; j++) {
            smin(opt[i], dp[i][j] + dx(j, k));
        }
    }
    for (int i = 0; i < (1 << k); i++) {
        for (int j = 0; j <= i; j++) {
            if ((i & j) == j) {
                smin(opt[i], opt[j] + opt[i ^ j]);
            }
        }
    }
    cout << opt[(1 << k) - 1] << '\n';
}
/**
 * TASK: Fossil Excavation.
 * First, use 01 BFS / Dijkstra to calculate SP
 * from every fossil to every other fossil/the base.
 * Then, use bitmask DP to find the optimal "tour" that
 * gets a subset of fossils. To combine said tours, you 
 * use bitmask DP again.
*/