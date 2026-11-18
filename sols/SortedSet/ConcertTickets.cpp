#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m; cin >> n >> m;
    multiset<int> tickets;
    while (n--) {
        int p; cin >> p;
        tickets.insert(p);
    }
    while (m--) {
        int m; cin >> m;
        auto it = tickets.upper_bound(m);
        if (it == begin(tickets)) {
            cout << -1 << "\n";
        } else {
            cout << *--it << "\n";
            tickets.erase(it);
        }
    }
}