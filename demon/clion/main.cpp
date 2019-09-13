#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 5005;
const long long INF = 0x7f3f3f3f;
const long long LINF = 0x1f3f3f3f3f3f3f3f;
const long long MOD = 998244353;
const long long OVER_FLOW = 0xffffffff;

long long n; /**< n个数,m个操作,以model为模 */
string str;

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
    6.0-1子矩阵子序列:前缀和
    7.模拟题注意代码复用.
    8.单个区间问题考虑前缀和,多个区间左右端点拆开,排序,记录端点极值
思考提醒：
    1.最大值和最小值问题可不可以用二分+贪心？
    2.dp
    3.如果规模小的话还能尝试dfs
    4.如果存在等式.转换关系少可以暴力枚举变量,或者考虑从数据大小入手
*/

    ios::sync_with_stdio(false);
    long long T;
    cin >> T;
    while (T--) {
        cin >> str;
        long long up = 0, down = 0, left = 0, right = 0;
        long long f_up = 0, l_up = 0, f_down = 0, l_down = 0, f_left = 0, l_left = 0, f_right = 0, l_right = 0;
        long long cur_x = 0, cur_y = 0;
        for (long long i = 0; i < str.size(); i++) {
            if (str[i] == 'W') {
                cur_x++;
                if (cur_x > up) {
                    up = cur_x;
                    f_up = l_up = i;
                } else if (cur_x == up) {
                    l_up = i;
                }
            } else if (str[i] == 'S') {
                cur_x--;
                if (cur_x < down) {
                    down = cur_x;
                    f_down = l_down = i;
                } else if (cur_x == down) {
                    l_down = i;
                }
            } else if (str[i] == 'A') {
                cur_y--;
                if (cur_y < left) {
                    left = cur_y;
                    f_left = l_left = i;
                } else if (cur_y == left) {
                    l_left = i;
                }
            } else if (str[i] == 'D') {
                cur_y++;
                if (cur_y > right) {
                    right = cur_y;
                    f_right = l_right = i;
                } else if (cur_y == right) {
                    l_right = i;
                }
            }
        }

        long long res = (up - down + 1) * (right - left + 1);
        if (l_up < f_down || l_down < f_up) res = min(res, max(2ll, (up - down)) * (right - left + 1));
        if (l_left < f_right || l_right < f_left) res = min(res, max(2ll, (right - left)) * (up - down + 1));

        cout << res << endl;
    }

#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}