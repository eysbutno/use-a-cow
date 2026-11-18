#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define f first 
#define s second 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    ll n, m; cin >> n >> m;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(begin(a) + 1, end(a));
    vector<ll> pf(n + 1);
    for (int i = 1; i <= n; i++) {
        pf[i] = a[i] + pf[i - 1];
    }
    auto check = [&](int mid) {
        ll cnt = 0;
        for (int i = 1; i <= n; i++) {
            if (a[i] + a[n] < mid) continue;
            int idx = lower_bound(begin(a) + i, end(a), 
                mid - a[i]) - begin(a);
            cnt += 2 * (n - idx + 1) - (idx == i);
        }
        // could have used 2P but too lazy lol
        return cnt >= m;
    };
    int low = 0, high = 2e5;
    while (low < high) {
        int mid = (low + high + 1) / 2;
        if (check(mid)) low = mid;
        else high = mid - 1;
    }
    ll sum = 0, cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] + a[n] < low) continue;
        int idx = lower_bound(begin(a) + i, end(a), 
            low - a[i]) - begin(a);
        sum += 2 * ((n - idx + 1 - (idx == i)) * 
            a[i] + (pf[n] - pf[idx - 1]));
        cnt += 2 * (n - idx + 1) - (idx == i);
    }
    sum -= (cnt - m) * low;
    cout << sum << '\n';
}
/*
Time Complexity: O(Nlog^2(n))
(it's easy to get down to O(Nlog(N)))
Hardest part is figuring out what to actually
binary search. In this case, we binary search
the highest minimum handshake value for >= m 
handshakes. After that, use prefix sums to
calculate the answer.

Note:
"Why does just subtracting (cnt - m) * low work
to get the answer? What if the lowest set of handshakes
that makes the set of handshakes > m has unique numbers?"
Answer: If that was the case, low would be higher.
*/