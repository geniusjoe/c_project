#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 2005;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x1f3f3f3f3f3f3f3f;
const long long MOD = (long long) 1e9 + 7;
const long long OVER_FLOW = 0xffffffff;

struct point {
    long long x, y, rst_x, rst_y;
};

long long s, T, n, m, M, k, A, B, p;
long long r, c, x, y;
string graph[MAXN];
queue<point> q;
pair<long long, long long> buf[MAXN][MAXN];

bool ok(point x) {
    return (x.x >= 1 && x.x <= n && x.y >= 1 && x.y <= m &&
            (graph[x.x][x.y - 1] == '.' ||
             (graph[x.x][x.y - 1] == '1' && (buf[x.x][x.y].first < x.rst_x || buf[x.x][x.y].second < x.rst_y)))
            && x.rst_y >= 0 && x.rst_x >= 0);
}

void solve() {
    q.push(point{r, c, x, y});
    graph[r][c - 1] = '1';
    buf[r][c].first = x, buf[r][c].second = y;
    while (!q.empty()) {
        point cur = q.front();
        q.pop();
        long long dx[] = {-1, 0, 1, 0}, dy[] = {0, -1, 0, 1};
        for (long long i = 0; i < 4; i++) {
            point nxt{cur.x + dx[i], cur.y + dy[i], cur.rst_x - (dy[i] == -1), cur.rst_y - (dy[i] == 1)};
            if (ok(nxt)) {
                graph[nxt.x][nxt.y - 1] = '1';
                q.push(nxt);
                buf[nxt.x][nxt.y].first = max(buf[nxt.x][nxt.y].first, nxt.rst_x);
                buf[nxt.x][nxt.y].second = max(buf[nxt.x][nxt.y].second, nxt.rst_y);
            }
        }
    }
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
    cin >> n >> m;
    cin >> r >> c;
    cin >> x >> y;
    for (long long i = 1; i <= n; i++) cin >> graph[i];
    solve();
    long long res = 0;
    for (long long i = 1; i <= n; i++) {
        for (long long j = 1; j <= m; j++) {
            if (graph[i][j - 1] == '1') res++;
        }
    }
    cout << res << endl;


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}