#include <bits/stdc++.h>

#define loc
const int INF = 0x3f3f3f3f;
using namespace std;
const long long MAXN = 1e5 + 5;

long long n, p, k, res = 0;
long long buf[MAXN + 5];

// x * y % m
long long qmul(long long x, long long y, long long m) {
    long long res = 0;
    while (y) {
        if (y & 1) res = (res + x) % m;
        x = (x + x) % m;
        y >>= 1;
    }
    return res;
}

// a ^ n % m
long long qpow(long long a, long long n, long long m) {
    long long res = 1;
    while (n) {
        if (n & 1) res = qmul(res, a, m) % m;
        a = qmul(a, a, m) % m, n >>= 1;
    }
    return res;
}

map<int, int> mp;

int main() {
    ios::sync_with_stdio(false);

#ifdef local
    freopen("testdata.in", "r+", stdin);
    freopen("testdata.out", "w+", stdout);
#endif // local

    cin >> n >> p >> k;
    for (int i = 1; i <= n; i++) {
        long long cur;
        cin >> cur;
        cur = (qpow(cur, 4ll, p) - k * cur % p) % p;
        cur = (cur + p) % p;
        res += mp[cur];
        mp[cur]++;
    }
    cout << res << endl;
}