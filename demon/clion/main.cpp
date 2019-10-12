#include<bits/stdc++.h>

//#pragma GCC optimize(2)

using namespace std;

const long long MAXN = 300500;
const long long PHI = (long long) 998244352;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x3f3f3f3f3f3f3f3f;
const long long MOD = (long long) 1e9 + 7;
const long long OVER_FLOW = 0x7fffffff;
const long long LOVER_FLOW = 0x7fffffffffffffff;

long long n;

struct pts {
    long long x, y, id;

    bool operator<(pts pts1) {
        return this->x - this->y < pts1.x - pts1.y;
    }
} buf[MAXN], tar[MAXN];

long long pre_x[MAXN], pre_y[MAXN], suf_x[MAXN], suf_y[MAXN];
long long res[MAXN];

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
    long long m;
    cin >> n >> m;
    for (long long i = 1; i <= n; i++) {
        cin >> buf[i].x >> buf[i].y;
        buf[i].id = i;
        tar[i].x = buf[i].x, tar[i].y = buf[i].y;
    }
    sort(buf + 1, buf + 1 + n);

    for (long long i = 1; i <= n; i++) {
        pre_x[i] = pre_x[i - 1] + buf[i].x, pre_y[i] = pre_y[i - 1] + buf[i].y;
    }
    for (long long i = n; i >= 1; i--) {
        suf_x[i] = suf_x[i + 1] + buf[i].x, suf_y[i] = suf_y[i + 1] + buf[i].y;
    }
    for (long long i = 1; i <= n; i++) {
        res[buf[i].id] += pre_x[i - 1] + (i - 1) * buf[i].y
                          + (n - i) * buf[i].x + suf_y[i + 1];
    }

    for (long long i = 1; i <= m; i++) {
        long long u, v;
        cin >> u >> v;
        long long cur = 0;
        if (tar[u].x + tar[v].y < tar[u].y + tar[v].x) {
            cur = tar[u].x + tar[v].y;
        } else {
            cur = tar[u].y + tar[v].x;
        }
        res[u] -= cur, res[v] -= cur;
    }

    for (long long i = 1; i <= n; i++) {
        cout << res[i] << " ";
    }
    cout << endl;


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}