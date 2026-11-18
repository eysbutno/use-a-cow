#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define pb push_back
#define ins insert
#define f first 
#define s second 

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    a.pb(0);
    string res = "";
    int i = 0;
    while (i != 0 || a[i] != 0) {
        while (a[i] > 0) {
            res += 'R';
            a[i]--;
            i++;
        }
        while (i > 0 && (a[i] == 0
            || a[i - 1] > 1)) {
            res += 'L';
            a[i - 1]--;
            i--;
        }
    }
    cout << res << '\n';
}
/**
 * Greedily make turns.
*/