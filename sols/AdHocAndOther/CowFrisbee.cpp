#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define f first 
#define s second 

ll res(int n, vector<int>& nums) {
    stack<pair<int, int>> stk;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        while (!stk.empty() && 
            stk.top().f < nums[i]) {
            stk.pop();
        }
        if (!stk.empty()) {
            ans += i - stk.top().s + 1;

        }
        stk.push({nums[i], i});
    }
    return ans;
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n; cin >> n;
    vector<int> nums(n);
    for (int& i : nums) cin >> i;
    ll sum = 0;
    sum += res(n, nums);
    reverse(begin(nums), end(nums));
    sum += res(n, nums);
    cout << sum << '\n';
}
/*
Ok I feel like I COULD have gotten it,
if I did more stack problems... dammit.

Algorithm: Maintain a monotonic stack, aka
the orders are in descending order. Pop any elements
that came before the current one that are
less than the current element. If there's still 
an element, you add that to the answer.
*/