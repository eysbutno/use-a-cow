#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int n, m, k; cin >> n >> m >> k;
    vector<int> app(n); vector<int> apt(m);
    for (int i = 0; i < n; i++) cin >> app[i];
    for (int i = 0; i < m; i++) cin >> apt[i];
    sort(begin(app), end(app));
    sort(begin(apt), end(apt));
    int c1 = 0; int c2 = 0; int count = 0;
    while (c1 < n && c2 < m) {
        if (abs(app[c1] - apt[c2]) <= k) {c1++; c2++; count++;}
        else if (apt[c2] + k > app[c1]) c1++;
        else c2++;
    }
    cout << count << endl;
    return 0;
}