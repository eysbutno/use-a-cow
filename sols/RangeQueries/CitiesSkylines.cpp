#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define pb push_back
#define f first 
#define s second 

template<class T> class FT2D {
    private:
        int n, m;
        vector<vector<T>> arr;
    public:
        FT2D(int N, int M) {
            n = N + 1;
            m = M + 1;
            arr = vector<vector<T>>(N + 1, 
                vector<T>(M + 1));
        }
        void update(int r, int c, T dx) {
            for (int i = r; i < n; i += i & -i) {
                for (int j = c; j < m; j += j & -j) {
                    arr[i][j] += dx;
                }
            }
        }
        T get(int r, int c) {
            T tot = 0;
            for (int i = r; i > 0; i -= i & -i) {
                for (int j = c; j > 0; j -= j & -j) {
                    tot += arr[i][j];
                }
            }
            return tot;
        }
        T query(int r1, int c1, int r2, int c2) {
            --r1, --c1; // already one indexed
            return get(r2, c2) - get(r2, c1) - 
                get(r1, c2) + get(r1, c1);
        }
};
const int MAX = 1e3 + 1;
bool grid[MAX][MAX];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int n, q; cin >> n >> q;
    FT2D<int> ft(n, n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            char c; cin >> c;
            if (c == '*') {
                grid[i][j] = 1;
                ft.update(i, j, 1);
            }
        }
    }
    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int x, y; cin >> x >> y;
            if (grid[x][y]) {
                ft.update(x, y, -1);
            } else {
                ft.update(x, y, 1);
            }
            grid[x][y] = !grid[x][y];
        } else {
            int r1, c1, r2, c2;
            cin >> r1 >> c1 >> r2 >> c2;
            cout << ft.query(r1, c1, r2, c2) << '\n';
        }
    }
}
/*
Pretty standard BIT problem.
*/