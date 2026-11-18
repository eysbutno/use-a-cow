#include <bits/stdc++.h>
using namespace std;

int n, m, c; vector<int> times;
bool check(int dif) {
    int busCount = 0; int space = 0; int prev = -1;
    for (int i : times) {
        if (abs(prev - i) > dif || space == 0) {
            busCount++; space = c - 1; prev = i;
        } else {
            space--;
        }
    }
    return busCount <= m;
}
int main() {
    ifstream fin ("convention.in");
    ofstream fout ("convention.out");
    fin >> n >> m >> c;
    int l = 2000000000; int h = -1;
    for (int i = 0; i < n; i++) {
        int a; fin >> a; times.push_back(a);
        l = min(l, a); h = max(h, a);
    }
    sort(begin(times), end(times));
    int low = 0, high = h;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (check(mid)) high = mid;
        else low = mid + 1;
    }
    fout << low << endl;
    return 0;
}
/*
Type: Binary Search
Algorithm:
Binary search the largest difference possible
How to simulate:
Add every cow that can fit within the given dif
Returns true if you satisfy the condition, false if you can't
*/