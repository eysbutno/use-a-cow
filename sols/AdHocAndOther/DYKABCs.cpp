#include <bits/stdc++.h>
using namespace std;

bool valid(int a, int b, int c,
    vector<int>& nums) {
    set<int> gen = {
        a, b, c, a + b, b + c, 
        c + a, a + b + c
    };
    for (int i : nums) {
        if (!gen.count(i)) return false;
    }
    return true;
}
void solve() {
    int n; cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    set<int> possible;
    for (int i = 0; i < n; i++) {
        possible.insert(nums[i]);
        for (int j = i + 1; j < n; j++) {
            possible.insert(abs(nums[i] - nums[j]));
        }
    }
    int cnt = 0;
    for (int i : possible) {
        for (int j : possible) {
            for (int k : possible) {
                if (i <= j && j <= k) {
                    cnt += valid(i, j, k, nums);
                }
            }
        }
    }
    cout << cnt << '\n';
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int t; cin >> t;
    while (t--) solve();
}
/*
Algorithm:
All you need to do is make the observation
that any possible values for a, b, or c are found
by subtracting the given numbers for each other.
For example, if a, b, and c are missing, you can
subtract a + b, b + c, or c + a from a + b + c to
get the individual possible values. After that,
checking each triple is easy.
*/