#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
using ll = long long;
#define pb push_back
#define f first 
#define s second 

void solve() {
    int n; cin >> n;
    vector<ll> b(n);
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    vector<ll> pf(n), sf(n);
    for (int i = 0; i < n; i++) {
        pf[i] = b[i] + i;
        sf[i] = b[i] - i;
    }
    for (int i = 1; i < n; i++) {
        pf[i] = max(pf[i], pf[i - 1]);
    }
    for (int i = n - 2; i >= 0; i--) {
        sf[i] = max(sf[i], sf[i + 1]);
    }
    ll mx = 0;
    for (int i = 1; i < n - 1; i++) {
        mx = max(mx, pf[i - 1] +
            sf[i + 1] + b[i]);
    }
    cout << mx << '\n';
}
int main() {
    int t; cin >> t;
    while (t--) solve();
}
/*
Tricky prefix sum problem.
(AKA I was too stupid to solve it...)
Basically:
Prefix array: Maintains the best "starting"
location.
Suffix array: Maintains the best "ending" 
location.
To get your answer, just "merge".
*/