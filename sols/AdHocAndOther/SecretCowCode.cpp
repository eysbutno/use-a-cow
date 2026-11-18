#include <bits/stdc++.h>
using namespace std;
#define ll long long

int solve(ll n, ll idx) {
    if (idx < n) return idx;
    ll power = n;
    while (power * 2 <= idx) power *= 2;
    ll mapped = idx - power;
    if (mapped > 0) {
        return solve(n, mapped - 1);
    }
    return solve(n, power - 1);
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    freopen("cowcode.in", "r", stdin);
    freopen("cowcode.out", "w", stdout);
    string s; ll n;
    cin >> s >> n;
    cout << s[solve(s.length(), --n)];
}