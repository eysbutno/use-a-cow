#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
using ll = long long;
#define pb push_back
#define f first 
#define s second 

int gcd(int a, int b) {
    if (a < b) swap(a, b);
    if (b == 0) return a;
    return gcd(b, a % b);
}
int main() {
    int n; cin >> n;
    vector<int> a(n);   
    for (int& i : a) {
        cin >> i;
    }
    vector<int> pf(n), sf(n);
    sf[n - 1] = a[n - 1];
    pf[0] = a[0];
    for (int i = 1; i < n; i++) {
        pf[i] = gcd(pf[i - 1], a[i]);
    }
    for (int i = n - 2; i >= 0; i--) {
        sf[i] = gcd(sf[i + 1], a[i]);
    }
    int res = max(sf[1], pf[n - 2]);
    for (int i = 1; i < n - 1; i++) {
        res = max(res, gcd(pf[i - 1], sf[i + 1]));
    }
    cout << res << '\n';
}   
/*
Prefix/Suffix array.
Merge results.
*/