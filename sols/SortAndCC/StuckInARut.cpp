#include <bits/stdc++.h>
using namespace std;

struct Cow {int xCoord, yCoord, id;};
bool eastCmp(Cow a, Cow b) {return a.yCoord < b.yCoord;}
bool northCmp(Cow a, Cow b) {return a.xCoord < b.xCoord;}
int main() {
    int n; cin >> n;
    vector<Cow> eastCows; vector<Cow> northCows;
    for (int i = 1; i <= n; i++) {
        char dir; int x; int y; cin >> dir >> x >> y;
        Cow c; c.xCoord = x; c.yCoord = y; c.id = i;
        if (dir == 'E') eastCows.push_back(c);
        else northCows.push_back(c);
    }
    sort(eastCows.begin(), eastCows.end(), eastCmp);
    sort(northCows.begin(), northCows.end(), northCmp);
    vector<bool> stuck(n + 1); vector<int> dist(n + 1); vector<int> stopped(n + 1);
    for (Cow i : eastCows) {
        for (Cow j : northCows) {
            if (!stuck[i.id] && !stuck[j.id] && i.xCoord < j.xCoord && i.yCoord > j.yCoord) {
                if (j.xCoord - i.xCoord > i.yCoord - j.yCoord) {
                    stuck[i.id] = true; stopped[j.id] += 1 + stopped[i.id];
                } else if (j.xCoord - i.xCoord < i.yCoord - j.yCoord) {
                    stuck[j.id] = true; stopped[i.id] += 1 + stopped[j.id];
                }
            } 
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << stopped[i] << "\n";
    }
}
/*
Same idea as Bronze Stuck In A Rut
In order to simulate trasitive collisions:
add the collisions from each cow one cow stops
(Read code)
*/