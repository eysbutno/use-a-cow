#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
using ll = long long;
#define pb push_back
#define f first 
#define s second 

int main() {
    ll n, m; cin >> n >> m;
    vector<ll> s(n);
    for (ll& i : s) {
        cin >> i;
    }
    for (int i = 1; i < n; i++) {
        if (s[i - 1] + m < s[i]) {
            s[i - 1] = s[i] - m;
        } 
        if (s[i] + m < s[i - 1]) {
            s[i] = s[i - 1] - m;
        }
    }
    reverse(begin(s), end(s));
    for (int i = 1; i < n; i++) {
        if (s[i - 1] + m < s[i]) {
            s[i - 1] = s[i] - m;
        } 
        if (s[i] + m < s[i - 1]) {
            s[i] = s[i - 1] - m;
        }
    }
    reverse(begin(s), end(s));
    for (ll& i : s) {
        cout << i << ' ';
    }
}
/*
Do the constraint stuff one time.
Then reverse the array, and do it again.
Note: Could have done a BFS-like strategy,
but that's slower and more complicated.
*/