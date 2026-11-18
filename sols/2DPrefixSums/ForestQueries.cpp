#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q; cin >> n >> q;
    int prefix[n + 1][n + 1];
    for (int i = 0; i <= n; i++) {
        prefix[i][0] = 0; prefix[0][i] = 0;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            char a; cin >> a;
            prefix[i][j] = (int) a == '*';
            prefix[i][j] += prefix[i - 1][j] + 
            prefix[i][j - 1] - prefix[i - 1][j - 1];
        }
    }
    for (int i = 0; i < q; i++) {
        int y1, x1, y2, x2; cin >> y1 >> x1 >> y2 >> x2;
        cout << prefix[y2][x2] - prefix[y1 - 1][x2]
        - prefix[y2][x1 - 1] + prefix[y1 - 1][x1 - 1] << endl;
    }
    return 0;
}
/*
Type: 2D Prefix
Algorithm:
Read data, then calculate prefix sums. Print out the queries.
*/