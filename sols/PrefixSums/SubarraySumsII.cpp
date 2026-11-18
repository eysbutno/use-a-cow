#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, x; cin >> n >> x;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];
    map<long long, long long> seen = {{0, 1}};
    long long ans = 0; long long prefix = 0;
    for (int i : nums) {
        prefix += i;
        ans += seen[prefix - x];
        seen[prefix]++;
    }
    cout << ans << endl;
    return 0;
}