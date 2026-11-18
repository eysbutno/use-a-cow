#include <bits/stdc++.h>
using namespace std;

bool cmp(int a, int b) {return a > b;}
int main() {
    ifstream fin ("lemonade.in");
    ofstream fout ("lemonade.out");
    int n; fin >> n; vector<int> cows(n);
    for (int i = 0; i < n; i++) fin >> cows[i];
    sort(begin(cows), end(cows), cmp);
    int count = 0;
    for (int i : cows) {
        if (i < count) break;
        count++;
    }
    fout << count << endl;
    return 0;
}
/*
Type: Sorting
Algorithm:
Just reverse it to make the cows
who don't wanna wait long go last so they leave
*/