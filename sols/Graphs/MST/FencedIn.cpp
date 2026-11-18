#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define pb push_back
#define ins insert
#define f first 
#define s second 

int main() {
	cin.tie(0) -> sync_with_stdio(0);
    freopen("fencedin.in", "r", stdin);
    freopen("fencedin.out", "w", stdout);
    ll a, b, n, m; 
    cin >> a >> b >> n >> m;
    vector<ll> v(n + 2), h(m + 2);
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> h[i];
    }
    v[n + 1] = a, h[m + 1] = b;
    sort(all(v)), sort(all(h));
    for (int i = 0; i <= n; i++) {
        v[i] = v[i + 1] - v[i];
    }
    for (int i = 0; i <= m; i++) {
        h[i] = h[i + 1] - h[i];
    }
    v.pop_back(), h.pop_back();
    sort(all(v)), sort(all(h));
    ll res = v[0] * m + h[0] * n;
    int p1 = 1, p2 = 1;
    ++m, ++n;
    while (p1 < n && p2 < m) {
        if (v[p1] < h[p2]) {
            res += v[p1] * (m - p2);
            ++p1;
        } else {
            res += h[p2] * (n - p1);
            ++p2;
        }
    }
    cout << res << '\n';
}
/**
 * TASK: Fenced In (Platinum).
 * Observation 1: You always remove
 * fences in "blocks", in order of length.
 * 
 * Observation 2: If given an optimal solution,
 * swapping two adjacent rows or two adjacent columns
 * does not change the answer.
 * 
 * So, what can we do with observation 2? Well, it 
 * justifies removing everything into blocks. Basically,
 * now that we can justify removing everything in blocks.
 * 
 * Every time we remove a block of horizontal/vertical 
 * fences, you need to know how many of these fences you
 * want to remove. So, how many do you need to remove?
 * 
 * The answer is that, if we remove a strip of fences of
 * some orientation, you need to remove (total possible - 
 * removed in the opposite direction).
 * 
 * Why is this? If we think about it for a little bit,
 * all the "blocks" of fences horizontally that you might
 * want to remove are already united, so you only need to
 * remove one block for each one of those. Why? Reference
 * observation 2.
*/