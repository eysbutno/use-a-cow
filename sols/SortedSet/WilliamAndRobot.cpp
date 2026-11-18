#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define f first 
#define s second 

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n; cin >> n;
    vector<int> a(n);
    for (int& i : a) {
        cin >> i;
    }
    priority_queue<int> pq;
    for (int i = 0; i < n; i += 2) {
        pq.push(-max(a[i], a[i + 1]));
        if (-pq.top() < min(a[i], a[i + 1])) {
            pq.pop(); pq.push(-min(a[i], a[i + 1]));
        }
    }
    ll res = 0;
    while (!pq.empty()) {
        res -= pq.top();
        pq.pop();
    }
    cout << res << '\n';
}
/*
Idea is that for each k,
k <= n, William can only
select the k / 2 greatest
integers at a time. So just
do that for every value of k
until you get k = n.

(Still gotta figure out why
my original sol gets WA)
*/