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

set<int> uniq;
multiset<int> szs;
int n, m;
void rem(int x) {
    szs.erase(szs.find(x));
}
void flip(int idx) {
    if (idx == 0 || idx == n) {
        return;
    }
    auto it = uniq.find(idx);
    if (it != end(uniq)) {
        int a = *prev(it), b = *next(it);
        rem(idx - a), rem(b - idx);
        szs.ins(b - a);
        uniq.erase(idx);
    } else {
        it = uniq.ins(idx).f;
        int a = *prev(it), b = *next(it);
        rem(b - a);
        szs.ins(idx - a);
        szs.ins(b - idx);
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    string s; cin >> s;
    n = s.length();
    uniq.ins(0);
    uniq.ins(n);
    for (int i = 0; i < n; i++) {
        if (s[i] != s[i + 1]) {
            uniq.ins(i + 1);
        }
    }
    for (auto it = begin(uniq); next(it) != end(uniq); it++) {
        szs.ins(*next(it) - *it);
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
        int x; cin >> x;
        flip(x - 1), flip(x);
        cout << *szs.rbegin() << ' ';
    }
}
/**
 * Maintain the intervals using
 * a set. Maintain set of nums
 * with a multiset.
 * 
 * Implementation Details:
 * Each bit flip can be viewed
 * as inserting index i and i + 1
 * in the unique location set.
 * To do that, you have to use
 * some iterator magic.
*/