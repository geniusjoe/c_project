#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 2050;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x1f3f3f3f3f3f3f3f;
const long long MOD = (long long) 998244353;
const long long OVER_FLOW = 0xffffffff;

long long n, m, q;
string buf[MAXN];
char tar[MAXN][MAXN];
vector<pair<long long, long long >> num[MAXN];

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
    5.离散化+打表
*/

    ios::sync_with_stdio(false);
    long long T;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (long long i = 1; i <= n; i++) cin >> buf[i];
        for (long long i = 1; i <= n; i++) for (long long j = 1; j <= m; j++) tar[i][j - 1] = '.';
        for (long long i = 0; i <= 26; i++) num[i].clear();

        bool flg = true;
        for (long long i = 1; i <= n; i++) {
            for (long long j = 1; j <= m; j++) {
                if (buf[i][j - 1] == '.') continue;
                else {
                    long long cur = buf[i][j - 1] - 'a';
                    if (num[cur].empty() or num[cur].size() == 1) num[cur].emplace_back(i, j);
                    else if ((num[cur][0].first == num[cur][1].first and num[cur][0].first == i) or
                             (num[cur][0].second == num[cur][1].second and num[cur][0].second == j)) {
                        num[cur].pop_back();
                        num[cur].emplace_back(i, j);
                    } else {
                        flg = false;
                        break;
                    }
                }
            }
            if (!flg) break;
        }
        long long lst = -1;
        for (long long i = 0; i <= 26; i++) {
            if (num[i].empty()) continue;
            else {
                lst = i;
                if (num[i].size() == 1) {
                    auto cur = num[i].back();
                    tar[cur.first][cur.second - 1] = i + 'a';
                } else if (num[i].size() == 2) {
                    auto front = num[i][0], tail = num[i][1];
                    if (front.first == tail.first) {
                        for (long long j = front.second; j <= tail.second; j++)
                            tar[front.first][j - 1] = i + 'a';
                    } else if (front.second == tail.second) {
                        for (long long j = front.first; j <= tail.first; j++)
                            tar[j][front.second - 1] = i + 'a';
                    }
                }
            }
        }

        for (long long i = 1; i <= n; i++) {
            for (long long j = 1; j <= m; j++) {
                if (buf[i][j - 1] == tar[i][j - 1]) continue;
                else flg = false;
            }
            if (!flg) break;
        }

        if (!flg)
            cout << "NO" << '\n';
        else {
            cout << "YES" << '\n';
            if (lst == -1) cout << "0" << '\n';
            else {
                cout << lst + 1 << '\n';
                for (long long i = 0; i <= lst; i++) {
                    if (num[i].empty()) {
                        auto cur = num[lst].back();
                        cout << cur.first << " " << cur.second << " " << cur.first << " " << cur.second << "\n";
                    } else if (num[i].size() == 1) {
                        auto cur = num[i].back();
                        cout << cur.first << " " << cur.second << " " << cur.first << " " << cur.second << "\n";
                    } else if (num[i].size() == 2) {
                        auto cur1 = num[i][0], cur2 = num[i][1];
                        cout << cur1.first << " " << cur1.second << " " << cur2.first << " " << cur2.second << "\n";
                    }
                }
            }
        }
    }


#ifndef ONLINE_JUDGE
    auto
            end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}