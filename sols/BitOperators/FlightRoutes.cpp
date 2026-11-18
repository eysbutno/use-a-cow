#include <bits/stdc++.h>
using namespace std;

int par[751][751];
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n; cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            char c; cin >> c;
            par[i][j] = c - '0';
        }
    }
    int res = 0;
    for (int i = 1; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (par[i][j]) {
                for (int k = j + 1; k <= n; k++) {
                    par[i][k] ^= par[j][k];
                }
                ++res;
            }
        }
    }
    cout << res << '\n';
}
/**
 * TASK: Flight Routes.
 * NOTE: Each flight goes from c_i
 * to c_i+1, where c_i < c_i+1.
 * 
 * If you remove one flight between
 * nodes i and j, then you essentially
 * subtract 1 from all the possible flight
 * routes from all nodes from i to k, where
 * there exists a flight route between j and k.
 * 
 * Idea: Try to keep on removing flight 
 * routes, based on the parity. Every time
 * the parity is 1 for par[i][j], we know
 * there must be a flight. 
 * 
 * Note that you can only know if there's a
 * flight if par[i][j] = 1. The answer is uniquely
 * determined, so we don't need to worry.
*/