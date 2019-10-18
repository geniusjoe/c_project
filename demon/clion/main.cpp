#include<bits/stdc++.h>

//#pragma GCC optimize(2)

using namespace std;

const long long MAXN = 2005000;
const long long PHI = (long long) 998244352;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x3f3f3f3f3f3f3f3f;
const long long MOD = (long long) 998244353;
const long long OVER_FLOW = 0x7fffffff;
const long long LOVER_FLOW = 0x7fffffffffffffff;

long long n;

struct point {
    long long x, y, c, f;

    bool operator<(point point1) {
        return this->c < point1.c;
    }
} points[MAXN];

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


void add(long long &x, long long y, long long mod) {  //手动取模
    x += y;
    while (x < 0) x += mod;
    while (x >= mod) x -= mod;
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
    2.dp或者数值太大,尝试给出递推公式
    3.概率题随机生成考虑1/2的情况,或者是满足的方案/所有可能的方案
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
    long long m, tarx, tary;
    cin >> n >> m;
    for (long long i = 1; i <= n; i++) {
        for (long long j = 1; j <= m; j++) {
            long long u;
            cin >> u;
            points[(i - 1) * m + j] = {i, j, u};
        }
    }
    cin >> tarx >> tary;

    sort(points + 1, points + 1 + n * m);

    long long s, sf, sx, sx2, sy, sy2;
    s = sf = sx = sx2 = sy = sy2 = 0;
    points[n * m + 1].c = -1;
    for (long long i = 1; i <= n * m; i++) {
        long long fi = 0;
        if (s) {
            add(fi, sf, MOD);
            add(fi, s * points[i].x % MOD * points[i].x % MOD, MOD);
            add(fi, -2ll * points[i].x % MOD * sx % MOD, MOD);
            add(fi, sx2, MOD);
            add(fi, s * points[i].y % MOD * points[i].y % MOD, MOD);
            add(fi, -2ll * points[i].y % MOD * sy % MOD, MOD);
            add(fi, sy2, MOD);
            fi = fi * inv(s, MOD) % MOD;
            points[i].f = fi;
        }
        if (points[i].x == tarx and points[i].y == tary) {
            cout << fi << endl;
        }
        if (points[i].c != points[i + 1].c) {
            for (long long j = i; j >= 1; j--) {
                if (points[j].c != points[i].c) break;
                add(sf, points[j].f, MOD);
                add(s, 1, MOD);
                add(sx, points[j].x, MOD);
                add(sx2, points[j].x * points[j].x % MOD, MOD);
                add(sy, points[j].y, MOD);
                add(sy2, points[j].y * points[j].y % MOD, MOD);
            }
        }
    }

#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}