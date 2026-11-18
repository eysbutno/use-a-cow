#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define pb push_back
#define ins insert
#define f first 
#define s second 
    
const int N = 3e5, M = 8;
int a[N][M], b[N], n, m;
vector<int> adj[256];
pair<int, int> res;
bool check(int mid) {
    vector<int> idx(1 << m, -1);
    for (int i = 0; i < n; i++) {
        b[i] = 0;
        for (int j = 0; j < m; j++) {
            if (a[i][j] >= mid) {
                b[i] |= (1 << j);
            }
        }
        idx[b[i]] = i;
    }
    for (int i = 0; i < n; i++) {
        for (int j : adj[b[i]]) {
            if (idx[j] != -1) {
                res = {i + 1, idx[j] + 1};
                return true;
            }
        }
    }
    return false;
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    int RES = (1 << m) - 1;
    for (int i = 0; i < (1 << m); i++) {
        for (int j = i + 1; j < (1 << m); j++) {
            if ((i | j) == RES) {
                adj[i].pb(j);
                adj[j].pb(i);
            }
        }
    }
    adj[RES].pb(RES);
    // ^ in case ig
    int low = 0, high = 1e9;
    while (low < high) {
        int mid = (low + high + 1) / 2;
        if (check(mid)) low = mid;
        else high = mid - 1;
    }
    if (!res.f && !res.s) {
        cout << "1 1";
    } else {
        cout << res.f << ' ' << res.s;
    }
}
/**
 * Binary search the value.
 * Do some bit operator magic.
*/