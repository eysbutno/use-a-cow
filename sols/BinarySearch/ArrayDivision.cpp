#include <bits/stdc++.h>
using namespace std;
#define ll long long
 
vector<ll> nums; int n, k;
bool check(ll m) {
    ll sub = 0, ans = 0;
    for (ll i : nums) {
        if (sub + i > m) {
            sub = i; ans++;
        } else {
            sub += i;
        }
    }
    return ans < k;
}
int main() {
    cin >> n >> k; nums.resize(n);
    ll low = 0, high = 0;
    for (int i = 0; i < n; i++) {
        cin >> nums[i]; 
        high += nums[i];
        low = max(low, nums[i]);
    }
    while (low < high) {
        ll mid = (low + high) / 2;
        if (check(mid)) high = mid;
        else low = mid + 1;
    }
    cout << low << "\n";
}