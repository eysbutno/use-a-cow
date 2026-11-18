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

const int N = 5001;
const int MOD = 998244353;
ll dp[N][N], pw[N], pf[N];
int main() {
	cin.tie(0) -> sync_with_stdio(0);
    int n; cin >> n;
    vector<int> a(n);
    for (int& i : a) {
        cin >> i, --i;
    }
    pw[0] = 1;
    for (int i = 1; i <= n; i++) {
        pw[i] = (pw[i - 1] * 2) % MOD;
    }
    dp[0][0] = 1, pf[1] = 1;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[i] < a[i - 1]) {
                dp[i][j] = pf[j] * pw[i - j - 1];
            } else {
                dp[i][j] = pf[j + 1] * pw[i - j - 1];
            }
            dp[i][j] %= MOD;
        }
        for (int j = 0; j < n; j++) {
            pf[j + 1] = (dp[i][j] + pf[j]) % MOD;
        }
    }
    cout << pf[n - 1] << '\n';
}
/**
 * TASK: Count BFS Graphs.
 * dp[i][j] = i'th node, connected to j.
 * Case 1: a[i] > a[i - 1].
 * a[i - 1] can be connected to any node
 * <= j. However, it cannot be connected to
 * any nodes between j and a[i - 1], because
 * then a[i - 1] would be after a[i], which is
 * a direct contradition. 
 * 
 * Case 2: a[i] < a[i - 1]. 
 * a[i - 1] cannot be connected to j or anything
 * after j, because then a[i - 1] would be after 
 * a[i], which is a direct contradiction.
*/
/* Stuff to look for:
	* Overflow, OOB.
	* Corner Cases.
	* Do something, stay organized!
	* WRITE STUFF!
	* THINK OF MULTIPLE APPROACHES
*/