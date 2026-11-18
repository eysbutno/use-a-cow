#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define f first 
#define s second 

const int MAX = 5e6 + 5;
map<int, set<int>> primes;
void solve() {
    int n; cin >> n;
    int earliest = INT_MAX, game = INT_MAX;
    for (int i = 0; i < n; i++) {
        int res = 0, val; cin >> val;
        if (val % 4) { 
            // FJ winning
            res = (val - *(--primes[val % 4].
                upper_bound(val))) / 2 + 1;
        } else {
            // FN winning
            res = val / 2;
        }
        if (res / 2 < game) {
            earliest = res, game = res / 2;
        }
    }
    cout << ((earliest % 2) ? "Farmer John" 
        : "Farmer Nhoj") << '\n';
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    vector<bool> comp(MAX + 1);
    for (int i = 2; i <= MAX; i++) {
        if (comp[i]) continue;
        for (int j = 2; i * j <= MAX; j++) {
            comp[i * j] = true;
        }
    }
    for (int i = 1; i < MAX; i++) {
        if (!comp[i]) primes[i % 4].insert(i);
    }
    int t; cin >> t; 
    while (t--) solve();
    return 0;
}
/*
BIGGEST OBSERVATION:
If a given farmer has a number,
which is equivalent to 0 (mod 4),
that farmer will lose. 4 is special
because no matter what prime numbers
you pick, it always becomes zero with
2 removals of cows (when played optimally).

Whoever's guaranteed to win wants the game to
end as fast as possible, with the inverse being
true for whoever will lose. If FJ is winning,
he wants to get the largest prime number which
will result in Nhoj's count being equiv. to 0 (mod 4).
For any number that's even, it will take n / 2 moves
for any given position.
*/