#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define ckmin(a, b) a = min(a, b)
#define ckmax(a, b) a = max(a, b)
#define pb push_back 
#define ins insert
#define f first 
#define s second

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n; cin >> n;
    vector<int> x(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
    }
    stack<int> s;
    for (int i = 1; i <= n; i++) {
        while (size(s) && x[s.top()] >= x[i]) {
            s.pop();
        }
        if (s.empty()) cout << 0;
        else cout << s.top();
        cout << ' ';
        s.push(i);
    }
}
/**
 * Maintain a mono-decreasing stack.
 * (You could also, just like, sweep it.
 * But that's too smart for dumb me.)
*/