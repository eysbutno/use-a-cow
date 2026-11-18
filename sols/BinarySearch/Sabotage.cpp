#include <bits/stdc++.h>
using namespace std;
#define f first 
#define s second
typedef long long ll;

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    freopen("sabotage.in", "r", stdin);
    freopen("sabotage.out", "w", stdout);
    cout << setprecision(3) << fixed;
    int n; cin >> n;
    vector<int> cows(n);
    int highest = 0;
    for (int& i : cows) {
        cin >> i; highest = max(highest, i);
    }
    double low = 0, high = highest, precision = 1e-5;
    auto check = [&](double mid) {
        double sum = 0, most = INT_MIN;
        for (int i : cows) {
            sum += i - mid;
        }
        double best = 0, cur = 0;
        for (int i = 1; i < n - 1; i++) {
            cur += cows[i] - mid;
            best = max(cur, best);
            cur = max(0.0, cur);
            most = max(cows[i] - mid, most);
        }
        best = (!best) ? most : best;
        return sum <= best;
    };
    while (high - low > precision) {
        double mid = (low + high) / 2;
        if (check(mid)) high = mid;
        else low = mid;
    }
    cout << low << "\n";
}
/*
Type: Binary Search
Time Complexity: O(NlogN)
Algorithm:
Binary search the milk production possible
after the sabotage. The check() function
searches for the greatest subarray that
Farmer Paul can take using Kadane's algorithm.
If that subarray or the best cow is greater than the
subarray, then it's possible for that average to be achieved.
*/