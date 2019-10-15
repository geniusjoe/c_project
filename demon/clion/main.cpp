#include<bits/stdc++.h>

//#pragma GCC optimize(2)

using namespace std;

const long long MAXN = 200500;
const long long PHI = (long long) 998244352;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x3f3f3f3f3f3f3f3f;
const long long MOD = (long long) 998244353;
const long long OVER_FLOW = 0x7fffffff;
const long long LOVER_FLOW = 0x7fffffffffffffff;

long long n;
string str1, str2;
long long buf[MAXN];
long long bse[MAXN];

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
    long long a, b;
    cin >> a >> b >> str2 >> str1;
    reverse(str1.begin(), str1.end()), reverse(str2.begin(), str2.end());
    for (long long i = 0; i < str1.size(); i++) {
        buf[i] = str1[i] == '1';
    }
    for (long long i = str1.size() - 1; i >= 0; i--) {
        buf[i] = (buf[i + 1] + buf[i]) % MOD;
    }
    long long res = 0;
    bse[0] = 1;
    for (long long i = 1; i <= max(str1.size(), str2.size()); i++) {
        bse[i] = (bse[i - 1] * 2) % MOD;
    }

    for (long long i = 0; i < str2.size(); i++) {
        if (str2[i] == '0') continue;
        res = (res + bse[i] * buf[i] % MOD) % MOD;
    }

    cout << res << endl;


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}