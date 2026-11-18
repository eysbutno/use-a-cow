#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    freopen("cardgame.in", "r", stdin);
    freopen("cardgame.out", "w", stdout);
    int n; cin >> n;
    vector<bool> elsie(n * 2 + 1);
    vector<int> hEls, hBes, lEls, lBes;
    for (int i = 0; i < n; i++) {
        int card; cin >> card;
        if (i < n / 2) hEls.push_back(card);
        else lEls.push_back(card);
        elsie[card] = 1;
    }
    vector<int> bes;
    for (int i = 1; i <= n * 2; i++) {
        if (!elsie[i]) bes.push_back(i);
    }
    sort(begin(bes), end(bes), greater<int>());
    for (int i = 0; i < n / 2; i++) {
        hBes.push_back(bes[i]);
    }
    for (int i = n / 2; i < n; i++) {
        lBes.push_back(bes[i]);
    }
    sort(begin(hBes), end(hBes));
    sort(begin(lBes), end(lBes));
    sort(begin(hEls), end(hEls));
    sort(begin(lEls), end(lEls));
    int p1 = 0, p2 = 0, ans = 0;
    while (p1 < (n / 2) && p2 < (n / 2)) {
        if (hBes[p1] > hEls[p2]) {
            p1++, p2++, ans++;
        } else {
            p1++;
        }
    }
    p1 = 0, p2 = 0;
    while (p1 < (n / 2) && p2 < (n / 2)) {
        if (lBes[p1] < lEls[p2]) {
            p1++, p2++, ans++;
        } else {
            p2++;
        }
    }
    cout << ans << '\n';
}
/*
High Card for Silver, except you need
to split all of Bessie's highest card
for the high card part and all of her
lowest card for the low card part.
Solve the two tasks and get your answer.
*/