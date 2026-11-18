#include <bits/stdc++.h>
using namespace std;
#define f first 
#define s second
// code could definitely be more efficient, but hey, it AC'ed
const int MAX = 250;
bool vis[MAX][MAX];
int grid[MAX][MAX], comp[MAX][MAX], n;
int dr[] = {0, 0, 1, -1}, dc[] = {1, -1, 0, 0};
map<int, set<int>> con;
struct hsh {
	size_t operator()(const pair<int, int> &p) const {
		return p.f * 239 + p.s;
	}
};
void ff(int r, int c, int color, int id) {
    if (r < 0 || r >= n || c < 0 || c >= n
        || grid[r][c] != color || comp[r][c]) {
        return;
    }
    comp[r][c] = id;
    for (int i = 0; i < 4; i++) {
        ff(r + dr[i], c + dc[i], color, id);
    }
}
void build(int r, int c, int id, vector<int>& cnt,
    unordered_map<pair<int, int>, unordered_set<int>, hsh>& adj) {
    if (r < 0 || r >= n || c < 0 || c >= n
        || vis[r][c] || comp[r][c] != id) {
        return;
    }
    cnt[id]++; vis[r][c] = 1;
    for (int i = 0; i < 4; i++) {
        int r1 = r + dr[i], c1 = c + dc[i];
        if (r1 >= 0 && r1 < n && c1 >= 0 &&
            c1 < n && comp[r1][c1] != id) {
            adj[{id, grid[r1][c1]}].insert(comp[r1][c1]);
            con[id].insert(grid[r1][c1]);
        }
    }
    for (int i = 0; i < 4; i++) {
        build(r + dr[i], c + dc[i], id, cnt, adj);
    }
}
int dfs(int node, int g1, int g2, vector<int>& cnt, 
    unordered_map<pair<int, int>, set<int>, hsh>& seen, unordered_map<
    pair<int, int>, unordered_set<int>, hsh>& adj) {
    if (seen[{g1, g2}].count(node)) return 0;
    seen[{g1, g2}].insert(node);
    int res = cnt[node];
    if (adj.count({node, g1})) {
        for (int i : adj[{node, g1}]) {
            if (!seen[{g1, g2}].count(i)) {
                res += dfs(i, g1, g2, cnt, seen, adj);
            }
        }
    }
    if (adj.count({node, g2})) {
        for (int i : adj[{node, g2}]) {
            if (!seen[{g1, g2}].count(i)) {
                res += dfs(i, g1, g2, cnt, seen, adj);
            }
        }
    }
    return res;
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    freopen("multimoo.in", "r", stdin);
    freopen("multimoo.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }
    int num = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!comp[i][j]) ff(i, j, 
                grid[i][j], ++num);
        }
    }
    unordered_map<int, unordered_set<int>> groups;
    unordered_map<pair<int, int>, unordered_set<int>, hsh> adj;
    vector<int> cnt(num + 1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!vis[i][j]) {
                build(i, j, comp[i][j], 
                    cnt, adj);
                groups[grid[i][j]].insert(comp[i][j]);
            }
        }
    }
    vector<int> nums;
    for (auto i : groups) nums.push_back(i.f);
    int best = 0;
    unordered_map<pair<int, int>, set<int>, hsh> seen;
    for (auto i : groups) {
        for (int j : i.s) {
            for (int k : con[j]) {
                best = max(best, dfs(j, max(i.f, k), 
                    min(i.f, k), cnt, seen, adj));
            }
        }
    }
    int alone = 0;
    for (int i : cnt) alone = max(alone, i);
    cout << alone << '\n' << best << '\n';
}
/*
Run floodfill to create all the connected components
and to calculate the best one cow can do.

To calculate how many squares a pair can do, you can
compress each region into a node, and append all the 
adjacent connected components to an adjacency list.
After that, run DFS to calculate it.

NOTE: DO NOT BRUTE FORCE EACH PAIR. THAT'S WAY TOO SLOW.
*/