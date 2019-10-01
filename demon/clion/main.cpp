#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 100500;
const long long PHI = (long long) 1e9 + 6;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x1f3f3f3f3f3f3f3f;
const long long MOD = (long long) 1e9 + 7;
const long long OVER_FLOW = 0xffffffff;

long long n;

// a ^ b % c
long long qpow(long long a, long long b, long long c) {
    long long cur = 1;
    while (b) {
        if (b & 1) cur = cur * a % c;
        a = a * a % c, b >>= 1;
    }
    return cur;
}

long long inv(long long num, long long m) {
    return qpow(num, m - 2, m);
}

const long long N = 100100;
long long lst[N]; //如果数字是合数,为其除去本身最大的因数
vector<long long> prm_factor[N], factor[N];
long long num[N]; //如果数字是质数,求出质数的序号
long long rnum[N]; //第几个质数

void sieve() {
    for (long long i = 1; i < N; i++) factor[i].push_back(1);
    for (long long i = 1; i < N; i++) lst[i] = i;
    for (long long i = 2; i < N; ++i) {
        for (long long j = 2; i * j < N; j++) factor[i * j].push_back(i);
        if (lst[i] != i) {
            lst[i] = i / lst[i];
            continue;
        }
        for (long long j = i; j < N; j += i) {
            lst[j] = min(lst[j], i);
            prm_factor[j].push_back(i);
        }
    }
    long long cur = 0;
    for (long long i = 2; i < N; ++i)
        if (lst[i] == i) {
            num[i] = ++cur;
            rnum[cur] = i;
        }
}

//1-b中有多少个数与a互质
long long coprime(long long a, long long b) {
    long long ret = b;
    vector<long long> buf;
    for (long long &it : prm_factor[a]) buf.push_back(it);
    long long len = buf.size();
    for (long long i = 1; i < 1 << len; i++) {
        long long tmp = 1;
        for (long long j = 0; j < len; j++) {
            if ((i >> j) & 1) {
                tmp = -tmp * buf[j];
            }
        }
        ret += b / tmp;
    }
    return ret;
}

long long f[MAXN];

int main() {

#ifndef ONLINE_JUDGE
    freopen("testdata.in", "r+", stdin);
    freopen("testdata.out", "w+", stdout);
#endif // ONLINE_JUDGE

#ifndef ONLINE_JUDGE
    auto start_time = clock();
    cerr << setprecision(3) << fixed;
#endif

/*
写代码时请注意：
    1.是否要开Long Long？数组边界处理好了么？
    2.实数精度
    3.下标能从最小值开始就从最小值开始
    5.排序之前不能取模.
    6.0-1子矩阵子序列:前缀和,异或和
    7.模拟题注意代码复用.
    8.单个区间问题考虑前缀和,多个区间左右端点拆开,排序,记录端点极值
思考提醒：
    1.最大值和最小值问题可不可以用二分+贪心？
    2.dp
    3.如果规模小的话还能尝试dfs
    4.如果存在等式.转换关系少可以暴力枚举变量,或者考虑从数据大小入手
    5.离散化+打表
*/

    ios::sync_with_stdio(false);
    sieve();
    long long m;
    cin >> m;
    f[1] = 1;
    for (long long i = 2; i <= m; i++) {
        f[i] = 1;
        for (auto it:factor[i]) {
            f[i] += f[it] * coprime(i / it, m / it) % MOD * inv(m, MOD) % MOD;
            f[i] %= MOD;
        }
        f[i] = inv((1ll + MOD - m / i % MOD * inv(m, MOD) % MOD) % MOD, MOD)
               * f[i] % MOD;
    }

    long long res = 0;
    for (long long i = 1; i <= m; i++) {
        res += f[i];
        res %= MOD;
    }
    res = res * inv(m, MOD) % MOD;
    cout << res << endl;

#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}