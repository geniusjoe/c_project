#include<bits/stdc++.h>

#define loca
#define debu
using namespace std;

const int MAXN = 500005;
const int INF = 0x3f3f3f3f;

char s[105], t[105], p[105];
int hsh1[26 + 5], hsh2[26 + 5];

long long n, m, T, k;

int main() {

#ifdef local
    freopen("testdata.in", "r+", stdin);
    freopen("testdata.out", "w+", stdout);
#endif // local

    //ios::sync_with_stdio(false);

    cin >> n >> m >> k;
    if (n % 2 == 0) {
        cout << "Marsel" << endl;
        return 0;
    }
    bool flag = false;
    for (int i = 1; i * i <= m; i++) {
        if (m % i == 0) {
            if (m / i >= k && i > 1) {
                flag = true;
                break;
            } else if (i >= k && m / i > 1) {
                flag = true;
                break;
            }
        }
    }
    if (flag)
        cout << "Timur" << endl;
    else
        cout << "Marsel" << endl;


    return 0;
}