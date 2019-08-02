#include<bits/stdc++.h>

#define loca
#define debu
using namespace std;

const int MAXN = 500010;

long long buf[MAXN];
map<int, int> mp;

long long n, m, pg;

int main() {

#ifdef local
    freopen("testdata.in", "r+", stdin);
    freopen("testdata.out", "w+", stdout);
#endif // local

    //ios::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> buf[i];
        mp[buf[i]]++;
    }

    bool win = true;
    if (mp[0] >= 2) win = false;
    for (auto it:mp) {
        if (it.second >= 3) win = false;
    }
    int cnt = 0;
    for (auto it:mp) {
        if (it.second >= 2) cnt++;
    }
    if (cnt >= 2) win = false;

    for (auto it:mp) {
        if (it.second >= 2 && mp[it.first - 1] >= 1) {
            win = false;
            break;
        }
    }
    if (!win) {
        cout << "cslnb" << endl;
        return 0;
    }
    long long sm = 0;
    for (int i = 1; i <= n; i++) sm += buf[i];
    if ((sm - n * (n - 1) / 2) % 2 == 1)
        cout << "sjfnb" << endl;
    else
        cout << "cslnb" << endl;
    return 0;

}