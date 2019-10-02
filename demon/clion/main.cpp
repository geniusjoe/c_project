#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 2000;
const long long PHI = (long long) 1e9 + 6;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x1f3f3f3f3f3f3f3f;
const long long MOD = (long long) 1e9 + 7;
const long long OVER_FLOW = 0xffffffff;

long long n;

struct Matrix {
    long long mat[150][150];

    Matrix() { memset(mat, 0, sizeof mat); }
};

Matrix mul_M(Matrix a, Matrix b, long long mod) {
    Matrix ret;
    for (int i = 0; i < 100; i++)
        for (int j = 0; j < 100; j++) {
            ret.mat[i][j] = 0;
            for (int k = 0; k < 100; k++) {
                ret.mat[i][j] += a.mat[i][k] * b.mat[k][j] % mod;
                ret.mat[i][j] %= mod;
            }
        }
    return ret;
}

Matrix pow_M(Matrix a, long long n, long long mod) {
    Matrix ret;
    memset(ret.mat, 0, sizeof(ret.mat));
    for (int i = 0; i < 100; i++)ret.mat[i][i] = 1;
    Matrix tmp = a;
    while (n) {
        if (n & 1)ret = mul_M(ret, tmp, mod);
        tmp = mul_M(tmp, tmp, mod);
        n >>= 1;
    }
    return ret;
}

long long pow_m(long long a, long long n, long long mod)//a^b % mod
{
    long long ret = 1;
    long long tmp = a % mod;
    while (n) {
        if (n & 1)
            ret = ret * tmp % mod;
        tmp = tmp * tmp % mod;
        n >>= 1;
    }
    return ret;
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

    ios::sync_with_stdio(false);

    long long N, M;
    cin >> N >> M;
    if (N >= M) {
        Matrix m, rgt;
        m.mat[0][0] = m.mat[0][M - 1] = 1;
        for (long long i = 1; i < M; i++) {
            m.mat[i][i - 1] = 1;
        }
        for (long long i = 0; i < M; i++) {
            rgt.mat[i][0] = 1;
        }
        rgt.mat[0][0]++;

        m = pow_M(m, N - M, MOD);
        cout << mul_M(m, rgt, MOD).mat[0][0] << endl;
    } else {
        cout << 1 << endl;
    }


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}