#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define f first 
#define s second 

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    string s; cin >> s;
    int n = s.length();
    vector<int> c(n + 1), o(n + 1), w(n + 1);
    for (int i = 0; i < n; i++) {
        if (s[i] == 'C') c[i + 1]++;
        else if (s[i] == 'O') o[i + 1]++;
        else w[i + 1]++;
        c[i + 1] += c[i];
        o[i + 1] += o[i];
        w[i + 1] += w[i];
    }
    string res = "";
    int q; cin >> q;
    while (q--) {
        int a, b; cin >> a >> b;
        int c1 = c[b] - c[a - 1];
        int o1 = o[b] - o[a - 1];
        int w1 = w[b] - w[a - 1];
        if ((c1 % 2 && !(o1 % 2) && !(w1 % 2)) ||
            (!(c1 % 2) && o1 % 2 && w1 % 2)) {
            res += 'Y';
        } else {
            res += 'N';
        }
    }
    cout << res << '\n';
}
/*
String order does not matter. Some evidence that
# of C chars have different parity to # of O & W chars:

If C is odd, O & W must be even to cancel each other out.
In the process of canceling out each other, an odd # of C
characters will be left behind, which you can simplify into C.

If C is even, O & W must be odd to produce an odd # of C characters.
*/