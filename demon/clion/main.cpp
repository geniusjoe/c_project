#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 100050;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x3f3f3f3f3f3f3f3f;
const long long MOD = 998244353;
const long long OVER_FLOW = 0xffffffff;

long long n, q, m, k, T, a, b;
string str;
long long buf[MAXN];
long long nm[5];

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
    4.做一些总比不做好.
    5.排序之前不能取模.
    6.0-1子矩阵子序列:前缀和
思考提醒：
    1.最大值和最小值问题可不可以用二分答案？
    2.有没有贪心策略？否则能不能dp？
    3.如果规模小的话还能尝试dfs,如果存在等式.转换关系少可以暴力枚举变量
*/

    ios::sync_with_stdio(false);
    cin >> n;
    cin >> str;
    for (long long i = 0; i < n; i++) cin >> buf[i];
    for (long long i = 0; i < str.size(); i++) {
        if (str[i] == 'h') nm[1] += buf[i];
        else if (str[i] == 'a') nm[2] = min(nm[1], nm[2] + buf[i]);
        else if (str[i] == 'r') nm[3] = min(nm[2], nm[3] + buf[i]);
        else if (str[i] == 'd') nm[4] = min(nm[3], nm[4] + buf[i]);
    }
    cout << nm[4] << endl;

#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}