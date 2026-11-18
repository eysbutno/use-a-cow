#include <bits/stdc++.h>
using namespace std;

vector<int> cows; int n, t;
bool check(int k) {
    priority_queue<int> stage; int time = 0;
    for (int i : cows) {
        if (stage.size() == k) {
            time = -stage.top();
            stage.pop();
        }
        if (time + i > t) return false;
        stage.push(-(time + i));
    }
    return true;
}
int main() {
    ifstream fin ("cowdance.in");
    ofstream fout ("cowdance.out");
    fin >> n >> t; cows.resize(n);
    for (int i = 0; i < n; i++) {
        fin >> cows[i];
    }
    int low = 1, high = n;
    while (low < high) { // finding lowest true
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
Binary search the size of the stage
Uses a priority queue to simulate a stage
*/