#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 500500;
const long long INF = 0x7f3f3f3f;
const long long LINF = 0x1f3f3f3f3f3f3f3f;
const long long MOD = 998244353;
const long long OVER_FLOW = 0xffffffff;

long long n, m; /**< n个数,m个操作,以model为模 */
long long buf[MAXN];
long long rst[720][720];

template<class T>
inline bool scan_d(T &ret) {
    char c;
    int sgn;
    if (c = getchar(), c == EOF) return 0;
    while (c != '-' && (c < '0' || c > '9')) c = getchar();
    sgn = (c == '-') ? -1 : 1;
    ret = (c == '-') ? 0 : (c - '0');
    while (c = getchar(), c >= '0' && c <= '9') ret = ret * 10 + (c - '0');
    ret *= sgn;
    return 1;
}

inline void out(int x) {
    if (x > 9) out(x / 10);
    putchar(x % 10 + '0');
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
    6.0-1子矩阵子序列:前缀和
    7.模拟题注意代码复用.
    8.单个区间问题考虑前缀和,多个区间左右端点拆开,排序,记录端点极值
思考提醒：
    1.最大值和最小值问题可不可以用二分+贪心？
    2.dp
    3.如果规模小的话还能尝试dfs
    4.如果存在等式.转换关系少可以暴力枚举变量,或者考虑从数据大小入手
*/

//    ios::sync_with_stdio(false);
    long long T;
//    cin >> T;
    scan_d(T);
    while (T--) {
        long long op, u, v;
//        cin >> op >> u >> v;
        scan_d(op), scan_d(u), scan_d(v);
        if (op == 1) {
            for (long long i = 1; i <= 710; i++) {
                rst[i][u % i] += v;
            }
            buf[u] += v;
        } else {
            if (u <= 710)
                cout << rst[u][v] << '\n';
            else {
                long long cur = 0;
                for (long long i = v; i <= 500000; i += u) {
                    cur += buf[i];
                }
                cout << cur << '\n';
            }
        }
    }

#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}