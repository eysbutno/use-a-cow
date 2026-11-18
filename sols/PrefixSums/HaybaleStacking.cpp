#include <bits/stdc++.h>
using namespace std;

void setIO(string name = "") {
    ios_base::sync_with_stdio(0); cin.tie(0);
    if (name.size()) {
       freopen((name + ".in").c_str(), "r", stdin);
       freopen((name + ".out").c_str(), "w", stdout);
    }
}
int main() {
    setIO("stacking");
    int n, k; cin >> n >> k;
    vector<int> haybales(n + 1);
    vector<int> data(n);
    while (k--) {
        int a, b; cin >> a >> b;
        haybales[--a]++; haybales[b]--;
    }
    int num = 0;
    for (int i = 0; i < n; i++) {
        num += haybales[i];
        data[i] = num;
    }
    sort(begin(data), end(data));
    cout << data[n / 2] << "\n";
    return 0;
}