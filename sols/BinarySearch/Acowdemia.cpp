#include <bits/stdc++.h>
using namespace std;
typedef long long ll; 

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n, k, l; cin >> n >> k >> l;
    vector<int> papers(n);
    for (int& i : papers) cin >> i;
    sort(begin(papers), end(papers), greater<int>());
    int low = 0, high = n;
    auto check = [&](int mid) {
        ll sum = 0;
        for (int i = 0; i < mid; i++) {
            sum += max(mid - papers[i], 0);
        }
        return papers[mid - 1] + k >= mid 
            && (sum <= (ll) k * (ll) l);
    };
    while (low < high) {
        int mid = (low + high + 1) / 2;
        if (check(mid)) low = mid;
        else high = mid - 1;
    }
    cout << low << '\n';
}
/*
Algorithm:
Binary search the h index.
NOTE:
There are only two ways a h index
is impossible: if you cannot
get enough citations, or if 
one paper cannot cut it in n - k
citations.
*/