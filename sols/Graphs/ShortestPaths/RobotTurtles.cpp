#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define smax(a, b) a = max(a, b)
#define smin(a, b) a = min(a, b)
#define pb push_back
#define ins insert
#define f first 
#define s second 

const int N = 8;
const int INF = 1e9;
int dist[4][N][N], 
    dr[]{0, -1, 0, 1},
    dc[]{1, 0, -1, 0};
string res[4][N][N];
char grid[N][N];
struct State {
    int f, s, dist, dir;
    string seq;
    bool operator<(const State& y) const {
        return dist > y.dist;
    }
};
int main() {
    int sr = -1, sc = -1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 'D') {
                sr = i, sc = j;
            }
            for (int k = 0; k < 4; k++) {
                dist[k][i][j] = INF;
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        res[i][sr][sc] = "no solution";
    }
    dist[0][7][0] = 0;
    priority_queue<State> pq;
    pq.push({7, 0, 0, 0, ""});
    auto ok = [&](int r, int c) {
        return (r >= 0 && r < 8 && 
            c >= 0 && c < 8 && 
            grid[r][c] != 'C');
    };
    while (!pq.empty()) {
        State s = pq.top(); pq.pop();
        int dx = s.dist, dir = s.dir,
            r = s.f, c = s.s;
        string moves = s.seq;
        if (dist[dir][r][c] != dx) {
            continue;
        }
        res[dir][r][c] = moves;
        int r1 = r + dr[dir], c1 = c + dc[dir];
        if (ok(r1, c1) && (grid[r1][c1] == '.'
            || grid[r1][c1] == 'D')) {
            int ndx = dist[dir][r][c] + 1;
            if (ndx < dist[dir][r1][c1]) {
                dist[dir][r1][c1] = ndx;
                pq.push({r1, c1, ndx, dir, moves + 'F'});
            }
        }
        if (ok(r1, c1) && grid[r1][c1] == 'I') {
            int ndx = dist[dir][r][c] + 2;
            if (ndx < dist[dir][r1][c1]) {
                dist[dir][r1][c1] = ndx;
                pq.push({r1, c1, ndx, dir, moves + "XF"});
            }
        }
        string ch[]{"R", "L"};
        int chx[]{-1, 1};
        for (int i = 0; i < 2; i++) {
            int nDir = (dir + chx[i] + 4) % 4;
            if (dist[dir][r][c] + 1
                < dist[nDir][r][c]) {
                dist[nDir][r][c] = dist[dir][r][c] + 1;
                pq.push({r, c, dist[nDir][r][c], 
                    nDir, moves + ch[i]});
            }
        }
    }
    string best = res[0][sr][sc];
    for (int i = 1; i < 4; i++) {
        if (res[i][sr][sc].length() < best.length()
            && res[i][sr][sc] != "no solution") {
            best = res[i][sr][sc];
        }
    }
    cout << best << '\n';
}
/**
 * Use BFS. (Why is the impl so
 * annoying?????)
*/