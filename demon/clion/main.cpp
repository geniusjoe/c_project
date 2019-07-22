#include<bits/stdc++.h>

using namespace std;

#define loca
#define debu

const long long MOD = 1e9 + 7;

const long long maxn = 1e6;

int n;
long long buf1[maxn + 5], buf2[maxn + 5], buf3[maxn + 5];
long long res[maxn + 5];

void exgcd(const int a, const int b, int &g, int &x, int &y) {
    if (!b) g = a, x = 1, y = 0;
    else exgcd(b, a % b, g, y, x), y -= x * (a / b);
}

inline long long inv(const int num) {
    int g, x, y;
    exgcd(num, MOD, g, x, y);
    return (long long) ((x % MOD) + MOD) % MOD;
}

void init() {

    buf1[1] = 1;
    for (long long i = 2; i <= maxn; i++) {
        buf1[i] = (buf1[i - 1] + inv(i)) % MOD;
    }

    for (long long i = 1; i <= maxn; i++) {
        buf2[i] = inv(3) * buf1[i] % MOD * i % MOD * (i + 1) % MOD * (2 * i + 1) % MOD;
    }

    buf3[1] = 2;
    for (long long i = 2; i <= maxn; i++) {
        buf3[i] = (buf3[i - 1] + 2 * i * i % MOD * buf1[i] % MOD) % MOD;
    }

    for (long long i = 1; i <= maxn; i++) {
        res[i] = (buf2[i] - buf3[i] + i + MOD) % MOD * (inv(i) * inv(i) % MOD) % MOD;
    }
}

int main() {
#ifdef local
    freopen("testdata.in", "r+", stdin);
    freopen("testdata.out", "w+", stdout);
#endif

    ios::sync_with_stdio(false);

    init();

    while (scanf("%d", &n) != EOF) {
        cout << res[n] << endl;
    }


}