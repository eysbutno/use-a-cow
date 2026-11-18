#include <bits/stdc++.h>
using namespace std;

int main() {
    multiset<int> towers;
    int n, ans = 0; cin >> n;
    while (n--) {
        int a; cin >> a;
        auto t = towers.upper_bound(a);
        if (t == end(towers)) {
            ans++; towers.insert(a);
        } else {
            towers.erase(t);
            towers.insert(a);
        }
    }
    cout << ans << "\n";
}