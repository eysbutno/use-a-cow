#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define f first 
#define s second 
#define pb push_back
#define ins insert

const int MAX = 801;
int grid[MAX][MAX], 
    pref[MAX][MAX];
bool check(int n, int k, int mid) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            pref[i][j] = (grid[i][j] > mid) +
                pref[i - 1][j] + pref[i][j - 1] 
                - pref[i - 1][j - 1];
        }
    }
    int target = (k * k) / 2 + 1;
    for (int i = k; i <= n; i++) {
        for (int j = k; j <= n; j++) {
            int sum = pref[i][j] - pref[i - k][j]
                - pref[i][j - k] + pref[i - k][j - k];
            if (sum < target) return true;
        }
    }
    return false;
}
int main() {
    int n, k; cin >> n >> k;
    int low = 2e9, high = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> grid[i][j];
            low = min(low, grid[i][j]);
            high = max(high, grid[i][j]);
        }
    }
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (check(n, k, mid)) high = mid;
        else low = mid + 1;
    }
    cout << low << '\n';
}
/*
Binary search the median.
Check function:
In order to check if a value 
M can be the median, we just need
to make sure there are less than
k^2 / 2 + 1 squares with a value
more than M. This will naturally make 
the binary search function find the answer.
*/