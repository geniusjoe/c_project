#include <bits/stdc++.h>

#define loca

#define ll long long

using namespace std;

long long T, n, m, p, d;
long long minn, MOD, res, mx_j, num;

long long eular(long long n) {
    long long ans = n;
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            ans -= ans / i;
            while (n % i == 0)
                n /= i;
        }
    }
    if (n > 1) ans -= ans / n;
    return ans;
}

ll qmul(ll x, ll y, ll m)
{
    ll res = 0;
    while(y)
    {
        if(y & 1) res = (res + x) % m;
        x = (x + x) % m;
        y >>= 1;
    }
    return res;
}


long long pow_m(long long a, long long _n) {
    long long ret = 1;
    long long tmp = a % MOD;
    while (_n) {
//        if (_n & 1) ret = (ret * tmp) % MOD;
//        tmp = tmp * tmp % MOD;
        if (_n & 1) ret =qmul(ret,tmp,MOD);
        tmp = qmul(tmp,tmp,MOD);
        _n >>= 1;
    }
    return ret;
}

long long quick_pow(long long a, long long _n) {
    long long ret = 1;
    long long tmp = a;
    while (_n) {
        if (_n & 1) ret = ret * tmp ;
        tmp = tmp * tmp;
        _n >>= 1;
    }
    return ret;
}

const long long MAXN = 100100;
long long prime[MAXN + 1];

void getPrime() {
    memset(prime, 0, sizeof(prime));
    for (long long i = 2; i <= MAXN; i++) {
        if (!prime[i]) prime[++prime[0]] = i;
        for (long long j = 1; j <= prime[0] && prime[j] <= MAXN / i; j++) {
            prime[prime[j] * i] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}



ll qpow(ll a, ll n, ll m)
{
    ll res = 1;
    while(n)
    {
        if(n & 1) res = qmul(res, a, m) % m;
        a = qmul(a, a, m) % m, n >>= 1;
    }
    return res;
}



long long factor[100][2];
long long fatCnt;

long long getFactors(long long x) {
    mx_j = fatCnt = 0;
    long long tmp = x;
    for (long long i = 1; prime[i] <= tmp / prime[i]; i++) {
        factor[fatCnt][1] = 0;
        if (tmp % prime[i] == 0) {
            factor[fatCnt][0] = prime[i];
            while (tmp % prime[i] == 0) {
                factor[fatCnt][1]++;
                tmp /= prime[i];
            }
            fatCnt++;
        }
    }
    if (tmp != 1) {
        factor[fatCnt][0] = tmp;
        factor[fatCnt++][1] = 1;
    }

    for (long long i = 0; i < fatCnt; i++)
        mx_j = max(mx_j, factor[i][1]);

    return fatCnt;
}


ll pri[105], fac[105];
void uniqueDecompose(ll x)//唯一分解，pri为对应质数，fac为对应次数
{
    num = 0;//唯一分解后的质数个数
    for(int j = 2; j*j <= x; j++)
        if(x % j == 0)
        {
            pri[++num] = j, fac[num] = 0;
            while(x % j == 0) fac[num]++, x /= j;
        }
    if(x > 1) pri[++num] = x, fac[num] = 1;
}


int main() {
//    ios::sync_with_stdio(false);

#ifdef  local
    freopen("testdata.in","r+",stdin);
    freopen("testdata.out","w+",stdout);
#endif

    getPrime();

    cin >> T;
    while (T--) {
        cin >> p >> n >> m;
        res = 0;
        if (p == 2 || p == 5) {
            cout << 0 << endl;
            continue;
        }

        MOD = 9 * p;
//        if (p == 3) d = 18;
//        else d = (p - 1) * 6;
        long long phi = eular(MOD);

        d = 1e18;
        for (long long i = 1; i * i <= phi; i++) {
            if (phi % i == 0) {
                ll fac1 = i, fac2 = phi / i;

                if (pow_m(10, i)  == 1)
                    d = min(d, i);
                if (pow_m(10, phi / i) == 1)
                    d = min(d, phi / i);

//                if(qpow(10, i, MOD) == 1) d = min(d, i);
//                if(qpow(10, phi/i, MOD) == 1) d = min(d, phi/i);
            }
        }

        getFactors(d);


        long long tmp = 1;
        for (long long i = 1; i <= min(m, 30ll); i++) {
            tmp = 1;
            for (long long j = 0; j <fatCnt; j++) {
                tmp *= pow_m(factor[j][0], ceil(1.0*factor[j][1]/i));
            }
            res += n / tmp;
        }
        if (m > 30ll) res += (m - 30) * (n / tmp);

        cout << res << endl;

    }
    return 0;
}