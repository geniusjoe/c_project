#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 200500;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x1f3f3f3f3f3f3f3f;
const long long MOD = 998244353;
const long long OVER_FLOW = 0xffffffff;


long long c, s, T, n, m, M, k;
map<long long, long long> mp;

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
    5.排序之前不能取模.
    6.0-1子矩阵子序列:前缀和
    7.模拟题注意代码复用.
    8.单个区间问题考虑前缀和,多个区间左右端点拆开,排序,记录端点极值
思考提醒：
    1.最大值和最小值问题可不可以用二分答案？
    2.有没有贪心策略？否则能不能dp？
    3.如果规模小的话还能尝试dfs,如果存在等式.转换关系少可以暴力枚举变量
*/

    ios::sync_with_stdio(false);
    long long b;
    cin >> n >> b;
    for (long long i = 2; i * i <= b; i++) {
        while (b % i == 0) {
            mp[i]++;
            b /= i;
        }
    }
    if (b != 1) mp[b]++;
    long long res = LINF;
    for (auto it = mp.begin(); it != mp.end(); it++) {
        long long cur = n, cnt = 0;
        while (cur) {
            cnt += cur / it->first;
            cur /= it->first;
        }
        cnt /= it->second;
        res = min(res, cnt);
    }
    cout << res << endl;


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}