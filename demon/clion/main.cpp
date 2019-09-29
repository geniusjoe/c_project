#include<bits/stdc++.h>

using namespace std;

//const long long MAXN = 500500;
const long long PHI = (long long) 1e9 + 6;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x1f3f3f3f3f3f3f3f;
const long long MOD = (long long) 1e6 + 3;
const long long OVER_FLOW = 0xffffffff;

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

#define eps 1e-9
const int MAXN = 220;
long long a[MAXN][MAXN], x[MAXN];//方程的左边的矩阵和等式右边的值, 求解之后x存的就是结果
int equ, var;//方程数和未知数个数
/*
* 返回0 表示无解,1 表示有解
*/
int Gauss() {
    int i, j, k, col, max_r;
    for (k = 0, col = 0; k < equ && col < var; k++, col++) {
        max_r = k;
        for (i = k + 1; i < equ; i++)
            if (abs(a[i][col]) > abs(a[max_r][col]))
                max_r = i;
        if (abs(a[max_r][col]) == 0)
            return 0;
        if (k != max_r) {
            for (j = col; j < var; j++)
                swap(a[k][j], a[max_r][j]);
            swap(x[k], x[max_r]);
        }
        x[k] = x[k] * inv(a[k][col], MOD) % MOD;
        for (j = col + 1; j < var; j++)a[k][j] = a[k][j] * inv(a[k][col], MOD) % MOD;
        a[k][col] = 1;
        for (i = 0; i < equ; i++)
            if (i != k) {
                x[i] = (x[i] - (x[k] * a[i][col] % MOD) + MOD) % MOD;
                for (j = col + 1; j < var; j++)a[i][j] = (a[i][j] - (a[k][j] * a[i][col] % MOD) + MOD) % MOD;
                a[i][col] = 0;
            }
    }
    return 1;
}

long long get(long long p) {
    cout << "? " << p << '\n';
    cout.flush();
    long long cur;
    cin >> cur;
    return cur;
}

long long cur[15];

bool ok(long long p) {
    long long res = 0;
    cur[0] = 1;
    for (long long i = 1; i <= 10; i++) {
        if (i == 1) cur[i] = p % MOD;
        else cur[i] = cur[i - 1] * p;
        cur[i] %= MOD;
    }
    for (long long i = 0; i <= 10; i++) {
        res += x[i] * cur[i] % MOD;
        res %= MOD;
    }
    return res == 0;
}

int main() {

#ifndef ONLINE_JUDGE
//    freopen("testdata.in", "r+", stdin);
//    freopen("testdata.out", "w+", stdout);
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
    equ = var = 11;
    a[0][0] = 1;
    for (long long i = 1; i <= 10; i++) {
        long long cnt = i;
        a[i][0] = 1;
        for (long long j = 1; j <= 10; j++) {
            a[i][j] = cnt;
            cnt *= i;
            cnt %= MOD;
        }
    }
    for (long long i = 0; i <= 10; i++) {
        long long cur = get(i);
        x[i] = cur;
    }

    Gauss();
    bool flg = false;
    for (long long i = 0; i <= (long long) 1e6 + 3; i++) {
        if (ok(i)) {
            cout << "! " << i << '\n';
            flg = true;
            break;
        }
    }
    if (!flg) {
        cout << "! " << -1 << '\n';
    }

#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}