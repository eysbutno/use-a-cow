#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define f first 
#define s second 

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n, k; cin >> n >> k;
    vector<int> nums(n);
    for (int& i : nums) {
        cin >> i;
    }
    sort(begin(nums), end(nums), 
        greater<int>());
    vector<int> itvs = {nums[0] / 12 + 1};
    for (int i = 1; i < n; i++) {
        int res = nums[i] / 12 + 1;
        if (itvs.back() != res) {
            itvs.push_back(res);
        }
    }
    itvs.push_back(0);
    int ans = (int) itvs.size() * 12 - 12;
    vector<int> dists;
    for (int i = 0; i < itvs.size() - 1; i++) {
        dists.push_back(itvs[i] - itvs[i + 1]);
        ans += (dists.back() - 1) * 12;
    }
    sort(begin(dists), end(dists), 
        greater<int>());
    for (int i = 1; i < k; i++) {
        ans -= (dists[i - 1] - 1) * 12;
    }
    cout << ans << '\n';
}
/*
Idea is to place each cow on an interval.
A cow must spend an entire interval to visit
each cow, and must either wait out or skip all
the time in between. Greedily sort the gaps
and teleport during the longest gaps.
*/