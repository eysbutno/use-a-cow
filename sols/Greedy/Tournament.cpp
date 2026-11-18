#include <bits/stdc++.h>
using namespace std; 
using pii = pair<int, int>;
#define pb push_back
#define f first 
#define s second 

void solve() {
    int n, m; cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<int> b = a;
    sort(begin(b), end(b));
    int res = 0;
    for (int i = 0; i < n; i++) {
        if (m < b[i]) break;
        m -= b[i];
        res++;
    }
    if (res != 0 && res != n && 
        m + b[res - 1] >= a[res]) {
        ++res;
    }
    cout << n + 1 - res << '\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
/*
Observation 1:
Contestant i will have i wins.

Observation 2:
If you beat b opponents,
your placement at the very least
will be n + 1 - b.

Reasoning:
For all opponents, i < x,
even if they beat you they won't
change your place. Therefore, 
there are n - b opponents who
have strictly more wins, so your
place is n - b + 1.
To get one place higher, if you can swap out 
the previously most time consuming option,
you can score one place higher. This also
covers the scenario where you're tied with
someone and beat them. It's -1 places for
obvious reasons.
*/