#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin ("bcount.in");
    ofstream fout ("bcount.out");
    int n, q; fin >> n >> q;
    vector<int> h(n + 1); vector<int> g(n + 1); vector<int> j(n + 1);
    vector<int> ph(n + 1); vector<int> pg(n + 1); vector<int> pj(n + 1);
    for (int i = 1; i <= n; i++) {
        int a; fin >> a;
        if (a == 1) h[i]++;
        else if (a == 2) g[i]++;
        else j[i]++;
    }
    for (int i = 1; i <= n; i++) {
        ph[i] = ph[i - 1] + h[i]; pg[i] = pg[i - 1] + g[i]; pj[i] = pj[i - 1] + j[i];
    }
    for (int i = 0; i < q; i++) {
        int a, b; fin >> a >> b;
        fout << ph[b] - ph[a - 1] << " " << pg[b] - pg[a - 1] << " " << pj[b] - pj[a - 1] << endl;
    }
    return 0;
}