#include<bits/stdc++.h>

//#pragma GCC optimize(2)

using namespace std;

const long long MAXN = 2050;
const long long PHI = (long long) 998244352;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x1f3f3f3f3f3f3f3f;
const long long MOD = (long long) 998244353;
const long long OVER_FLOW = 0xffffffff;

long long n;
map<long long, map<string, vector<long long>>> mp;

#define setbit(x, y) x|=(1ll<<y)

#define clrbit(x, y) x&=~(1ll<<y)

#define reversebit(x, y) x^=(1ll<<y)

#define getbit(x, y) ((x) >> (y)&1ll)

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
    cin >> n;
    for (long long j = 1; j <= n; j++) {
        string s, t;
        cin >> s >> t;
        long long cur = 0;
        for (auto it:t) {
            setbit(cur, (it - 'a'));
        }
        long long lst = s.size();
        for (long long i = s.size() - 1; i >= 0; i--) {
            if (getbit(cur, s[i] - 'a')) lst = i;
            else break;
        }
#ifndef ONLINE_JUDGE
        cout << s.substr(0, lst) << endl;
#endif
        mp[cur][s.substr(0, lst)].push_back(j);
    }

    long long res = 0;
    for (const auto &mpi:mp) {
        res += mpi.second.size();
    }
    cout << res << endl;
    for (auto mpi:mp) {
        for (auto it:mpi.second) {
            cout << it.second.size() << " ";
            for (auto it2:it.second) {
                cout << it2 << " ";
            }
            cout << '\n';
        }
    }


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}