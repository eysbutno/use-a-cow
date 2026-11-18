#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define f first 
#define s second 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n, k; cin >> n >> k;
    vector<int> nums(n);
    for (int& i : nums) cin >> i;
    int low = 0, high = 2e5;
    auto check = [&](int mid) {
        vector<int> f(n);
        for (int i = 0; i < n; i++) {
            f[i] = (nums[i] >= mid) ? 1 : -1;
            if (i) f[i] += f[i - 1];
        }
        int mn = 0, diff = f[k - 1];
        for (int i = k; i < n; i++) {
            mn = min(mn, f[i - k]);
            diff = max(diff, f[i] - mn);
        }
        return diff > 0;
    };
    while (low < high) {
        int mid = (low + high + 1) / 2;
        if (check(mid)) low = mid;
        else high = mid - 1;
    }
    cout << low << '\n';
}
/*
How did I not get this problem??
Algorithm:
Bisearch the best median.
To do this, you use an algorithm
kind of like kadanes, except for 
a subarray of length k.
*/