#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 200500;
const long long PHI = (long long) 1e9 + 6;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x1f3f3f3f3f3f3f3f;
const long long MOD = (long long) 1e9 + 7;
const long long OVER_FLOW = 0xffffffff;

long long n;
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
    mp[3] = 1;
    mp[7] = 1;
    mp[15] = 5;
    mp[31] = 1;
    mp[63] = 21;
    mp[127] = 1;
    mp[255] = 85;
    mp[511] = 73;
    mp[1023] = 341;
    mp[2047] = 89;
    mp[4095] = 1365;
    mp[8191] = 1;
    mp[16383] = 5461;
    mp[32767] = 4681;
    mp[65535] = 21845;
    mp[131071] = 1;
    mp[262143] = 87381;
    mp[524287] = 1;
    mp[1048575] = 349525;
    mp[2097151] = 299593;
    mp[4194303] = 1398101;
    mp[8388607] = 178481;
    mp[16777215] = 5592405;
    mp[33554431] = 1082401;

    long long T;
    cin >> T;
    while (T--) {
        cin >> n;
        if (mp.count(n)) {
            cout << mp[n] << '\n';
        } else {
            long long cnt = 0;
            while (n) {
                cnt++;
                n >>= 1;
            }
            cout << (1 << cnt) - 1 << '\n';
        }
    }


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}