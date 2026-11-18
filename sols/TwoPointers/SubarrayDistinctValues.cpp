#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = array<int, 2>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

#ifdef LOCAL
#include "../src/debug.hpp"
#else
#define debug(...) 420
#endif
// g++ -DLOCAL -Wall Practice.cpp -o bin

template<class T> bool smax(T &a, T b) {
    return a < b ? a = b, 1 : 0;
}
template<class T> bool smin(T &a, T b) {
    return a > b ? a = b, 1 : 0;
}
void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> x(n);
    for (int &i : x) {
        cin >> i;
    }
    map<int, int> frq;
    int ptr = 0;
    ll res = 0;
    for (int i = 0; i < n; i++) {
        ++frq[x[i]];
        while (sz(frq) > k) {
            if (!(--frq[x[ptr]])) frq.erase(x[ptr]);
            ++ptr;
        }
        res += i - ptr + 1;
    }
    cout << res << "\n";
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; // cin >> t;
    while (t--) solve();
}