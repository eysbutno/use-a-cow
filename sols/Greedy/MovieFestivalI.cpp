#include <bits/stdc++.h>
using namespace std;
#define f first 
#define s second
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k; cin >> n >> k;
    vector<pair<int, int>> mov(n);
    for (int i = 0; i < n; i++) {
        cin >> mov[i].s >> mov[i].f;
    }
    sort(begin(mov), end(mov));
    multiset<int> memb;
    for (int i = 0; i < k; i++) {
        memb.insert(0);
    }
    int ans = 0;
    for (auto i : mov) {
        auto ptr = memb.upper_bound(i.s);
        if (ptr != begin(memb)) {
            memb.erase(--ptr), memb.insert(i.f);
            ans++;
        }
    }
    cout << ans << "\n";
}