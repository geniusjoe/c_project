#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 3005000;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x1f3f3f3f3f3f3f3f;
const long long MOD = (long long) 1e9 + 7;
const long long OVER_FLOW = 0xffffffff;


long long s, T, n, m, M, k, A, B, p;
long long pre[MAXN], suf[MAXN];
long long vis[MAXN];

struct point {
    long long id, tme, cst;

    bool operator<(point point1) {
        return this->tme < point1.tme;
    }
};

vector<point> come, go;
queue<point> q_cme, q_go;
long long res1[MAXN], res2[MAXN];

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
    cin >> n >> m >> k;
    for (long long i = 1; i <= m; i++) {
        long long di, fi, ti, ci;
        cin >> di >> fi >> ti >> ci;
        if (fi == 0) {
            go.push_back(point{ti, di, ci});
        } else {
            come.push_back(point{fi, di, ci});
        }
    }
    sort(go.begin(), go.end()), sort(come.begin(), come.end());
    if (!go.empty())
        for (long long i = go.size() - 1; i >= 0; i--) q_go.push(go[i]);
    for (auto it:come) q_cme.push(it);
    for (long long i = 1; i <= 1000000; i++) res1[i] = vis[i] = LINF;

    long long nm = 0, sm = 0;
    for (long long i = 1; i <= 1000000; i++) {
        while (!q_cme.empty()) {
            point cur = q_cme.front();
            if (cur.tme == i) {
                q_cme.pop();
                if (vis[cur.id] == LINF) {
                    nm++;
                    vis[cur.id] = cur.cst;
                    sm += cur.cst;
                } else if (vis[cur.id] > cur.cst) {
                    sm -= vis[cur.id];
                    sm += cur.cst;
                    vis[cur.id] = cur.cst;
                }
            } else break;
        }
        if (nm == n) res1[i] = sm;
    }

    nm = sm = 0;
    for (long long i = 1; i <= 1000000; i++) res2[i] = vis[i] = LINF;
    for (long long i = 1000000; i >= 1; i--) {
        while (!q_go.empty()) {
            point cur = q_go.front();
            if (cur.tme == i) {
                q_go.pop();
                if (vis[cur.id] == LINF) {
                    nm++;
                    vis[cur.id] = cur.cst;
                    sm += cur.cst;
                } else if (vis[cur.id] > cur.cst) {
                    sm -= vis[cur.id];
                    sm += cur.cst;
                    vis[cur.id] = cur.cst;
                }
            } else break;
        }
        if (nm == n) res2[i] = sm;
    }

    long long res = LINF;
    for (long long i = 1; i <= 1000000 - k - 1; i++) {
        res = min(res, res1[i] + res2[i + k + 1]);
    }

    if (res == LINF)
        cout << -1 << endl;
    else
        cout << res << endl;


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}