#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define pb push_back
#define ins insert
#define f first 
#define s second 

const int MAX = 2e5 + 1;
int dp[MAX][26];
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    string s; cin >> s;
    int n = s.length();
    for (int i = 1; i <= n; i++) {
        int idx = s[i - 1] - 'a';
        dp[i][idx]++;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 26; j++) {
            dp[i][j] += dp[i - 1][j];
        }
    }
    auto check = [&](int l, int r) {
        int cnt = 0;
        for (int i = 0; i < 26; i++){
            int sum = dp[r][i] - dp[l - 1][i];
            if (sum > 0) ++cnt;
        }
        return cnt < 3 || s[l - 1] == s[r - 1]
            || l != r;
    };
    int q; cin >> q;
    while (q--) {
        int a, b; cin >> a >> b;
        if (check(a, b)) cout << "Yes";
        else cout << "No";
        cout << '\n';
    }
}
/**
 * Observation 1:
 * Assuming the size isn't one, a
 * substring that's all the same character
 * can always form an anagram.
 * 
 * Observation 2:
 * If the first and last character
 * are different, you can form an
 * anagram.
 * Reasoning:
 * If you simply swap the first and
 * last characters, it'll be an
 * irreducible anagram.
 * 
 * The reason it's an irreducible anagram
 * in this scenario is because if we order
 * the internal elements correctly, there'll
 * be no way to make it reducible.
 * 
 * Observation 3:
 * If there are more than 2 unique characters, you can
 * form an irreducible anagram.
 * 
 * Reasoning:
 * A...BD...A
 * B...A...A...D
 * Irreducible.
*/