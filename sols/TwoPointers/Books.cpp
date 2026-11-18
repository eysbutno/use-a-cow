#include <bits/stdc++.h>
using namespace std;
// basic two pointers implementation
int main() {
    int n, t; cin >> n >> t;
    vector<int> books(n);
    for (int i = 0; i < n; i++) cin >> books[i];
    int l = 0, r = 0, c = 0, ans = 0;
    while (l < n && r < n) {
        while (r < n) {
            c += books[r++];
            if (c > t) {
                c -= books[--r];
                break;
            }
        }
        ans = max(ans, r - l);
        c -= books[l++];
    }
    cout << ans << endl;
}