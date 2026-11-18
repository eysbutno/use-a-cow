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
    for (int& i : a) {
        cin >> i;
    }
    int temp = 0;
    for (int i : a) {
        temp = max(temp + 1, i);
    }
    int mx = -1, idx = -1;
    for (int i = 0; i < n; i++) {
        if (a[i] > mx) {
            mx = a[i];
            idx = i;
        }
    }
    for (int i = 0; i < n; i++) {
        if (i == idx) continue;
        if (i < idx) {
            mx = max(mx, a[i] + n - 1 - i);
        } else {
            mx = max(mx, a[i] + i);
        }
    }
    int res = min(temp, mx);
    temp = 0;
    reverse(begin(a), end(a));
    for (int i : a) {
        temp = max(temp + 1, i);
    }
    cout << min(res, temp) << '\n';
}
/**
 * Simulate 3 starting locations: start,
 * end, and the highest element.
 * 
 * NOTE: don't directly simulate the process;
 * just make the observation that the worst case
 * scenario for an element is that the spell covers 
 * an entire prefix/suffix before reaching the current one.
*/