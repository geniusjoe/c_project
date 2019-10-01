#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 200500;
const long long PHI = (long long) 1e9 + 6;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x1f3f3f3f3f3f3f3f;
const long long MOD = (long long) 1e9 + 7;
const long long MOD1 = (long long) 1e8 + 3;
const long long MOD2 = (long long) 988244353;
const long long OVER_FLOW = 0xffffffff;

long long n;
map<double, long long> hsh1, hsh2, hsh3;
long long buf[MAXN], tar[MAXN];

// a ^ b % c
long long qpow(long long a, long long b, long long c) {
    long long cur = 1;
    while (b) {
        if (b & 1) cur = cur * a % c;
        a = a * a % c, b >>= 1;
    }
    return cur;
}

long long inv(long long num, long long m) {
    return qpow(num, m - 2, m);
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
    cin >> n;
    for (long long i = 1; i <= n; i++) cin >> buf[i];

    long long cnt = 0;

    for (long long i = 1; i <= n; i++) {
        long long u;
        cin >> u;
        if (buf[i] == 0 and u != 0) continue;
        else if (buf[i] == 0 and u == 0) cnt++;
        else {
            long long x = buf[i] / __gcd(buf[i], u), y = u / __gcd(buf[i], u);
            hsh1[1.0l * x / y]++;
            hsh2[x * inv(y, MOD) % MOD]++;
        }
    }

    long long res1 = cnt, res2 = cnt;
    for (auto &it:hsh1) {
        res1 = max(res1, it.second + cnt);
    }
    for (auto it:hsh2) {
        res2 = max(res2, it.second + cnt);
    }

    cout << min(res1, res2)  << endl;


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}