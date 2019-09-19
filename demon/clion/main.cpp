#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 5050;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x1f3f3f3f3f3f3f3f;
const long long MOD = (long long) 1e9 + 7;
const long long OVER_FLOW = 0xffffffff;

long long n;
bitset<MAXN + 5> edge[MAXN];

struct line {
    long long x1, x2, y1, y2;
};
vector<line> row, col;

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
    cin >> n;
    for (long long i = 1; i <= n; i++) {
        long long x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 == x2) row.push_back(line{x1, x2, min(y1, y2), max(y1, y2)});
        else col.push_back(line{min(x1, x2), max(x1, x2), y1, y2});
    }

    if (row.size() < col.size()) {
        for (long long i = 0; i < row.size(); i++) {
            for (long long j = 0; j < col.size(); j++) {
                if (row[i].y1 <= col[j].y1 && row[i].y2 >= col[j].y1
                    && row[i].x1 >= col[j].x1 && row[i].x1 <= col[j].x2)
                    edge[i].set(j);
            }
        }
        long long res = 0;
        for (long long i = 0; i < row.size(); i++) {
            for (long long j = i + 1; j < row.size(); j++) {
                long long t = (edge[i] & edge[j]).count();
                res += t * (t - 1) / 2;
            }
        }
        cout << res << endl;
    } else {
        for (long long i = 0; i < col.size(); i++) {
            for (long long j = 0; j < row.size(); j++) {
                if (col[i].x1 <= row[j].x1 && col[i].x2 >= row[j].x1
                    && col[i].y1 >= row[j].y1 && col[i].y1 <= row[j].y2)
                    edge[i].set(j);
            }
        }
        long long res = 0;
        for (long long i = 0; i < col.size(); i++) {
            for (long long j = i + 1; j < col.size(); j++) {
                long long t = (edge[i] & edge[j]).count();
                res += t * (t - 1) / 2;
            }
        }
        cout << res << endl;
    }


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}