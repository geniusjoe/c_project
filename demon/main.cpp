#include<bits/stdc++.h>
#define loc
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

/**< 主席树 */
int n, q, m, tot;
int a[MAXN], t[MAXN];
int times[MAXN];
int T[M], lson[M], rson[M], c[M];
int seg_sum[M], seg_max[M];
int city_num, event_num;
int raw_city[MAXN];

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
int build(int l, int r) {
    int root = tot++;
    seg_sum[root] = 0;
    seg_max[root] = 0;
    if(l != r) {
        int mid = (l + r) >> 1;
        lson[root] = build(l, mid);
        rson[root] = build(mid + 1, r);
    }
    return root;
}
void push_up(int i) {
    seg_max[i] = max(seg_max[lson[i]], seg_max[rson[i]]);
    seg_sum[i] = seg_sum[lson[i]] + seg_sum[rson[i]];
}
int update(int l, int r, int root, int pos, int val) {
    int newroot = ++tot;
    int mid = (l + r) >> 1;
    if(l == r) {
        seg_sum[newroot] = seg_sum[root] + val;
        seg_max[newroot] = seg_max[root] + val;
        return newroot;
    }
    if(pos <= mid) {
        lson[newroot] = update(l, mid, lson[root], pos, val);
        rson[newroot] = rson[root];
    } else {
        rson[newroot] = update(mid + 1, r, rson[root], pos, val);
        lson[newroot] = lson[root];
    }
    push_up(newroot);
    return newroot;
}

int query(int l, int r, int x, int y, int root, int type) { /**< type==0 代表最大值， type==1 代表求和 */
    if(l >= x && r <= y) {
        if(type == 0)
            return seg_max[root];
        else
            return seg_sum[root];
    }

    int mid = (l + r) >> 1;
    if(mid >= y)
        return query(l, mid, x, y, lson[root], type);
    else if(mid < x)
        return query(mid + 1, r, x, y, rson[root], type);
    else {
        if(type == 0)
            return max(query(l, mid, x, y, lson[root], type), query(mid + 1, r, x, y, rson[root], type));
        if(type == 1)
            return query(l, mid, x, y, lson[root], type) + query(mid + 1, r, x, y, rson[root], type);
    }
}
int find(int u, int v, int type, int k) { /**< type==0 代表最大值， type==1 代表求和 */
    int f1 = top[u], f2 = top[v];
    int tmp0 = 0,tmp1=-100000;
    while(f1 != f2) {
        if(deep[f1] < deep[f2]) {
            swap(f1, f2);
            swap(u, v);
        }
        if(type == 0)
            tmp1 = max(tmp1, query(0, pos - 1, p[f1], p[u], T[0], type));
        else
            tmp0 += query(0, pos - 1, p[f1], p[u], T[0], type);
        u = fa[f1];
        f1 = top[u];
    }
    if(deep[u] > deep[v])
        swap(u, v);
    if(type == 0)
        return max(tmp1, query(0, pos - 1, p[u], p[v], T[0], type));
    else
        return tmp0 + query(0, pos - 1, p[u], p[v], T[0], type);
}
int e[MAXN];


void init() {
    TOT = tot = 0;
    memset(head, -1, sizeof(head));
    pos = 0;
    memset(son, -1, sizeof(son));

    cin >> city_num;

    for(int i = 1; i <= city_num - 1; i++) {
        int u, v;
        cin >> u >> v;
        addedge(u, v);
        addedge(v, u);
    }

    for(int i=1;i<=city_num;i++)
        cin>>raw_city[i];

    dfs1(1, 0, 0);
    getpos(1, 1);
    T[0] = build(0, pos - 1);

    for(int i=1;i<=city_num;i++)
        T[0]=update(0,pos-1,T[0],p[i],raw_city[i]);

    cin>>event_num;

}


void work1() {
    for(int i = 1; i <= event_num; i++) {
        char s[10];
        int city1, city2;
        scanf("%s%d%d",s,&city1,&city2);
        if(s[1]=='S') {
            cout << find(city1, city2, 1, city1) << endl;
            continue;
        } else if(s[1]=='M') {
            cout << find(city1, city2, 0, city1) << endl;
            continue;
        } else if(s[1]=='H') {
            int tmp=raw_city[city1];
            raw_city[city1] = city2;
            T[0] = update(0, pos - 1, T[0], p[city1], -tmp + raw_city[city1]);
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
