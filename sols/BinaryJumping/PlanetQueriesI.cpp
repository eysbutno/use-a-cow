#include <bits/stdc++.h>
using namespace std;

const int LOG = 30;
int jump(int n, int k, vector<vector<int>>& des) {
    for (int i = LOG; i >= 0; i--) {
        int num = pow(2, i);
        if (k >= num) {
            n = des[i][n];
            k -= num;
        }
    }
    return n;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q; cin >> n >> q;
    vector<vector<int>> des(LOG, vector<int>(n + 1));
    for (int i = 1; i <= n; i++) {
        cin >> des[0][i];
    }
    for (int i = 1; i < LOG; i++) {
        for (int j = 1; j <= n; j++) {
            des[i][j] = des[i - 1][des[i - 1][j]];
        }
    }
    while (q--) {
        int a, b; cin >> a >> b;
        cout << jump(a, b, des) << "\n";
    }
}