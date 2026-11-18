#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
	cin.tie(NULL);
    int x, n; cin >> x >> n;
    set<int> pts = {0, x};
    multiset<int> gaps = {x};
    while (n--) {
        int l; cin >> l;
        auto it = pts.upper_bound(l);
        auto it2 = it; --it2;
        gaps.erase(gaps.find(*it - *it2));
        gaps.insert(*it - l); 
        gaps.insert(l - *it2);
        pts.insert(l);
        auto ans = end(gaps); ans--;
        cout << *ans << " ";
    }
}