#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define f first 
#define s second 

template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
const int MOD = 998244353;
int main() {
	cin.tie(0) -> sync_with_stdio(0);
    int n; cin >> n;
    vector<char> s(1 << n);
    for (int i = 1; i < (1 << n); i++) {
        cin >> s[i];
    }
    auto dfs = [&](int u, auto&& dfs) 
             -> pair<string, ll> {
        string add(1, s[u]);
        if (u * 2 >= (1 << n)) {
            return {add, 1};
        }
        auto [s1, p1] = dfs(u * 2, dfs);
        auto [s2, p2] = dfs(u * 2 + 1, dfs);
        if (s1 < s2) swap(s1, s2);
        ll ways = (p1 * p2) % MOD;
        if (s1 != s2) ways = (ways * 2) % MOD;
        add += s1, add += s2;
        return {add, ways};
    };
    cout << dfs(1, dfs).s << "\n";
}
/**
 * TASK: E. Preorder (CF)
 * Problem Statement Key Points:
 * 1. Given a perfect binaryu tree.
 * 2. Find # of different preorder strings,
 *    if you can swap the children.
 * 
 * There are two cases, for each vertex:
 * Case 1: s_l can equal s_r.
 * Then, swapping the subtrees does nothing.
 * Case 2: They will never be equal.
 * Then, swapping the subtrees adds a multiple of 2.
 * 
 * To detect when a substring can equal another one,
 * you can try to maximize the resulting string. This
 * will always detect "collisions".
*/
/**
  * 1. Can a graph be constructed?
  * 2. How can we reuse information?
  * 3. Prove/justify any observations.
  * 4. For math formulas, try rewriting them.
  * 5. Break down the problem, or maybe reframe it.
  * 6. Try multiple techniques.
*/