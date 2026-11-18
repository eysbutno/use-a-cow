#include <bits/stdc++.h>
using namespace std;
#define f first 
#define s second 

set<int> calc(int n, int m,
    vector<int>& nums) {
    set<int> unique;
    int sz = nums.size();
    for (int i = 0; i < 1 << sz; i++) {
        int sum = 0;
        for (int j = 0; j < sz; j++) {
            if (i & (1 << j)) {
                sum += nums[j] % m;
                sum %= m;
            }
        }
        unique.insert(sum);
    }
    return unique;
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n, m; cin >> n >> m;
    vector<int> left(n / 2),
        right((n + 1) / 2);
    for (int& i : left) cin >> i;
    for (int& i : right) cin >> i;
    set<int> l = calc(n, m, left);
    set<int> r = calc(n, m, right);
    int res = 0;
    for (int i : l) {
        auto it = r.lower_bound(m - i);
        res = max(res, (i + *(--it)) % m);
    }
    cout << res << '\n';
}
/*
MITM & merge results.
*/