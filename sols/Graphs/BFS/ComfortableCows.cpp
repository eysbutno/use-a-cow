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

const int MAX = 3e3;
bool placed[MAX][MAX];
int dr[]{0, 0, 1, -1},
    dc[]{1, -1, 0, 0};
int n = 0, res = 0;
bool comfy(int a, int b) {
    int cnt = 0;
    for (int i = 0; i < 4; i++) {
        if (placed[a + dr[i]][b + dc[i]]) ++cnt;
    }
    return (cnt == 3);
}
void adjust(int r, int c) {
    queue<pii> q;
    q.push({r, c});
    auto process = [&](int a, int b) {
        if (!placed[a][b] ||
            !comfy(a, b)) {
            return;
        }
        ++res;
        for (int i = 0; i < 4; i++) {
            int r = a + dr[i],
                c = b + dc[i];
            if (!placed[r][c]) {
                placed[r][c] = 1;
            }
            q.push({r, c});
        }
    };
    while (!q.empty()) {
        auto p = q.front(); q.pop();
        process(p.f, p.s);
        for (int i = 0; i < 4; i++) {
            process(p.f + dr[i], p.s + dc[i]);
        }
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin >> n;
    for (int i = 0; i < n; i++) {
        int r, c; cin >> r >> c;
        r += 1500, c += 1500;
        if (placed[r][c]) {
            placed[r][c] = 1;
            --res;
        } else {
            placed[r][c] = 1;
            adjust(r, c);
        }
        cout << res << '\n';
    }
}
/**
 * When adding each cow, if
 * the addition of the cow will make
 * any adjacent cow comfortable, you need
 * to run on that cow. So, just BFS.
 * 
 * When processing a cow, first check if 
 * the newly placed cow is comfortable. If so,
 * place a cow there and check every adjacent
 * location to see if it's comfy.
 * 
 * BFS works because it go outwards and also
 * go back to double check if a cell is ok.
*/