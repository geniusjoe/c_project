#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 200500;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x1f3f3f3f3f3f3f3f;
const long long MOD = 998244353;
const long long OVER_FLOW = 0xffffffff;

long long s, T, n, m, M, k, A, B;
string str;

string get_res(long long x, long long y) {
    cout << "? " << x << " " << y << "\n";
    fflush(stdout);
    string cur;
    cin >> cur;
    return cur;
}

int main() {

#ifndef ONLINE_JUDGE
//    freopen("testdata.in", "r+", stdin);
//    freopen("testdata.out", "w+", stdout);
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
    4.注意数据规模,考虑从数据入手
*/

    ios::sync_with_stdio(false);
    while (cin >> str) {
        if (str != "start") break;
        long long cur = 1, lst = 0;
        while (cur <= (1 << 30)) {
            string w = get_res(lst, cur);
            if (w == "x") {
                break;
            } else {
                lst = cur;
                cur <<= 1;
            }
        }
        long long low = lst, high = cur;
        while (low + 1 < high) {
            long long mid = (low + high) >> 1;
            string w = get_res(mid, low);
            if (w == "x") low = mid;
            else high = mid;
        }
        cout << "! " << high << endl;

        fflush(stdout);
    }


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}