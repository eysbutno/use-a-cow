#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define f first 
#define s second

vector<pair<int, int>> ord;
bool works(int x, vector<int>& nums) {
    ord.clear();
    multiset<int> rem;
    for (int& i : nums) {
        rem.insert(i);
    }
    while (!rem.empty()) {
        int pick = *rem.rbegin();
        rem.erase(rem.find(pick));
        if (!rem.count(x - pick)) {
            return false;
        }
        rem.erase(rem.find(x - pick));
        ord.push_back({pick, x - pick});
        x = pick;
    }
    return rem.empty();
}
void solve() {
    int n; cin >> n;
    int sz = n * 2;
    vector<int> nums(sz);
    for (int& i : nums) cin >> i;
    sort(begin(nums), end(nums));
    for (int i = 0; i < sz - 1; i++) {
        int sum = nums[i] + nums[sz - 1];
        if (works(sum, nums)) {
            cout << "YES" << '\n';
            cout << nums[i] + nums[sz - 1] << '\n';
            for (auto& j : ord) {
                cout << j.f << ' ' << j.s << '\n';
            }
            return;
        }
    }
    cout << "NO" << '\n';
}
int main() {
    int t; cin >> t;
    while (t--) solve();
}
/*
Two observations:
1. The optimal x must be
the largest element + another
element b/c otherwise the
largest element will never
be elminated.
2. For similar reasons to 1,
at any given moment the two numbers
chosen to be deleted must be the 
largest number not deleted and 
another number.
*/