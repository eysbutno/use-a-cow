#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define f first 
#define s second

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n; cin >> n;
    vector<string> a(n);
    for (auto& i : a) cin >> i;
    sort(begin(a), end(a), [&]
        (string& x, string& y) {
        return (x + y) < (y + x);
    });
    for (string i : a) {
        cout << i;
    }
    cout << '\n';
}
/*
Okay the comparator was actually
SO SO SO SO SO MUCH simpler than I thought
it would be. I came up with some hocus pocus
that probably wasn't even algorithmically correct.

The comparator is just to combine the two in two
different orders and see if that works. Because if
you think about the problem substructure, that is
indeed the actual way to do it.
*/