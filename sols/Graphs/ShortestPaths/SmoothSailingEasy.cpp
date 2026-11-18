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

template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
const int INF = 1e9;
int dr[]{1, -1, 0, 0, 1, 1, -1, -1},
	dc[]{0, 0, -1, 1, 1, -1, 1, -1};
int main() {
	cin.tie(0) -> sync_with_stdio(0);
	int n, m, q; cin >> n >> m >> q;
	vector<vector<char>> grid(n, 
		vector<char>(m));
	vector<vector<int>> vdist(n, 
		vector<int>(m, INF));
	queue<pii> volc;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> grid[i][j];
			if (grid[i][j] == 'v') {
				volc.push({i, j});
				vdist[i][j] = 0;
			}
		}
	}
	auto valid = [&](int r, int c) {
		return (r >= 0 && r < n &&
				c >= 0 && c < m);
	};
	while (!volc.empty()) {
		auto [r, c] = volc.front(); volc.pop();
		for (int i = 0; i < 4; i++) {
			int r1 = r + dr[i], c1 = c + dc[i];
			if (valid(r1, c1) && smin(vdist[r1][c1], vdist[r][c] + 1)) {
				volc.push({r1, c1});
			}
		}
	}
	auto check = [&](int r, int c, int v) {
		if (vdist[r][c] < v) return false;
		vector<vector<bool>> vis(n,
			vector<bool>(m));
		queue<pii> q; 
		q.push({r, c});
		vis[r][c] = true;
		while (!q.empty()) {
			auto [r1, c1] = q.front(); q.pop();
			for (int i = 0; i < 4; i++) {
				int r2 = r1 + dr[i], c2 = c1 + dc[i];
				if (valid(r2, c2) && !vis[r2][c2] 
					&& grid[r2][c2] != '#' &&
					vdist[r2][c2] >= v) {
					vis[r2][c2] = true;
					q.push({r2, c2});
				}
			}
		}
		vector<vector<bool>> ivis(n,
			vector<bool>(m));
		pii start = {-1, -1};
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (grid[i][j] == '#') {
					ivis[i][j] = true;
					start = {i, j};
					break;
				}
			}
			if (start != make_pair(-1, -1)) {
				break;
			}
		}
		q.push(start);
		while (!q.empty()) {
			auto [r1, c1] = q.front(); q.pop();
			for (int i = 0; i < 8; i++) {
				int r2 = r1 + dr[i], c2 = c1 + dc[i];
				if (valid(r2, c2) && !vis[r2][c2] 
					&& !ivis[r2][c2]) {
					ivis[r2][c2] = true;
					q.push({r2, c2});
				}
			}
		}
		for (int i = 0; i < n; i++) {
			if (ivis[i][0] || ivis[i][m - 1]) {
				return false;
			}
		}
		for (int i = 0; i < m; i++) {
			if (ivis[0][i] || ivis[n - 1][i]) {
				return false;
			}
		}
		return true;
	};
	auto query = [&](int r, int c) {
		int low = 0, high = n + m;
		while (low < high) {
			int mid = (low + high + 1) / 2;
			check(r, c, mid) ? low = mid : high = mid - 1;
		}
		return low;
	};
	while (q--) {
		int x, y; cin >> x >> y;
		cout << query(--x, --y) << '\n';
	}
}
/**
 * TASK: Smooth Sailing.
 * Binary search on the answer. To check,
 * floodfill all the cells that have a distance
 * of >= answer to a volcanoe. If a cell in the island
 * can reach a border, then you cannot make a tour.
*/
/**
  * Make observations.
  * Try out various techniques in your head.
  * See if there are some "restrictions" that you
  * can place, to limit it to a set of states. This
  * often makes life a million times easier!
  * Actually do something and don't just stare at
  * the screen....!
*/
/*
const int MOD = 1e9 + 7;
template<class T> void add(T& a, T b) {
	a += b, a %= MOD;
}
template<class T> void sub(T& a, T b) {
	a > b ? a -= b : a -= b, a += MOD;
}
template<class T> void mul(T& a, T b) {
	a = (a * b) % MOD;
}
*/