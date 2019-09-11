#include<bits/stdc++.h>

using namespace std;

const long long MAXN = 200050;
const long long INF = 0x7f3f3f3f;
const long long LINF = 0x1f3f3f3f3f3f3f3f;
const long long MOD = 998244853;
const long long OVER_FLOW = 0xffffffff;

long long n, m; /**< n个数,m个操作,以model为模 */
long long a[MAXN], ans[MAXN << 2];
long long add[MAXN << 2]; /**< add 代表加的add,mul代表乘的add */

long long res[MAXN];

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
    add[p] = 0;
    if (l == r) {
        ans[p] = a[l];
        add[p] = 0;
        return;
    }
    long long mid = (l + r) >> 1;
    build(lchild(p), l, mid);
    build(rchild(p), mid + 1, r);
    push_up(p);
}

inline void f(long long p, long long l, long long r,
              long long cur_add) {
    add[p] += cur_add;
    ans[p] += cur_add;
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
                   long long l, long long r, long long p, long long add_num /**< 当前边界和节点 */
) {
    if (nl <= l && r <= nr) {
        ans[p] += add_num;
        add[p] += add_num;
        return;
    }
    push_down(p, l, r);
    long long mid = (l + r) >> 1;
    if (nl <= mid)
        update(nl, nr, l, mid, lchild(p), add_num);
    if (nr > mid)
        update(nl, nr, mid + 1, r, rchild(p), add_num);
    push_up(p);
}

/**< 区间查询操作 */
long long query(long long l, long long r, long long p) {
    long long res = 0;
    if (l == r) {
        ans[p] = LINF;
        return l;
    }
    long long mid = (l + r) >> 1;
    push_down(p, l, r);
    if (ans[p] == ans[rchild(p)])
        res = query(mid + 1, r, rchild(p));
    else
        res = query(l, mid, lchild(p));
    push_up(p);
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
*/

    ios::sync_with_stdio(false);
    cin >> n;
    for (long long i = 1; i <= n; i++) cin >> a[i];
    build(1, 1, n);
    for (long long i = 1; i <= n; i++) {
        long long cur = query(1, n, 1);
        res[cur] = i;
        if (cur < n) {
            update(cur + 1, n, 1, n, 1, -i);
        }
    }
    for (long long i = 1; i <= n; i++) {
        cout << res[i] << " ";
    }
    cout << endl;


#ifndef ONLINE_JUDGE
    auto end_time = clock();
    cerr << "Execution time: " << (end_time - start_time) * (int) 1e3 / CLOCKS_PER_SEC << " ms\n";
#endif

    return 0;

}