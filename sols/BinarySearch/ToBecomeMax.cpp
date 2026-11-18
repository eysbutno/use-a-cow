#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define pb push_back
#define ins insert
#define f first 
#define s second 

void solve() {
    int n, k; 
    cin >> n >> k;
    vector<int> a(n);
    int low = 0, high = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        low = max(low, a[i]);
    }
    high = low + k;
    auto check = [&](int mid) {
        ll ops = 2e9;
        for (int i = 0; i < n; i++) {
            // pos i is the max element
            ll temp = 0, prev = mid;
            for (int j = i; j < n; j++) {
                if (j == n - 1 && a[j] < prev) {
                    temp = 2e9; break;
                }
                if (a[j] >= prev) {
                    break;
                }
                temp += prev - a[j];
                --prev;
            }
            if (temp < ops) {
                ops = temp;
            }
        }
        return ops <= (ll) k;
    };
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
/**
 * Observation 1:
 * O(N^2) is allowed.
 * 
 * Observation 2:
 * You can binary search.
 * 
 * Observation 3:
 * Just binary search brute force
 * bash the problem.
*/