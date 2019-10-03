#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 200500;
const long long PHI = (long long) 998244352;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x1f3f3f3f3f3f3f3f;
const long long MOD = (long long) 998244353;
const long long OVER_FLOW = 0xffffffff;

long long n, K, m;

struct Matrix {
    long long mat[150][150];

} lft, rgt;

Matrix mul_M(Matrix a, Matrix b, long long mod) {
    Matrix ret;
    for (int i = 0; i < K; i++)
        for (int j = 0; j < K; j++) {
            ret.mat[i][j] = 0;
            for (int k = 0; k < K; k++) {
                ret.mat[i][j] += a.mat[i][k] * b.mat[k][j] % mod;
                if (ret.mat[i][j] >= mod)ret.mat[i][j] -= mod;
            }
        }
    return ret;
}

Matrix pow_M(Matrix a, long long n, long long mod) {
    Matrix ret;
    memset(ret.mat, 0, sizeof(ret.mat));
    for (int i = 0; i < K; i++)ret.mat[i][i] = 1;
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


void exgcd(long long a, long long b, long long &g, long long &x, long long &y) {
    if (!b) return (void) (x = 1, y = 0, g = a);
    exgcd(b, a % b, g, y, x);
    y -= x * (a / b);
}

long long rmd_equation(long long A, long long B, long long P) { //Ax == B (mod P), solve x
    long long a = A, b = P, g, x, y;
    exgcd(a, b, g, x, y);
    if (B % g) return -1;
    x *= B / g, y *= B / g;
    long long t = b / g;
    x = (x % t + t) % t;
    return x;
}


//(POJ 2417,3243)
//baby_step giant_step
// a^x = b (mod n) n 是素数和不是素数都可以
// 求解上式0<=x < n 的解
#define md 76543
int hs[md], head[md], nxt[md], id[md], top;

void insert(int x, int y) {
    int k = x % md;
    hs[top] = x, id[top] = y, nxt[top] = head[k], head[k] = top++;
}

int find(int x) {
    int k = x % md;
    for (int i = head[k]; i != -1; i = nxt[i])
        if (hs[i] == x)
            return id[i];
    return -1;
}

int BSGS(int a, int b, int n) {
    memset(head, -1, sizeof(head));
    top = 1;
    if (b == 1)return 0;
    int m = sqrt(n * 1.0), j;
    long long x = 1, p = 1;
    for (int i = 0; i < m; ++i, p = p * a % n)insert(p * b % n, i);
    for (long long i = m;; i += m) {
        if ((j = find(x = x * p % n)) != -1)return i - j;
        if (i > n)break;
    }
    return -1;
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
    cin >> K;
    lft.mat[0][K - 1] = 1;
    for (long long i = 0; i < K - 1; i++) {
        rgt.mat[i + 1][i] = 1;
    }
    for (long long i = 0; i < K; i++) {
        long long u;
        cin >> u;
        rgt.mat[K - 1 - i][K - 1] = u;
    }
    cin >> n >> m;

    rgt = pow_M(rgt, n - K, PHI);
    lft = mul_M(lft, rgt, PHI);
    long long cur = lft.mat[0][K - 1];
    long long x, a;
    a = BSGS(3ll, m, MOD);
    x = rmd_equation(cur, a, PHI);
    if (x == -1) {
        cout << -1 << endl;
    } else {
        cout << qpow(3ll, x, MOD) << endl;
    }


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}