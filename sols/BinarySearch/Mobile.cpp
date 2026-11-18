#include <bits/stdc++.h>
using namespace std;
using ld = long double;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define ckmax(a, b) a = max(a, b)
#define ckmin(a, b) a = min(a, b)
#define f first 
#define s second 

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n, l; cin >> n >> l;
    vector<pii> loc(n);
    for (auto& i : loc) {
        cin >> i.f >> i.s;
    }
    auto len = [&](ld d, ld y) {
        return sqrt(d * d - y * y);
    };
    auto check = [&](ld d) {
        ld far = 0;
        for (int i = 0; i < n; i++) {
            if (d < abs(loc[i].s)) {
                continue;
            }
            ld dx = len(d, loc[i].s);
            ld l = loc[i].f - dx,
                r = loc[i].f + dx;
            if (l <= far) ckmax(far, r);
        }
        return far >= l;
    };
    ld low = 0, high = 1.5e9, 
        prec = 1e-3;
    while (high - low > prec) {
        ld mid = (low + high) / 2;
        if (check(mid)) {
            high = mid;
        } else {
            low = mid;
        }
    }
    cout << setprecision(4);
    cout << low << '\n';
}
/**
 * Binary search the minimum
 * distance needed to cover the
 * highway. That's the answer.
 * 
 * Note: cannot just create intervals
 * and sort them. That's too slow.
*/