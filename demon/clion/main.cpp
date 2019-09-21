#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 300500;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x1f3f3f3f3f3f3f3f;
const long long MOD = (long long) 998244353;
const long long OVER_FLOW = 0xffffffff;

long long n;
long long buf[MAXN], tar[MAXN];
queue<long long> idx[MAXN];

long long ans[MAXN << 2];

inline long long lchild(long long x)
/**<  每个树节点的编号*/
{
    return x << 1;
}

inline long long rchild(long long x) {
    return x << 1 | 1;
}

inline void push_up(long long p) {
    ans[p] = min(ans[lchild(p)], ans[rchild(p)]);
}

/**< 由顶向下建立线段树 */
/**< 左右均为闭区间 */
void build(long long p, long long l, long long r) {
    if (l == r) {
        ans[p] = tar[l];
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
        ans[p] = INF;
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
    long long res = INF;
    if (q_x <= l && r <= q_y) {
        return ans[p];
    }
    long long mid = (l + r) >> 1;
    if (q_x <= mid) {
        res = min(res, query(q_x, q_y, l, mid, lchild(p)));
    }
    if (q_y > mid)
        res = min(res, query(q_x, q_y, mid + 1, r, rchild(p)));
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
    long long T;
    cin >> T;
    while (T--) {
        for (long long i = 1; i <= n; i++) while (!idx[i].empty()) idx[i].pop();
        cin >> n;

        for (long long i = 1; i <= n; i++) {
            long long u;
            cin >> u;
            idx[u].push(i);
            tar[i] = u;
        }
        for (long long i = 1; i <= n; i++) {
            cin >> buf[i];
        }

        build(1, 1, n);
        bool flg = true;
        for (long long i = 1; i <= n; i++) {
            if (idx[buf[i]].empty()) {
                flg = false;
                break;
            } else {
                long long pos = idx[buf[i]].front(), cur = i;
                idx[buf[i]].pop();
                if (buf[cur] != query(1, pos, 1, n, 1)) {
                    flg = false;
                    break;
                }
                update(pos, pos, 1, n, 1);
            }
        }

        if (flg) {
            cout << "YES" << endl;
        } else
            cout << "NO" << endl;
    }


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}