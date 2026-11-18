#include <bits/stdc++.h>
using namespace std;

void setIO(string name = "") {
    ios_base::sync_with_stdio(0), cin.tie(0);
    if (name.size()) {
       freopen((name + ".in").c_str(), "r", stdin);
       freopen((name + ".out").c_str(), "w", stdout);
    }
}
int main() {
    setIO();
    string a, b; int n;
    cin >> a >> b >> n;
    vector<int> t1(18), t2(18);
    string alph = "abcdefghijklmnopqr";
    for (char i : alph) {
        for (char j : a) {
            if (j == i) t1[i - 'a']++;
        }
        for (char j : b) {
            if (j == i) t2[i - 'a']++;
        }
    }
    bool works[18][18];
    for (char i : alph) {
        for (char j : alph) {
            string a1 = "", b1 = "";
            for (char k : a) {
                if (k == i || k == j) {
                    a1 += k;
                }
            }
            for (char k : b) {
                if (k == i || k == j) {
                    b1 += k;
                }
            }
            works[i - 'a'][j - 'a'] = a1 == b1;
            // precalculating pairs
        }
    }
    while (n--) {
        string subset; cin >> subset;
        int o1 = 0, o2 = 0;
        for (char i : subset) {
            o1 += t1[i - 'a'], o2 += t2[i - 'a'];
        }
        if (o1 != o2) {
            cout << 'N'; 
            continue;
        }
        bool ans = true;
        for (char i : subset) {
            if (!ans) break;
            for (char j : subset) {
                if (!ans) break;
                ans = works[i - 'a'][j - 'a'];
            }
        }
        if (ans) cout << 'Y';
        else cout << 'N';
    }
}
/*
Type: Ad Hoc (or Binary Search)
Algorithm:
First, record the # of occurrences of each character
in each string (this is for the one character cases)
Then, calculate whether or not a restriction would be the same
for every possible pair of restriction characters
For each test case, first check if there is an equal amount of characters 
(this is for the one character restriction and just a preventative check)
Then, check every single pair in the subset to see if that works.
*/