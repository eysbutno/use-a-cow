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
int main() {
	cin.tie(0) -> sync_with_stdio(0);
    int n; cin >> n;
    vector<int> a;
    {
        string s; cin >> s;
        for (int i = 1; i < n; i++) {
            int x = s[i - 1] - '0',
                y = s[i] - '0';
            a.push_back(abs(x - y));
        }
        --n; // reduced to n - 1
    }
    auto binom = [&](int n, int k) -> int {
        return (int) ((n & k) == k);
    };
    auto solve = [&]() -> int {
        int res = 0;
        for (int i = 0; i < n; i++) {
            if (a[i]) res += binom(n - 1, i);
        }
        return res % 2;
    };
    int cnt = 0;
    for (int i : a) {
        if (i == 1) ++cnt;
    }
    if (cnt == 0) {
        for (int &i : a) {
            i /= 2;
        }
        cout << solve() * 2 << "\n";
    } else {
        for (int &i : a) {
            if (i == 2) i = 0;
        }
        cout << solve() << "\n";
    }
}
/**
 * TASK: 123 Triangle.
 * Perform one operation to make all the elements
 * in the range [0, 2]. We can break up all cases into
 * the case where all the elements are (0, 1).
 * 
 * To solve the (0, 1) case, note that |a_i - a_i+1|
 * is equivalent to (a_i + a_i+1) % 2, because of the
 * parities. So for each top row element, you can
 * deduce the contribution.
 * 
 * To do the contribution stuff, I think it's kind of like
 * Pascal's triangle? Yeah, it's (n - 1, choose i). Reasoning
 * is that, you will proceed down n - 1 layers, and will eventually
 * move i spots (within the Pascal triangle).
*/
/**
  * 1. Can a graph be constructed?
  * 2. How can we reuse information?
  * 3. Monotonicity? Concavity? Anything else?
  * 4. Prove/justify any observations.
  * 5. If there are 1e9+7 edge cases and it's
  *    impossible to implement, maybe it's not right.
  * 6. For math formulas, try rewriting them.
  * 7. Break down the problem, or maybe reframe it.
  * 8. Loop through common techniques... binary search?
  *    DP? DFS/BFS/Graphs? 
  * 9. If your idea is almost certainly right, try some
  *    optimization techniques. Small to large merging?
  *    Deleting unnecessary stuff? Using a set? IDK.
*/