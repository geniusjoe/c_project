#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 200500;
const long long PHI = (long long) 998244352;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x1f3f3f3f3f3f3f3f;
const long long MOD = (long long) 998244353;
const long long OVER_FLOW = 0xffffffff;

long long n;
vector<pair<long long, long long>> buf[MAXN];

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
    2.dp或者数值太大,尝试给出递推公式或者预处理数据
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
    const long long m = 2e5 + 5;
    for (long long i = 1; i <= m; i++) {
        for (long long j = i + 1; j * j - i * i <= m; j++) {
            buf[j * j - i * i].emplace_back(i, j);
        }
    }

    cin >> n;
    vector<long long> res;
    bool flg = true;
    res.push_back(0);
    for (long long i = 1; i <= n / 2; i++) {
        long long u;
        cin >> u;
        bool flag = false;
        for (auto it:buf[u]) {
            if (it.first > res.back()) {
                res.push_back(it.first), res.push_back(it.second);
                flag = true;
                break;
            }
        }
        if (!flag) {
            flg = false;
        }
    }
    if (flg) {
        cout << "Yes" << endl;
        for (long long i = 1; i < res.size(); i++) {
            cout << res[i] * res[i] - res[i - 1] * res[i - 1] << " ";
        }
        cout << endl;
    } else {
        cout << "No" << endl;
    }


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}