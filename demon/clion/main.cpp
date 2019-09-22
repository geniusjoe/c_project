#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 1005000;
const long long INF = 0x3f3f3f3f;
const long long LINF = 0x1f3f3f3f3f3f3f3f;
const long long MOD = (long long) 998244353;
const long long OVER_FLOW = 0xffffffff;

long long n, m, q;
long long price[MAXN], money[MAXN];


long long ans[MAXN << 2];
long long add[MAXN << 2]; /**< add 代表加的add,mul代表乘的add */
long long add_num; /**< 每个操作的操作数 */
inline long long lchild(long long x)
/**<  每个树节点的编号*/
{
    return x << 1;
}

inline long long rchild(long long x) {
    return x << 1 | 1;
}

inline void push_up(long long p) {
    ans[p] = max(ans[lchild(p)], ans[rchild(p)]);
}

/**< 由顶向下建立线段树 */
/**< 左右均为闭区间 */
void build(long long p, long long l, long long r) {
    add[p] = 0;
    if (l == r) {
        ans[p] = 0;
        return;
    }
    long long mid = (l + r) >> 1;
    build(lchild(p), l, mid);
    build(rchild(p), mid + 1, r);
    push_up(p);
}

inline void f(long long p, long long l, long long r,
              long long cur_add) {
    add[p] = add[p] + cur_add;
    ans[p] = ans[p] + cur_add;
}

inline void push_down(long long p, long long l, long long r) {
    long long mid = (l + r) >> 1;
    f(lchild(p), l, mid, add[p]);
    f(rchild(p), mid + 1, r, add[p]);
    add[p] = 0;
}
/**< 区间赋值操作 */
/**< 区间内元素增加的值 */
inline void update(long long nl, long long nr,   /**< 目标边界 */
                   long long l, long long r, long long p /**< 当前边界和节点 */
) {
    if (nl <= l && r <= nr) {
        ans[p] = (ans[p] + add_num);
        add[p] = (add[p] + add_num);
        return;
    }
    push_down(p, l, r);
    long long mid = (l + r) >> 1;
    if (nl <= mid)
        update(nl, nr, l, mid, lchild(p));
    if (nr > mid)
        update(nl, nr, mid + 1, r, rchild(p));
    push_up(p);
}

/**< 区间查询操作 */
long long query(long long l, long long r, long long p) {
    long long res = 0;
    if (l == r)
        if (ans[p] > 0)
            return l;
        else return -1;
    long long mid = (l + r) >> 1;
    push_down(p, l, r);
    if (ans[rchild(p)] > 0)
        res = query(mid + 1, r, rchild(p));
    else res = query(l, mid, lchild(p));
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
    cin >> n >> m;
    const long long r = 1e6 + 5;
    build(1, 1, r);

    for (long long i = 1; i <= n; i++) {
        cin >> price[i];
        add_num = 1;
        update(1, price[i], 1, r, 1);
    }
    for (long long i = 1; i <= m; i++) {
        cin >> money[i];
        add_num = -1;
        update(1, money[i], 1, r, 1);
    }

    cin >> q;

    for (long long i = 1; i <= q; i++) {
        long long u, v, x;
        cin >> u >> v >> x;
        if (u == 1) {
            add_num = -1;
            update(1, price[v], 1, r, 1);
            add_num = 1, price[v] = x;
            update(1, price[v], 1, r, 1);
        } else {
            add_num = 1;
            update(1, money[v], 1, r, 1);
            add_num = -1, money[v] = x;
            update(1, money[v], 1, r, 1);
        }
        cout << query(1, r, 1) << '\n';
    }


#ifndef ONLINE_JUDGE
    auto
            end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}