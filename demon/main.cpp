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
int bottom[MAXN];
int pos;

int n, q, m, tot;
long long add[MAXN << 2], ans[MAXN << 2];
int a[MAXN], t[MAXN], raw_cor[MAXN];

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
    if(son[u] == -1) {
        bottom[p[u]] = pos - 1;
        return ;
    }

    getpos(son[u], sp);
    for(int i = head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].to;
        if(v != son[u] && v != fa[u])
            getpos(v, v);
    }

    bottom[p[u]] = pos - 1;
}

inline long long lchild(long long x)
/**<  每个树节点的编号*/{
    return x << 1;
}
inline long long rchild(long long x) {
    return x << 1 | 1;
}
inline void push_up(long long p) {
    ans[p] = ans[lchild(p)] + ans[rchild(p)];
    add[p] = 0;
}


inline void f(long long p, long long l, long long r,
              long long cor) {
    /**< 1代表安装，2代表卸载 */
    add[p] += cor;
    ans[p] += (r - l + 1) * cor;

}
inline void push_down(long long p, long long l, long long r) {
    long long mid = (l + r) >> 1;
    f(lchild(p), l, mid, add[p]);
    f(rchild(p), mid + 1, r, add[p]);
    add[p] = 0;
}

inline void update(long long nl, long long nr,
                   long long l, long long r, int p, int cor
                  ) {
    if(nl <= l && r <= nr) {
        ans[p] += (r - l + 1) * cor;
        add[p] += cor;
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
long long query(long long q_x, long long q_y, long long l, long long r, long long p) {
    long long res = 0;
    if(q_x <= l && r <= q_y) {
        return ans[p];
    }
    long long mid = (l + r) >> 1;
    push_down(p, l, r);
    if(q_x <= mid)
        res += query(q_x, q_y, l, mid, lchild(p));
    if(q_y > mid)
        res += query(q_x, q_y, mid + 1, r, rchild(p));

    return res;
}
void find(int u, int v, int type, int cor) {    /**< type==0 表示安装,type==1 表示卸载 */
    if(type == 1) {
        u = bottom[p[v]];
        update(p[v], u, 0, pos - 1, 1, cor);
        return ;
    }
    int f1 = top[u], f2 = top[v];
    int tmp0 = 0;
    while(f1 != f2) {
        if(deep[f1] < deep[f2]) {
            swap(f1, f2);
            swap(u, v);
        }
        tmp0 +=query( p[f1], p[u], 0, pos - 1, 1);
        u = fa[f1];
        f1 = top[u];
    }
    if(deep[u] > deep[v]) {
        swap(u, v);
    }

    tmp0 +=query(p[u], p[v], 0, pos - 1, 1);

    cout << tmp0 << endl;
    return ;
}
void init() {
    TOT = tot = 0;
    memset(head, -1, sizeof(head));
    pos = 0;
    memset(son, -1, sizeof(son));

    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        cin >> raw_cor[i];

    for(int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        addedge(u, v);
        addedge(v, u);
    }

    dfs1(1, 0, 0);
    getpos(1, 1);

    for(int i = 1; i <= n; i++) {
        update(p[i], p[i], 0, pos - 1, 1, raw_cor[i]);
    }

}


void work1() {
    for(int i = 1; i <= m; i++) {
        int op;
        int buf, cur_cor;
        scanf("%d%d", &op, &buf);
        if(op == 1) {
            cin >> cur_cor;
            update(p[buf], p[buf], 0, pos - 1, 1,cur_cor);
            continue;
        } else if(op == 2) {
            cin >> cur_cor;
            find(1, buf, 1,cur_cor);
            continue;
        }
        else {
            find(1, buf, 2,0);
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
