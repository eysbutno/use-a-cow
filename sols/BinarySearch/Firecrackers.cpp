#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define f first 
#define s second 
#define pb push_back
#define ins insert

void solve() {
    int n, m, a, b;
    cin >> n >> m >> a >> b;
    vector<int> s(m);
    for (int& i : s) {
        cin >> i;
    }
    sort(begin(s), end(s));
    auto check = [&](int mid) {
        int fin = 0, cur = 0;
        if (a > b) {
            fin = n - b;
        } else {
            fin = b - 1;
        }
        for (int i = mid - 1; i >= 0; i--) {
            if (s[i] + cur >= fin) {
                return false;
            }
            ++cur;
        }
        return true;
        /*
        Assumes hooligan immediately plants
        all the firecrackers and then books it.
        */
    };
    int low = 0, high = min(m, abs(a - b) - 1);
    // hooligan at most can detonate abs(a - b) - 1
    // fireworks b/c time it takes for cop to reach
    // is abs(a - b), but a firework placed at the
    // last second cannot detonate under any circumstances
    while (low < high) {
        int mid = (low + high + 1) / 2;
        if (check(mid)) low = mid;
        else high = mid - 1;
    }
    cout << low << '\n';
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t; cin >> t;
    while (t--) solve();
}
/*
Observation 1:
The hooligan should never 
walk towards the guard.
Reasoning: It's obvious.

Observation 2:
The hooligan, in an optimal scenario,
will always drop some prefix of fireworks,
assuming the fireworks are in ascending order.
Reasoning: It doesn't make sense for the hooligan
to do otherwise.

Observation 3:
The hooligan, in an optimal play, will plant
all the fireworks at once, then leave.
Reasoning: Doing otherwise just increases the
final detonation time.
*/