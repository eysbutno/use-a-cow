#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
int main() {
    int n, d, m; cin >> n >> d >> m;
    vector<pair<int, int>> reqs(m);
    for (int i = 0; i < m; i++) {
        cin >> reqs[i].f;
        reqs[i].s = i + 1;
    }
    sort(begin(reqs), end(reqs));
    auto check = [&](int mid) {
        int num = 0;
        for (int i = 1; i <= n; i++) { // day
            for (int j = 0; j < mid; j++) { // adding
                if (i - reqs[num].f > d) return false;
                if (reqs[num].f > i) break;
                num++;
                if (num == m) return true;
            }
        }
        return false;
    };
    int low = 1, high = m;
    while (low < high) {
        int mid = (low + high) / 2;
        if (check(mid)) high = mid;
        else low = mid + 1;
    }
    cout << low << "\n";
    int num = 0;
    for (int i = 1; i <= n; i++) { // day
        bool added = false;
        for (int j = 0; j < low; j++) { // adding
            if (num == m) break;
            if (i - reqs[num].f > d) return false;
            if (reqs[num].f > i) break;
            cout << reqs[num].s << " ";
            num++;
        }
        cout << 0 << "\n";
    }
}