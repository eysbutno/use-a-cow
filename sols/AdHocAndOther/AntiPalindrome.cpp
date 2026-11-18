#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define pb push_back
#define ins insert
#define f first 
#define s second 

void solve() {
    int n; cin >> n;
    vector<int> s(n + 1);
    vector<int> freq(26);
    for (int i = 1; i <= n; i++) {
        char c; cin >> c;
        s[i] = c - 'a';
        freq[s[i]]++;
    }
    if (n % 2) {
        cout << -1 << '\n';
        return;
    }
    for (int& i : freq) {
        if (i * 2 > n) {
            cout << -1 << '\n';
            return;
        }
    }
    vector<int> bad(26);
    int pairs = 0;
    for (int i = 1; i <= n / 2; i++) {
        if (s[i] == s[n - i + 1]) {
            bad[s[i]]++;
            ++pairs;
        }
    }
    for (int i = 0; i < 26; i++) {
        if (bad[i] * 2 > pairs) {
            cout << bad[i] << '\n';
            return;
        }
    }
    cout << (pairs + 1) / 2 << '\n';
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t; cin >> t;
    while (t--) solve();
}
/**
 * Count pairs. If one character
 * makes up more than half of the total pairs,
 * you need that many swaps.
 * 
 * Otherwise, print out the # of pairs divided
 * by two, rounding up.
*/