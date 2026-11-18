#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, x; cin >> n >> x;
    vector<int> w(n);
    vector<bool> f(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }
    sort(begin(w), end(w));
    int l = 0, r = n - 1, ans = 0;
    while (l < r) {
        if (w[l] + w[r] > x) {
            r--;}
        else {
            f[l] = 1, f[r] = 1;
            l++; r--; ans++;
        }
    }
    for (bool i : f) {
        if (!i) ans++;
    }
    cout << ans << "\n";
}