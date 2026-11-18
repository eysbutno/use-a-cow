#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define f first 
#define s second

void calcSums(vector<ll>& nums, vector<ll>& res) {
    ll len = nums.size();
    for (int i = 0; i < 1 << len; i++) {
        ll sum = 0;
        for (int j = 0; j < len; j++) {
            if (i & (1 << j)) {
                sum += nums[j];
            }
        }
        res.push_back(sum);
    }
}
int main() {
    ll n, x; cin >> n >> x;
    vector<ll> left(n / 2), right((n + 1) / 2);
    for (int i = 0; i < n / 2; i++) {
        cin >> left[i];
    }
    for (int i = 0; i < (n + 1) / 2; i++) {
        cin >> right[i];
    }
    vector<ll> leftRes, rightRes;
    calcSums(left, leftRes);
    calcSums(right, rightRes);
    sort(begin(rightRes), end(rightRes));
    ll ans = 0;
    for (ll i : leftRes) {
        ll idx1 = lower_bound(begin(rightRes), end(rightRes)
            , x - i) - begin(rightRes);
        ll idx2 = upper_bound(begin(rightRes), end(rightRes)
            , x - i) - begin(rightRes);
        ans += idx2 - idx1;
    }
    cout << ans << '\n';
}