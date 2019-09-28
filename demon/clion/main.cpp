#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 300500;
const long long PHI = (long long) 1e9 + 6;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x1f3f3f3f3f3f3f3f;
const long long MOD = (long long) 1e9 + 7;
const long long OVER_FLOW = 0xffffffff;

long long n;
long long buf[MAXN];

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
    long long k, delta;
    cin >> k >> n;
    bool flg = true;
    for (long long i = 1; k >= 0 and i <= n; i++) {
        buf[i] = i, k -= i;
    }
    if (k < 0) flg = false;
    else {
        delta = k / n;
        k -= delta * n;
        while (k) {
            for (long long i = n; k and i >= 1; i--) {
                if (buf[i] + delta + 1 <= (buf[i - 1] + delta) * 2) {
                    buf[i]++, k--;
                } else break;
            }
            if (k and buf[n] + delta + 1 > (buf[n - 1] + delta) * 2) {
                flg = false;
                break;
            }
        }
    }

    if (!flg) {
        cout << "NO" << '\n';
    } else {
        cout << "YES" << '\n';
        for (long long i = 1; i <= n; i++) {
            cout << buf[i] + delta << " ";
        }
        cout << "\n";
    }


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}