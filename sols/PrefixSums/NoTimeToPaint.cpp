#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define f first 
#define s second

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n, q; string a;
    cin >> n >> q >> a;
    vector<int> pf1(n + 1), pf2(n + 1);
    priority_queue<char> active;
    for (int i = 0; i < n; i++) {
        while (!active.empty() && active.top() > a[i]) {
            active.pop();
        }
        if (active.empty() || active.top() != a[i]) {
            pf1[i + 1]++; active.push(a[i]);
        }
        pf1[i + 1] += pf1[i];
    }
    reverse(begin(a), end(a));
    while (!active.empty()) active.pop();
    for (int i = 0; i < n; i++) {
        while (!active.empty() && active.top() > a[i]) {
            active.pop();
        }
        if (active.empty() || active.top() != a[i]) {
            pf2[i + 1]++; active.push(a[i]);
        }
        pf2[i + 1] += pf2[i];
    }
    while (q--) {
        int a, b; cin >> a >> b;
        cout << pf1[a - 1]  + pf2[n - b] << '\n';
    }
}