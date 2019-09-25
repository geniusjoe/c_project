#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 200500;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x1f3f3f3f3f3f3f3f;
const long long MOD = (long long) 998244353;
const long long OVER_FLOW = 0xffffffff;

long long n, m, q;
long long buf[MAXN];

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
    long long T;
    cin >> T;
    while (T--) {
        cin >> n;
        long long res = 0;
        for (long long i = 1; i <= n; i++)
            scan_d(buf[i]);
        res = max(res, *max_element(buf + 1, buf + 1 + n));
        long long flg2 = false, flg3 = false, flg5 = false;
        for (long long i = 1; i <= n; i++) {
            if (res == 2 * buf[i]) flg2 = true;
            if (res == 3 * buf[i]) flg3 = true;
            if (res == 5 * buf[i]) flg5 = true;
        }
        if (flg2 and flg3 and flg5) res = max(res, res / 2 + res / 3 + res / 5);
        sort(buf + 1, buf + 1 + n);
        for (long long i = 1; i < n; i++) {
            if (buf[n] % buf[i] == 0) {
                buf[i] = INF;
            }
        }
        sort(buf + 1, buf + 1 + n);
        n = lower_bound(buf + 1, buf + 1 + n, INF) - buf - 1;
        if (n >= 2) res = max(res, buf[n] + buf[n - 1]);
        for (long long i = n - 2; i >= 1; i--) {
            if (buf[n - 1] % buf[i] != 0)
                res = max(res, buf[n] + buf[n - 1] + buf[i]);
        }
        cout << res << '\n';

    }


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}