#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    string s; cin >> s;
    string b = "bessie";
    int n = s.length();
    ll res = 0;
    vector<ll> states(7);
    for (int i = 0; i < n; i++) {
        states[0]++;
        for (int j = 5; j >= 0; j--) {
            if (s[i] == b[j]) {
                states[j + 1] += states[j];
                states[j] = 0;
            }
        }
        res += states[6] * (n - i);
        states[0] += states[6];
        states[6] = 0;
    }
    cout << res << '\n';
}
/*
An optimized approach of the O(N^2) solution
of fixing a character and greedily
calculating b(s) for all prefixes
of all suffixes of s.

Instead of manually calculating each one, we can
store groups of strings that need a character i.
We iterate through the string s, and progress
the counter if the current character is equal to the character needed.
Once a group of strings has progressed to having a finished
"bessie" string, we multiply the # of strings by the #
of characters left to process. In order to properly
calculate B(s) for strings that may have a B(s) more than 1,
we add the strings processed to the "waiting" group so it will 
get added if there are more "bessies".
*/