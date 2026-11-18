#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define f first 
#define s second 
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int x, n; cin >> x >> n;
    multiset<int> sticks;
    for (int i = 0; i < n; i++) {
        int num; cin >> num; 
        sticks.insert(num);
    }
    ll ans = 0;
    while (sticks.size() > 1) {
        auto it = begin(sticks);
        int big = 0;
        for (int i = 0; i < 2; i++) {
            big += *it;
            it = sticks.erase(it);
        }
        sticks.insert(big), ans += big;
    }
    cout << ans << '\n';
}