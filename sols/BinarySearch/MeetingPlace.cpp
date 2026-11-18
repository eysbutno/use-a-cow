#include <bits/stdc++.h>
using namespace std;
#define ld long double

int main() {
	int n; cin >> n;
	vector<ld> x(n), v(n);
	for (ld& i : x) cin >> i;
	for (ld& i : v) cin >> i;
	auto check = [&](ld mid) {
		ld lb = -1e9, ub = 1e9;
		for (int i = 0; i < n; i++) {
			lb = max(lb, x[i] - mid * v[i]);
			ub = min(ub, x[i] + mid * v[i]);
		}
		return lb <= ub;
	};
	ld m1 = *max_element(begin(x), end(x));
	ld m2 = *min_element(begin(v), end(v));
	ld low = 0, high = m1 / m2 + 1, 
		ans = -1;
	while (low <= high) {
        ld mid = (low + high) / 2.0;
        if (check(mid)) {
			ans = mid;
			high = mid - 1e-8;
		} else {
			low = mid + 1e-8;
		}
    }
	cout.precision(13);
    cout << ans << "\n";
}
/*
I HATE DECIMAL PRECISION!!!
Binary search the time. Maintain
an upper and lower bound to see
if there's a feasible location.
*/