#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    freopen("highcard.in", "r", stdin);
    freopen("highcard.out", "w", stdout);
    int n; cin >> n;
    vector<bool> elsie(n * 2 + 1);
    for (int i = 0; i < n; i++) {
        int card; cin >> card;
        elsie[card] = 1;
    }
    vector<int> bes, els;
    for (int i = 1; i <= n * 2; i++) {
        if (elsie[i]) els.push_back(i);
        else bes.push_back(i);
    }
    sort(begin(bes), end(bes));
    sort(begin(els), end(els));
    int p1 = 0, p2 = 0, ans = 0;
    while (p1 < n && p2 < n) {
        if (bes[p1] > els[p2]) {
            p1++, p2++, ans++;
        } else {
            p1++;
        }
    }
    cout << ans << '\n';
}