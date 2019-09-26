#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 200500;
const long long PHI = (long long) 1e9 + 6;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x1f3f3f3f3f3f3f3f;
const long long MOD = (long long) 1e9 + 7;
const long long OVER_FLOW = 0xffffffff;

long long n, m, q;
long long buf[MAXN];

struct Matrix {
    long long mat[7][7];
    long long row, col;

    Matrix(long long x, long long y) {
        memset(this->mat, 0, sizeof this->mat);
        this->row = x, this->col = y;
    }
};

Matrix mul_M(Matrix a, Matrix b, long long mod) {
    Matrix ret(a.row, b.col);
    for (int i = 0; i < a.row; i++)
        for (int j = 0; j < a.col; j++) {
            ret.mat[i][j] = 0;
            for (int k = 0; k < b.row; k++) {
                ret.mat[i][j] += a.mat[i][k] * b.mat[k][j] % mod;
                ret.mat[i][j] %= mod;
            }
        }
    return ret;
}

Matrix pow_M(Matrix a, long long n, long long mod) {
    Matrix ret(a.row, a.col);
    for (int i = 0; i < ret.col; i++)ret.mat[i][i] = 1;
    Matrix tmp = a;
    while (n) {
        if (n & 1)ret = mul_M(ret, tmp, mod);
        tmp = mul_M(tmp, tmp, mod);
        n >>= 1;
    }
    return ret;
}

// a ^ b % c
long long qpow(long long a, long long b, long long c) {
    long long cur = 1;
    while (b) {
        if (b & 1) cur = cur * a % c;
        a = a * a % c, b >>= 1;
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

//    ios::sync_with_stdio(false);
    long long f1, f2, f3, w;
    cin >> n >> f1 >> f2 >> f3 >> w;
    Matrix a(3, 3), b(5, 5), a1(3, 1), b1(3, 1), c1(3, 1), d1(5, 1);
    a.mat[0][0] = a.mat[0][1] = a.mat[0][2] = a.mat[1][0] = a.mat[2][1] = 1;

    a1.mat[2][0] = 1, b1.mat[1][0] = 1, c1.mat[0][0] = 1;
    a = pow_M(a, n - 3, PHI);
    a1 = mul_M(a, a1, PHI), b1 = mul_M(a, b1, PHI), c1 = mul_M(a, c1, PHI);

    b.mat[0][0] = b.mat[0][1] = b.mat[0][2] = b.mat[0][3] = b.mat[0][4] = 1;
    b.mat[1][0] = b.mat[2][1] = b.mat[3][3] = b.mat[3][4] = b.mat[4][4] = 1;
    b = pow_M(b, n - 3, PHI);
//    d1.mat[0][0] = f3, d1.mat[1][0] = f2, d1.mat[2][0] = f1, d1.mat[4][0] = 2;
    d1.mat[4][0] = 2;
    d1 = mul_M(b, d1, PHI);

    long long res = 0;
    res = qpow(w, d1.mat[0][0], MOD)
          * qpow(f1, a1.mat[0][0], MOD) % MOD
          * qpow(f2, b1.mat[0][0], MOD) % MOD
          * qpow(f3, c1.mat[0][0], MOD) % MOD;

    cout << res << endl;

#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}