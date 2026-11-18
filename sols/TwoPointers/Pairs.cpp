#include <bits/stdc++.h>
using namespace std;
// standard use case of two pointers
int main() {
    int n, x; cin >> n >> x;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];
    sort(begin(nums), end(nums));
    int i = 0, j = n - 1; // pointers
    bool flag = 0;
    while (i < j) {
        if (nums[i] + nums[j] == x) {flag = 1; break;}
        else if (nums[i] + nums[j] < x) i++;
        else j--;
    }
    cout << flag << endl;
    return 0;
}