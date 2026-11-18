#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define f first 
#define s second 
#define pb push_back
#define ins insert

const int MAX = 1e3 + 1,
    MOD = 1e6;
int h, k, a[MAX];
int dist(int a, int b) {
    if (a > b) {
        return min(a - b, MOD - a + b);
    }
    return min(b - a, MOD - b + a);
}
bool check(int mid) {
    for (int i = 0; i < h; i++) {
        // first hydrant placed with respect
        // to hydrant i
        int cnt = 1, idx = i, ptr = (i + 1) % h;
        while (ptr != i) {
            if (dist(a[idx], a[ptr]) > 2 * mid) {
                ++cnt; idx = ptr;
            }
            ptr = (ptr + 1) % h;
        }
        if (cnt <= k) return true;
    }
    return false;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cin >> h;
    for (int i = 0; i < h; i++) {
        cin >> a[i];
    }
    sort(a, a + h);
    cin >> k;
    int low = 0, high = 1e6;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (check(mid)) high = mid;
        else low = mid + 1;
    }
    cout << low << '\n';
}
/*
Binary search the distance.
To check, just use a greedy algorithm.
Reminds me of "Closest Cow Wins".
*/