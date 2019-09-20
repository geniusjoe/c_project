#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 400050;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x1f3f3f3f3f3f3f3f;
const long long MOD = (long long) 1e9 + 7;
const long long OVER_FLOW = 0xffffffff;

long long n;
long long ans[MAXN << 2];
vector<pair<long long, long long>> points;
vector<long long> pts[MAXN];
vector<long long> buf;

inline long long lchild(long long x)
/**<  每个树节点的编号*/
{
    return x << 1;
}

inline long long rchild(long long x) {
    return x << 1 | 1;
}

inline void push_up(long long p) {
    ans[p] = (ans[lchild(p)] + ans[rchild(p)]);
}

/**< 由顶向下建立线段树 */
/**< 左右均为闭区间 */
void build(long long p, long long l, long long r) {
    if (l == r) {
        ans[p] = 0;
        return;
    }
    long long mid = (l + r) >> 1;
    build(lchild(p), l, mid);
    build(rchild(p), mid + 1, r);
    push_up(p);
}
/**< 区间赋值操作 */
/**< 区间内元素增加的值 */
inline void update(long long nl, long long nr,   /**< 目标边界 */
                   long long l, long long r, long long p /**< 当前边界和节点 */
) {
    if (nl <= l && r <= nr) {
        ans[p] = 1;
        return;
    }
    long long mid = (l + r) >> 1;
    if (nl <= mid)
        update(nl, nr, l, mid, lchild(p));
    if (nr > mid)
        update(nl, nr, mid + 1, r, rchild(p));
    push_up(p);
}

/**< 区间查询操作 */
long long query(long long q_x, long long q_y, long long l, long long r, long long p) {
    if (q_x > q_y) return 0;
    long long res = 0;
    if (q_x <= l && r <= q_y)
        return ans[p];
    long long mid = (l + r) >> 1;
    if (q_x <= mid)
        res += query(q_x, q_y, l, mid, lchild(p));
    if (q_y > mid)
        res += query(q_x, q_y, mid + 1, r, rchild(p));
    return res;
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
    5.离散化+打表
*/

    ios::sync_with_stdio(false);
    cin >> n;

    for (long long i = 1; i <= n; i++) {
        long long x, y;
        cin >> x >> y;
        points.emplace_back(x, y);
        buf.push_back(x), buf.push_back(y);
    }
    sort(buf.begin(), buf.end());
    auto ip = unique(buf.begin(), buf.end());
    buf.resize(distance(buf.begin(), ip));

    build(1, 1, buf.size() + 10);

    for (auto cur : points) {
        cur.first = lower_bound(buf.begin(), buf.end(), cur.first) - buf.begin() + 1;
        cur.second = lower_bound(buf.begin(), buf.end(), cur.second) - buf.begin() + 1;
        pts[cur.second].push_back(cur.first);
    }
    for (long long i = 1; i < 4e5 + 5; i++)
        sort(pts[i].begin(), pts[i].end());

    long long res = 0;
    for (long long i = 4e5 + 5; i >= 1; i--) {
        if (!pts[i].empty()) {
            pts[i].push_back(buf.size() + 5);
            for (long long j = 0; j < pts[i].size() - 1; j++) {
                long long t1 = query(1, pts[i][j] - 1, 1, buf.size(), 1);
                long long t2 = query(pts[i][j] + 1, buf.size(), 1, buf.size(), 1) -
                               query(pts[i][j + 1], buf.size(), 1, buf.size(), 1);
                res += (t1 + 1) * (t2 + 1);
                update(pts[i][j], pts[i][j], 1, buf.size(), 1);
            }
        }
    }

    cout << res << endl;


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}