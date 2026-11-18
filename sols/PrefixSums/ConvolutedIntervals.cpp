#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define f first 
#define s second 

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    ll n, m; cin >> n >> m;
    vector<int> st(m + 1), ed(m + 1);
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        st[a]++, ed[b]++;
    }
    vector<ll> res(m * 2 + 2);
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= m; j++) {
            res[i + j] += (ll) st[i] * st[j];
            res[i + j + 1] -= (ll) ed[i] * ed[j];
        }
    }
    ll running = 0;
    for (int i = 0; i <= 2 * m; i++) {
        running += res[i];
        cout << running << '\n';
    }
}
/*
Algorithm:
First step is realizing that you can use
prefix sums to calculate each value k
by incrementing at location a_i + a_j
and decrementing at location b_i + b_j + 1
and by taking the prefix sum at indice k.

To improve time complexity, instead of going
through all the pairs, you can simply mark
where the first and last indices are for each
interval. Brute forcing locations is always correct
because either way you're going to increment that location,
albeit in a different order.
*/