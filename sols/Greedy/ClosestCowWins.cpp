#include <bits/stdc++.h>
using namespace std;
#define ll long long 
#define f first 
#define s second 

int main() {
    int k, m, n; 
    cin >> k >> m >> n;
    vector<ll> p(k), t(k);
    vector<pair<ll, ll>> locs(k);
    for (int i = 0; i < k; i++) {
        cin >> locs[i].f >> locs[i].s;
    }
    sort(begin(locs), end(locs));
    for (int i = 0; i < k; i++) {
        p[i] = locs[i].f;
        t[i] = locs[i].s;
    }
    vector<ll> nhoj(m);
    for (int i = 0; i < m; i++) {
        cin >> nhoj[i];
    }
    sort(begin(nhoj), end(nhoj));
    auto res = [&](int l, int r) {
        ll c1 = 0, tot = 0;
        int idx1 = lower_bound(begin(p), 
            end(p), l) - begin(p);
        int idx2 = lower_bound(begin(p), 
            end(p), r) - begin(p);
        for (int i = idx1; i < idx2; i++) {
            tot += t[i];
        }
        int j = idx1;
        ll soFar = 0, len = (r - l) / 2;
        for (int i = idx1; i < idx2; i++) {
            while (j < idx2 && (p[j] - 
                p[i]) * 2 < r - l) {
                soFar += t[j]; ++j;
            }
            c1 = max(soFar, c1);
            soFar -= t[i];
        }
        return make_pair(c1, tot);
    };
    vector<ll> cows;
    for (int i = 1; i < m; i++) {
        auto p = res(nhoj[i - 1], nhoj[i]);
        cows.push_back(p.f);
        cows.push_back(p.s - p.f);
    }
    ll temp = 0;
    for (int i = 0; i < k; i++) {
        if (p[i] < nhoj[0]) {
            temp += t[i];
        } else {
            break;
        }
    }
    cows.push_back(temp);
    temp = 0;
    for (int i = k - 1; i >= 0; i--) {
        if (p[i] > nhoj[m - 1]) {
            temp += t[i];
        } else {
            break;
        }
    }
    cows.push_back(temp);
    sort(begin(cows), end(cows), greater<ll>());
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ans += cows[i];
    }
    cout << ans << '\n';
}
/*
This problem certainly is a doozy.
1. Notice that you can essentially break
up this problem into subproblems of 
intervals (starting and ending with a Nhoj cow).
2. Notice that you greedily sort the best results
to get your final answer.

To calculate how much each interval can yield, you
calculate the yield for placing either one or two cows.
For one cow, use two pointers, for two just sum up everything.
*/