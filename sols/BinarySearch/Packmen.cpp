#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define f first 
#define s second 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n; cin >> n;
    string s; cin >> s;
    vector<int> ast, pac;
    for (int i = 0; i < n; i++) {
        if (s[i] == '*') ast.push_back(i);
        if (s[i] == 'P') pac.push_back(i);
    }
    auto check = [&](int mid) {
        queue<int> active;
        for (int i : ast) {
            active.push(i);
        }
        for (int i : pac) {
            if (active.empty()) break;
            int f = active.front();
            if (i - f > mid) break;
            while (!active.empty() && active.front() < i) {
                active.pop();
            }
            int t1 = i - f, t2 = t1 * 2;
            if (f > i) t1 = 0, t2 = 0;
            while (!active.empty() && t1 + 2 * 
                (active.front() - i) <= mid) {
                active.pop();
            }
            while (!active.empty() && t2 + 
                active.front() - i <= mid) {
                active.pop();
            }
        }
        return active.size() == 0;
    };
    int low = 0, high = 3e5;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (check(mid)) high = mid;
        else low = mid + 1;
    }
    cout << low << '\n';
}
/*
Wow... I need to do more
binary search practice!

Algorithm:
Binary search the value z.
For each pacman, figure out
the most asteriks it can eat
while still eating the leftmost
uneaten subarray.
*/