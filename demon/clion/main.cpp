#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 200500;
const long long PHI = (long long) 998244352;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x1f3f3f3f3f3f3f3f;
const long long MOD = (long long) 1e9 + 7;
const long long OVER_FLOW = 0xffffffff;

long long n, k, m;

//******************************
//返回d=gcd(a,b); 和对应于等式ax+by=d 中的x,y
long long extend_gcd(long long a, long long b, long long &x, long long &y) {
    if (a == 0 && b == 0) return -1;//无最大公约数
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long d = extend_gcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

//********* 求逆元*******************
//ax = 1(mod n)
long long inv(long long a, long long n) {
    long long x, y;
    long long d = extend_gcd(a, n, x, y);
    if (d == 1) return (x % n + n) % n;
    else return -1;
}

long long f[10050][65];

long long solve(long long x, long long cnt) {
    for (long long i = 0; i <= k; i++) for (long long j = 0; j <= cnt; j++) f[i][j] = 0;
//    memset(f,0,sizeof f);

    f[0][cnt] = 1;
    for (long long i = 0; i < k; i++) {
        for (long long j = 0; j <= cnt; j++) {
            if (f[i][j]) {
                long long cur_inv = inv(j + 1, MOD);
                assert(cur_inv != -1);

                for (long long o = 0; o <= j; o++) {
                    f[i + 1][o] = (f[i + 1][o] + f[i][j] * inv(j + 1, MOD) % MOD) % MOD;
                }
            }
        }
    }

    long long cur = 0, mul = 1;
    for (long long i = 0; i <= cnt; i++) {
        cur = (cur + f[k][i] * mul % MOD) % MOD;
        mul = mul * x % MOD;
    }

    return cur;
}

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
    1.数学公式尝试化简
    2.数量值太大尝试给出递推公式
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
    cin >> n >> k;
    long long res = 1, raw = n;
    for (long long i = 2; i * i <= raw; i++) {
        if (n % i == 0) {
            long long cnt = 0;
            while (n % i == 0) {
                n /= i;
                cnt++;
            }
            res = res * solve(i, cnt) % MOD;
        }
    }
    if (n != 1) res = res * solve(n, 1) % MOD;

    cout << res << endl;


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}