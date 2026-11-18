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
void solve() {
    int n, m; 
    cin >> n >> m;
    vector a(n, vector(m, '?'));
    vector vis(n, vector(m, false));
    queue<pii> cur;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
            if (a[i][j] == 'L') {
                cur.push({i, j});
                vis[i][j] = true;
            }
        }
    }
    int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, -1, 1};
    auto onGrid = [&](int r, int c) -> bool {
        return (r >= 0 && r < n && c >= 0 && c < m);
    };
    auto valid = [&](int r, int c) -> bool {
        // returns: if {r, c} is a valid cell.
        if (!onGrid(r, c)) return false;
        if (a[r][c] == '#') return false;
        vector<int> cnts = {0, 0};
        for (int i = 0; i < 4; i++) {
            int r1 = r + dr[i], c1 = c + dc[i];
            if (onGrid(r1, c1) && a[r1][c1] != '#') {
                cnts[vis[r1][c1]]++;
            }
        }
        return cnts[0] <= 1 && cnts[1] >= 1;
    };
    while (!cur.empty()) {
        auto [r, c] = cur.front(); cur.pop();
        for (int i = 0; i < 4; i++) {
            int r1 = r + dr[i], c1 = c + dc[i];
            if (valid(r1, c1) && !vis[r1][c1]) {
                vis[r1][c1] = true, cur.push({r1, c1});
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] == '.' && vis[i][j]) {
                cout << '+';
            } else {
                cout << a[i][j];
            }
        }
        cout << "\n";
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; cin >> t;
    while (t--) solve();
}
/**
 * TASK: E. Crazy Robot (CF)
 * BFS from the lab. Every time you propogate,
 * check if you can "force" the robot into a previously
 * traversed cell. The idea is that if a cell can be forced
 * into another cell that is able to force to the lab, then
 * this cell can also be included.
*/