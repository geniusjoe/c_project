#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 50005000;
const long long PHI = (long long) 1e9 + 6;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x1f3f3f3f3f3f3f3f;
const long long MOD = (long long) 1e9 + 7;
const long long OVER_FLOW = 0xffffffff;

long long n;
long long pos[MAXN];

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
    long long res = LINF;
    int p1 = 0, p2 = 0;
    cin >> n;
    for (long long i = 1; i <= n; i++) {
        long long u;
        cin >> u;
        if (pos[u] == 0) pos[u] = i;
        else {
            if (res > u) {
                res = u;
                p1 = i, p2 = pos[u];
            }
        }
    }
    for (long long i = 1; i <= 1e7 + 5; i++) {
        long long s1 = 0, v1 = 0;
        for (long long j = i; j <= 1e7 + 5; j += i) {
            if (pos[j] and s1) {
                if (res > 1ll * v1 * j / i) {
                    res = v1 * j / i;
                    p1 = s1, p2 = pos[j];
                }
                break;
            } else if (pos[j] and s1 == 0) {
                s1 = pos[j], v1 = j;
            }
        }
    }

    cout << min(p1, p2) << " " << max(p1, p2) << endl;


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}