#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 200500;
const long long PHI = (long long) 1e9 + 6;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x1f3f3f3f3f3f3f3f;
const long long MOD = (long long) 1e9 + 7;
const long long OVER_FLOW = 0xffffffff;

long long n;
long long buf[MAXN], buf1[MAXN], tar[MAXN], tar1[MAXN];

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
    2.数量值太大尝试给出递推公式
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
    for (long long i = 1; i <= n; i++) cin >> buf1[i];

    for (long long i = 2; i <= n; i++) {
        tar[i] = buf[i] - buf[i - 1], tar1[i] = buf1[i] - buf1[i - 1];
    }
    sort(tar + 1, tar + 1 + n), sort(tar1 + 1, tar1 + 1 + n);

    bool flg = buf[1] == buf1[1];

    for (long long i = 1; i <= n; i++) {
        if (tar[i] != tar1[i]) {
            flg = false;
            break;
        }
    }

    if (flg) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}