#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    int n; cin >> n;
    vector<ll> pf(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> pf[i]; pf[i] += pf[i - 1];
    }
    ll pfmin = pf[0], pfmax = pf[1];
    for (int i = 1; i <= n; i++) {
        pfmax = max(pfmax, pf[i] - pfmin);
        pfmin = min(pfmin, pf[i]);
    }
    cout << pfmax << "\n";
}
/*
Type: Prefix Sums
Algorithm:
Calculate the prefix sum. For every new prefix,
calculate the maximum possible sum and the starting
prefix with the lowest value. 
NOTE: Compare starting index AFTER calculating the max b/c
the end index obviously can't be the starting index too
*/