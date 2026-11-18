#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    long long n, q; cin >> n >> q;
    vector<long long> nums(n + 1);
    vector<long long> prefix(n + 1);
    prefix[0] = 0;
    for (long long i = 1; i <= n; i++) cin >> nums[i];
    for (long long i = 1; i <= n; i++) {
        prefix[i] = prefix[i - 1] + nums[i];
    }
    for (long long i = 0; i < q; i++) {
        long long l, r; cin >> l >> r;
        cout << prefix[r] - prefix[l] << endl;
    }
    return 0;
}