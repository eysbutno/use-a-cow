#include <bits/stdc++.h>
using namespace std;
int n, k; vector<int> locs;
bool works(int r) {
    int count = 0; int prev = -1000000000;
    for (int i : locs) {
        if (abs(prev - i) > r) {
            count++; prev = i + r;
        }
    }
    return count <= k;
}
int main() {
    ifstream fin ("angry.in");
    ofstream fout ("angry.out");
    fin >> n >> k; locs.resize(n);
    for (int i = 0; i < n; i++) {
        fin >> locs[i];
    }
    sort(begin(locs), end(locs));
    int low = 0, high = (locs[n - 1] - locs[0] + 1) / 2;
    while (low < high) { // finding lowest true
        int mid = low + (high - low) / 2;
        if (works(mid)) high = mid;
        else low = mid + 1;
    }
    fout << low << endl;
    return 0;
}
/*
Type: Binary Search
Algorithm:
Binary search the value of r
To properly simulate explosions, just 
simulate chains of explosions (where you fire a haybale
does not matter, because of how the problem works)
*/