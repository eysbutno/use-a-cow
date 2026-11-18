#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main() { // O(n) possible
    ifstream fin ("div7.in");
    ofstream fout ("div7.out");
    long long n; fin >> n;
    vector<long long> vals(n + 1);
    vector<long long> prefix(n + 1);
    for (long long i = 1; i <= n; i++) {
        fin >> vals[i];
        prefix[i] = prefix[i - 1] + vals[i];
    }
    long long ans = 0;
    for (long long i = 0; i <= n; i++) {
        for (long long j = i + 1; j <= n; j++) {
            if ((prefix[j] - prefix[i]) % 7 == 0) ans = max(ans, j - i);
        }
    }
    fout << ans << endl;
}