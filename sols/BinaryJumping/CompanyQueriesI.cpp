#include<bits/stdc++.h>
using namespace std;

const int MX = 2e5 + 1;
const int LOG = 18;
int up[LOG][MX];
int kth(int x, int d) {
    for (int i = LOG; i >= 0; i--) {
        int num = pow(2, i);
        if (d >= num) {
            x = up[i][x];
            d -= num;
        }
    }
    return x ?: -1;
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n, q; cin >> n >> q;
    for (int i = 2; i <= n; i++) {
        int b; cin >> b;
        up[0][i] = b;
    }
    for (int i = 1; i < LOG; i++) {
        for (int j = 1; j <= n; j++) {
            up[i][j] = up[i - 1][up[i - 1][j]];
        }
    }
    while (q--) {
        int x, k; cin >> x >> k;
        cout << kth(x, k) << "\n";
    }
}