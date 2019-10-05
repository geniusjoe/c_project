#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 200500;
const long long PHI = (long long) 998244352;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x1f3f3f3f3f3f3f3f;
const long long MOD = (long long) 998244353;
const long long OVER_FLOW = 0xffffffff;

long long n;


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
    vector<pair<long long, long long>> buf, ans;
    for (long long i = 1; i <= 3; i++) {
        long long u, v;
        cin >> u >> v;
        buf.emplace_back(u, v);
    }
    long long res = LINF;
    sort(buf.begin(), buf.end(), [](pair<long long, long long> p1, pair<long long, long long> p2) {
        return p1.first < p2.first;
    });

    long long y_max = max(max(buf[0].second, buf[1].second), buf[2].second),
            y_min = min(min(buf[0].second, buf[1].second), buf[2].second);
    if (res > buf[2].first - buf[0].first + y_max - y_min) {
        ans.clear();
        long long cur_x = buf[1].first;
        for (long long i = y_min; i <= y_max; i++) {
            ans.emplace_back(cur_x, i);
        }
        for (long long i = cur_x + 1; i <= buf[2].first; i++) {
            ans.emplace_back(i, buf[2].second);
        }
        for (long long i = cur_x - 1; i >= buf[0].first; i--) {
            ans.emplace_back(i, buf[0].second);
        }
        res = ans.size();
    }

    sort(buf.begin(), buf.end(), [](pair<long long, long long> p1, pair<long long, long long> p2) {
        return p1.second < p2.second;
    });
    long long x_max = max(max(buf[0].first, buf[1].first), buf[2].first),
            x_min = min(min(buf[0].first, buf[1].first), buf[2].first);
    if (res > buf[2].second - buf[0].second + x_max - x_min) {
        ans.clear();
        long long cur_y = buf[1].second;
        for (long long i = x_min; i <= x_max; i++) {
            ans.emplace_back(i, cur_y);
        }
        for (long long i = cur_y + 1; i <= buf[2].second; i++) {
            ans.emplace_back(buf[2].first, i);
        }
        for (long long i = cur_y - 1; i >= buf[0].second; i--) {
            ans.emplace_back(buf[0].first, i);
        }
        res = ans.size();
    }

    cout << res << endl;
    for (auto it:ans) {
        cout << it.first << " " << it.second << '\n';
    }


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}