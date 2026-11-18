#include <bits/stdc++.h>
using namespace std;

const int MAX = 210;
bool vis[MAX][MAX], cow[MAX][MAX], fence[MAX][MAX];
vector<int> num; int n, k, r, id = -1;
void ff(int r, int c) {
    if (r < 2 || r > 2 * n || c < 2 || c > 2 * n
        || vis[r][c] || fence[r][c]) {
        return;
    }
    vis[r][c] = 1; num[id] += cow[r][c];
    ff(r + 1, c), ff(r, c + 1);
    ff(r - 1, c), ff(r, c - 1);
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    freopen("countcross.in", "r", stdin);
    freopen("countcross.out", "w", stdout);
    cin >> n >> k >> r;
    for (int i = 0; i < r; i++) {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        fence[r1 + r2][c1 + c2] = 1;
        if (r1 == r2) {
            fence[r1 + r2 + 1][c1 + c2] = 1;
            fence[r1 + r2 - 1][c1 + c2] = 1;
        } else {
            fence[r1 + r2][c1 + c2 + 1] = 1;
            fence[r1 + r2][c1 + c2 - 1] = 1;
        }
    }
    for (int i = 0; i < k; i++) {
        int r, c; cin >> r >> c;
        cow[r * 2][c * 2] = 1;
    }
    for (int i = 2; i <= n * 2; i += 2) {
        for (int j = 2; j <= n * 2; j += 2) {
            if (!vis[i][j]) {
                num.push_back(0);
                ++id, ff(i, j);
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < num.size() - 1; i++) {
        for (int j = i + 1; j < num.size(); j++) {
            ans += num[i] * num[j];
        }
    }
    cout << ans << "\n";
}
/*
Type: Floodfill
Time Complexity: O(N^2)
Algorithm:
Mark the cows and fences on a graph scaled up by a factor of 2.
Run floodfill to calculate the # of cows in each component. 
Get your answer with the method shown above.
NOTE: YOU MUST ADD TWO SQUARES ON EACH SIDE WHEN MARKING THE FENCE!
If you don't, then the floodfill algorithm will go into parts that it's not supposed to go into.
*/