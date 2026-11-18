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

const int N = 5e5 + 20;
int calc(vector<int>& a, 
    vector<int>& b, int n) {
    vector<int> store(N);
    for (int i = 0; i < n; i++) {
        store[b[i]] = i + 1;
    }
    vector<int> ans(N);
    for (int i = 0; i < n; i++) {
        int d = abs(store[a[i]]
                    - (i + 1));
        if (store[a[i]] == 0) {
            continue;
        }
        if (store[a[i]] < i + 1) {
            d = n - d;
        }
        ans[d]++;
    }
    int res = 0;
    for (int i = 0; i < N; i++)
        ckmax(res, ans[i]);
 
    return res;
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n, k; cin >> n >> k;
    vector<int> a(k), b(k);
    set<int> seen;
    for (int i = 0; i < k; i++) {
        cin >> a[i];
        seen.ins(a[i]);
    }
    vector<int> mp(N);
    for (int i = 0; i < k; i++) {
        cin >> b[i];
        seen.ins(b[i]);
        mp[b[i]] = i + 1;
    }
    int ans = n - size(seen), comp = 0;
    for (int i = 0; i < 2; i++) {
        ckmax(comp, calc(a, b, k));
        reverse(all(a));
    }
    cout << ans + comp << '\n';
}