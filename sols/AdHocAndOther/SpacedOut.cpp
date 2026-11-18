#include <bits/stdc++.h>
using namespace std;

const int MAX = 1001;
int grid[2][MAX][MAX];
int res(int n, int id) {
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int even = 0, odd = 0;
        for (int j = 0; j < n; j++) {
            if (j % 2) odd += grid[id][i][j];
            else even += grid[id][i][j];
        }
        ans += max(even, odd);
    }
    return ans;
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[0][i][j];
            grid[1][j][i] = grid[0][i][j];
        }
    }
    cout << max(res(n, 0), res(n, 1));
}
/*
I SUCK AT MAKING OBSERVATIONS!
The biggest observation is that 
if your rows are alternating,
then your chosen locations just
need to be all odd / even,
and if your columns are alternating,
then your chosen locations need to be
odd / even. After that, implementation
is TRIVIAL.
*/