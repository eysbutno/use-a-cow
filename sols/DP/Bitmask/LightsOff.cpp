#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define mp(x, y) make_pair(x, y)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define pb push_back
#define ins insert
#define f first 
#define s second 

bool dp[61][1 << 20];
int pads[61][20];
int toInt(string s) {
    int n = s.length(), res = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            res |= 1 << (n - i - 1);
        }
    }
    return res;
}
int rotate(int bit, int n) {
    return ((bit & 1) << (n - 1)) | (bit >> 1);
}
void solve(int n) {
    string a, b; cin >> a >> b;
    int s = toInt(a), l = toInt(b), cur = 0;
    for (int i = 0; i <= n * 3; i++) {
        if (dp[i][cur ^ s]) {
            cout << i << '\n';
            return;
        }
        cur ^= l, l = rotate(l, n);
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t, n; cin >> t >> n;
    for (int l = 1; l <= n * 3; l++) {
        for (int d = 0; d < n; d++) {
            pads[l][d] = (1 << d) ^ pads[l - 1][(d + 1) % n];
        }
    }
    dp[0][0] = true;
    for (int i = 1; i <= n * 3; i++) {
        for (int j = 0; j < (1 << n); j++) {
            for (int k = 0; k < n; k++) {
                if (dp[i - 1][j ^ pads[i][k]]) {
                    dp[i][j] = true;
                    break;
                }
            }
        }
    }
    while (t--) solve(n);
}
/**
 * TASK: Lights Off.
 * Observation 1:
 * If all the switches are off right now,
 * we can flip each bit in two moves. So,
 * in total, you can always get the answer in
 * N * 3 moves.
 * 
 * Observation 2:
 * If we assume that you can do everything
 * in k moves, then the answer is just if you
 * can reach a string that's just the current
 * switches, XORed by the current state,
 * performed k times, in k moves total.
 * 
 * Reasoning:
 * If the switches get activated k times, then
 * the string "moving" also gets processed. By
 * XORing the stuff, we get the final "changes"
 * that need to happen.
 * 
 * Algorithm:
 * Precalculate dp[i][j], which stores if you can
 * reach subset j with i moves. Then, use observation
 * 2 to calculate your answer.
*/