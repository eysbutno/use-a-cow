#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define pb push_back
#define ins insert
#define f first 
#define s second 

const string BES = "bessie";
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    string s; cin >> s;
    int n = s.length();
    vector<int> lst(n), idx(6);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 6; j++) {
            if (j == 0) {
                idx[j] = max(idx[j], i);
            } else {
                idx[j] = max(idx[j], idx[j - 1] + 1);
            }
            while (idx[j] < n && s[idx[j]] != BES[j]) {
                ++idx[j];
            }
        }
        lst[i] = min(idx[5], n) + 1;
    }
    ll sum = 0;
    vector<ll> tot(n + 1);
    for (int i = n - 1; i >= 0; i--) {
        tot[i] = n + 1 - lst[i];
        if (tot[i] > 0) {
            tot[i] += tot[lst[i]];
        }
        sum += tot[i];
    }
    cout << sum << '\n';
}
/*
The answer can be defined as the sum
of tot[i], if i is in [0, |s| - 1].
tot[i] = sum(B(s)) for all prefixes
of [i, |s| - 1].

tot[i] = |s| + 1 - lst[i] + tot[lst[i]],
where lst[i] is defined as the first index
where [i... lst[i] - 1] is a Bessie occurence.

Reasoning:
For all prefixes [i, lst[i]... |s| - 1], there
will be an extra occurence of Bessie, thus the
need to add one more. tot[lst[i]] is added
because after lst[i] it's basically just tot[lst[i]].

To compute lst[i], have an array that contains the first 
occurence of a letter in Bessie. 

Note: 
The lst[i] code runs in O(N) because idx[i] is only
updated as needed.
*/