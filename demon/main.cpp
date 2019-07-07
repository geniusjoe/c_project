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

int n, q, m, tot;
int a[MAXN], t[MAXN];
int times[MAXN];
int seg_sum[M];
int l_cor[M],r_cor[M];
int cor_cnt=10000000;

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


using namespace std;
long long n,m; /**< n个数,m个操作,以model为模 */
long long a[MAXN],ans[MAXN<<2];
long long add[MAXN<<2]; /**< add 代表加的add,mul代表乘的add */
long long add_num; /**< 每个操作的操作数 */
long long opt_type;
inline long long lchild(long long x)
/**<  每个树节点的编号*/
{
    return x<<1;
}
inline long long rchild(long long x) {
    return x<<1|1;
}
inline void push_up(long long p) {
    ans[p]=(ans[lchild(p)]+ans[rchild(p)]);
    l_cor[p]=l_cor[lchild(p)];
    r_cor[p]=r_cor[rchild(p)];
    add[p]=0;
    if(r_cor[lchild(p)]==l_cor[rchild(p)])  ans[p]--;
}

/**< 由顶向下建立线段树 */
/**< 左右均为闭区间 */
void build(long long p,long long l,long long r,int val) {
    add[p]=0;
    if(l==r) {
        ans[p]=1;
        l_cor[p]=val;
        r_cor[p]=val;
        return ;
    }
    long long mid=(l+r)>>1;
    build(lchild(p),l,mid,val);
    build(rchild(p),mid+1,r,val);
    push_up(p);
}
inline void f(long long p,long long l,long long r,
              long long cor) {
    if(cor>0){
        add[p]=cor;
        ans[p]=1;
    }
}
inline void push_down(long long p,long long l,long long r) {
    long long mid=(l+r)>>1;
    f(lchild(p),l,mid,add[p]);
    f(rchild(p),mid+1,r,add[p]);
    add[p]=0;
}
/**< 区间赋值操作 */
/**< 区间内元素增加的值 */
inline void update(long long nl,long long nr,   /**< 目标边界 */
                   long long l,long long r,long long p,int val /**< 当前边界和节点 */
                  ) {
    if(nl<=l&&r<=nr) {
        ans[p]=1;
        add[p]=val;
        l_cor[p]=val;
        r_cor[p]=val;
        return ;
    }
    push_down(p,l,r);
    long long mid=(l+r)>>1;
    if(nl<=mid)
        update(nl,nr,l,mid,lchild(p),val);
    if(nr>mid)
        update(nl,nr,mid+1,r,rchild(p),val);
    push_up(p);
}
/**< 区间查询操作 */
long long query(long long q_x,long long q_y,long long l,long long r,long long p) {
    long long res=0;
    if(q_x<=l&&r<=q_y)
        return ans[p];
    long long mid=(l+r)>>1;
    push_down(p,l,r);
    if(q_x<=mid)
        res+=query(q_x,q_y,l,mid,lchild(p));
    if(q_y>mid)
        res+=query(q_x,q_y,mid+1,r,rchild(p));
    return res;
}
int find(int u, int v, int k) {
    int f1 = top[u], f2 = top[v];
    int tmp0 = 0;
    while(f1 != f2) {
        if(deep[f1] < deep[f2]) {
            swap(f1, f2);
            swap(u, v);
        }
        tmp0 += query(0, pos - 1, p[f1], p[u], T[0], type);
        u = fa[f1];
        f1 = top[u];
    }
    if(deep[u] > deep[v])
        swap(u, v);
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
