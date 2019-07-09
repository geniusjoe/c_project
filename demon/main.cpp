#include<bits/stdc++.h>
#define local
#define debu
using namespace std;

#define MAXM    500000+5

const int MAXN = 500025;
const int M = MAXN * 50;

struct Edge {
    /**< 树链剖分 */
    int to, next;
} edge[MAXN * 2];
int head[MAXN], TOT;
int top[MAXN];
int fa[MAXN];
int deep[MAXN];
int num[MAXN];
int p[MAXN];
int fp[MAXN];
int son[MAXN];
int pos;

int n, q, m, tot;
long long add[MAXN << 2], ans[MAXN << 2];
int a[MAXN], t[MAXN], raw_cor[MAXN];
int l_cor[M], r_cor[M];

/**< 树链剖分 */
void addedge(int u, int v) {
    edge[TOT].to = v;
    edge[TOT].next = head[u];
    head[u] = TOT++;
}
void dfs1(int u, int pre, int d) {
    deep[u] = d;
    fa[u] = pre;
    num[u] = 1;
    for(int i = head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].to;
        if(v != pre) {
            dfs1(v, u, d + 1);
            num[u] += num[v];
            if(son[u] == -1 || num[v] > num[son[u]])
                son[u] = v;
        }
    }
}
void getpos(int u, int sp) {
    top[u] = sp;
    p[u] = pos++;
    fp[p[u]] = u;
    if(son[u] == -1)
        return ;
    getpos(son[u], sp);
    for(int i = head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].to;
        if(v != son[u] && v != fa[u])
            getpos(v, v);
    }
}

inline long long lchild(long long x)
/**<  每个树节点的编号*/{
    return x << 1;
}
inline long long rchild(long long x) {
    return x << 1 | 1;
}
inline void push_up(long long p) {
    ans[p] = (ans[lchild(p)] + ans[rchild(p)]);
    l_cor[p] = l_cor[lchild(p)];
    r_cor[p] = r_cor[rchild(p)];
    add[p] = 0;
    if(r_cor[lchild(p)] == l_cor[rchild(p)])
        ans[p]--;
}


inline void f(long long p, long long l, long long r,
              long long cor) {
    if(cor > 0) {
        add[p] = cor;
        l_cor[p]=cor;
        r_cor[p]=cor;
        ans[p] = 1;
    }
}
inline void push_down(long long p, long long l, long long r) {
    long long mid = (l + r) >> 1;
    f(lchild(p), l, mid, add[p]);
    f(rchild(p), mid + 1, r, add[p]);
    add[p] = 0;
}
/**< 区间赋值操作 */
/**< 区间内元素增加的值 */
inline void update(long long nl, long long nr,  /**< 目标边界 */
                   long long l, long long r, long long p, int cor /**< 当前边界和节点 */
                  ) {
    if(nl <= l && r <= nr) {
        ans[p] = 1;
        add[p] = cor;
        l_cor[p] = cor;
        r_cor[p] = cor;
        return ;
    }
    push_down(p, l, r);
    long long mid = (l + r) >> 1;
    if(nl <= mid)
        update(nl, nr, l, mid, lchild(p), cor);
    if(nr > mid)
        update(nl, nr, mid + 1, r, rchild(p), cor);
    push_up(p);
}
/**< 区间查询操作 */
long long query(long long q_x, long long q_y, long long l, long long r, long long p, int &left_color,int & right_color) {
    long long res = 0;
    if(q_x <= l && r <= q_y){
        if(q_x==l)  left_color=l_cor[p];
        if(q_y==r)  right_color=r_cor[p];
        return ans[p];
    }
    long long mid = (l + r) >> 1;
    push_down(p, l, r);
    if(q_x <= mid)
        res += query(q_x, q_y, l, mid, lchild(p),left_color,right_color);
    if(q_y > mid)
        res += query(q_x, q_y, mid + 1, r, rchild(p),left_color,right_color);
    if(q_x<=mid&&q_y>mid){
        if(r_cor[lchild(p)]==l_cor[rchild(p)])
            res--;
    }
    return res;
}
int find(int u, int v, int type, int cor) { /**< 0 表示求和,1表示替换 */
    int f1 = top[u], f2 = top[v];
    int tmp0 = 0;
    int u_lc=-1,u_rc=-1;
    int last_u=-2,last_v=-2;
    while(f1 != f2) {
        if(deep[f1] < deep[f2]) {
            swap(f1, f2);
            swap(u, v);
            swap(last_u,last_v);
        }
        if(type == 0) {
            tmp0 += query( p[f1], p[u], 0, pos - 1, 1,u_lc,u_rc);
            if(last_u==u_rc)
                tmp0--;
            last_u=u_lc;
        } else {
            update(p[f1], p[u], 0, pos - 1, 1, cor);
        }

        u = fa[f1];
        f1 = top[u];
    }
    if(deep[u] > deep[v]){
        swap(u, v);
        swap(last_u,last_v);
    }
    if(type == 0) {
        int tmp1,tmp2;
        tmp0 += query(p[u], p[v], 0, pos - 1, 1,tmp1,tmp2);
        if(last_u==tmp1)    tmp0--;
        if(last_v==tmp2)    tmp0--;
        return tmp0;
    } else {
        update(p[u], p[v], 0, pos - 1, 1, cor);
    }

}
void init() {
    TOT = tot = 0;
    memset(head, -1, sizeof(head));
    pos = 0;
    memset(son, -1, sizeof(son));

    cin >> n >> m;

    for(int i = 1; i <= n; i++) {
        cin >> raw_cor[i];
    }

    for(int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        addedge(u, v);
        addedge(v, u);
    }

    dfs1(1, 0, 0);
    getpos(1, 1);

    for(int i = 0; i < n; i++) {
        update(i, i, 0, n - 1, 1, raw_cor[fp[i]]);
    }
}


void work1() {
    for(int i = 1; i <= m; i++) {
        char op;
        int tmp0, tmp1, tmp2;
        cin >> op;
        if(op == 'Q') {
            cin >> tmp0 >> tmp1;
            cout << find(tmp0, tmp1, 0, 0) << endl;
            continue;
        } else {
            cin >> tmp0 >> tmp1 >> tmp2;
            find(tmp0, tmp1, 1, tmp2);
            continue;
        }
    }
}

int main() {

#ifdef local
    freopen("testdata.in", "r+", stdin);
    freopen("testdata.out", "w+", stdout);
#endif // local

    //ios::sync_with_stdio(false);

    init();

    work1();

}
