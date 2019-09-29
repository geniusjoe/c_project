#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 500500;
const long long PHI = (long long) 1e9 + 6;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x1f3f3f3f3f3f3f3f;
const long long MOD = (long long) 1e9 + 7;
const long long OVER_FLOW = 0xffffffff;

long long n;
vector<pair<long long, long long>> buf;

// x * y % m
long long qmul(long long x, long long y, long long m) {
    long long res = 0;
    while (y) {
        if (y & 1) res = (res + x) % m;
        x = (x + x) % m;
        y >>= 1;
    }
    return res;
}

long long get(long long x) {
    long long even = 0, odd = 0, nm = 0;
    while (x > 0) {
        if (nm % 2 == 0) {
            odd += min(x, 1ll << nm);
        } else {
            even += min(x, 1ll << nm);
        }
        x -= 1ll << nm;
        nm++;
    }
    return (qmul(odd, odd, MOD) + qmul(even, even + 1, MOD)) % MOD;
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
    long long l, r;
    cin >> l >> r;
    cout << (get(r) - get(l - 1) + MOD) % MOD << endl;

#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}