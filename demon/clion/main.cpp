#include<bits/stdc++.h>

#define loca
#define debu
using namespace std;

const int MAXN = 500010;

long long buf[MAXN];

long long n, m, pg;

template<class T>
inline bool scan_d(T &ret) {
    char c;
    int sgn;
    if (c = getchar(), c == EOF)
        return 0;
    while (c != '-' && (c < '0' || c > '9'))
        c = getchar();
    sgn = (c == '-') ? -1 : 1;
    ret = (c == '-') ? 0 : (c - '0');
    while (c = getchar(), c >= '0' && c <= '9')
        ret = ret * 10 + (c - '0');
    ret *= sgn;
    return 1;
}

int main() {

#ifdef local
    freopen("testdata.in", "r+", stdin);
    freopen("testdata.out", "w+", stdout);
#endif // local

    //ios::sync_with_stdio(false);

    scan_d(n), scan_d(m), scan_d(pg);

    for (long long i = 1; i <= m; i++)
        scan_d(buf[i]);

    long long sum = 0, t = 1, r = 0, res = 0;
    while (t <= m) {
        r = (buf[t] - sum + pg - 1) / pg * pg + sum;
        while (t <= m && buf[t] <= r) {
            t++;
            sum++;
        }
        res++;
    }
    cout << res << endl;
    return 0;
}