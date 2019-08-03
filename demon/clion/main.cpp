#include<bits/stdc++.h>

#define loca
#define debu
using namespace std;

const int MAXN = 100005;
const int INF = 0x3f3f3f3f;
const long long MOD = 998244353;
long long n, res, mx_len;
map<long long, long long> mp1, mp2;

// a ^ n % m
long long qpow(long long a, long long b, long long m) {
    long long res = 1;
    while (b) {
        if (b & 1) res = res * a % m;
        a = a * a % m, b >>= 1;
    }
    return res;
}

void get_num(long long raw) {
    long long ret = 0, i = 1;
    while (raw) {
        long long cur = raw % 10;
        mp2[i] += cur;
        i++;
        raw /= 10;
    }
}

long long get_len(long long raw) {
    long long len = 0;
    while (raw) {
        raw /= 10;
        len++;
    }
    mx_len = max(len, mx_len);
    return len;
}

int main() {

#ifdef local
    freopen("testdata.in", "r+", stdn);
    freopen("testdata.out", "w+", stdout);
#endif // local

    ios::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        long long cur;
        cin >> cur;
        mp1[get_len(cur)]++;
        get_num(cur);
    }
    long long cur_nm = 0;
    for (int i = mx_len; i >= 1; i--) {
        cur_nm += mp1[i];
        res += qpow(10, 2 * (i - 1), MOD) * 11ll % MOD * cur_nm % MOD * mp2[i] % MOD;
        for (int j = i - 1; j >= 1; j--) {
            res += qpow(10, j + i - 1, MOD) * 2ll % MOD * mp1[j] % MOD * mp2[i] % MOD;
        }
        res %= MOD;
    }
    cout << res << endl;

    return 0;
}