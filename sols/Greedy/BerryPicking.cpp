#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    freopen("berries.in", "r", stdin);
    freopen("berries.out", "w", stdout);
    int n, k; cin >> n >> k;
    vector<int> b(n);
    int most = 0;
    for (int& i : b) {
        cin >> i; most = max(most, i);
    }
    int ans = 0;
    for (int i = 1; i <= most; i++) {
        int groups = 0;
        for (int j : b) groups += j / i;
        if (groups < k / 2) continue;
        if (groups >= k) {
            ans = max(ans, (k / 2) * i);
            continue;
        }
        int temp = (groups - k / 2) * i;
        sort(begin(b), end(b), [&](int& x, int&y) {
            return (x % i) > (y % i);
        });
        for (int j = 0; j + groups < k; j++) {
            temp += (b[j] % i);
        }
        ans = max(ans, temp);
    }
    cout << ans << '\n';
}
/*
Algorithm (because I failed this one)
Honestly, I don't really consider this a greedy
algorithm. But here it goes. Try to find a number
such that you can fill >= k / 2 baskets of berries
with this number of berries in each basket. If you can fill
>= k baskets, the temporary answer is just (k / 2) * i.
Otherwise, Bessie will get the leftover berries from
the berry bushes with the most extra.
*/