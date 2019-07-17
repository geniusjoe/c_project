#include<bits/stdc++.h>
#define local
#define debu
using namespace std;

template<class T>
inline bool scand_d(T&ret) {
    char c;
    int sgn;
    if(c=getchar(),c==EOF)
        return 0;
    while(c!='-'&&(c<'0'||c>'9'))
        c=getchar();
    sgn=(c=='-')?-1:1;
    ret=(c=='-')?0:(c-'0');
    while(c=getchar(),c>='0'&&c<='9')
        ret=ret*10+(c-'0');
    ret*=sgn;
    return 1;
}

inline void out(int x) {
    if(x>9)
        out(x/10);
    putchar(x%10+'0');
}

const int MAXN = 60010;
const int M = 2500010;
int n,q,m,tot;
int a[MAXN], t[MAXN];
int T[MAXN], lson[M], rson[M],c[M];
int S[MAXN];
int max_val;

struct Query {
    int kind;
    int l,r,k;
} query[10010];

void Init_hash(int k) {
    sort(t,t+k);
    n = unique(t,t+k) - t;
}
int Hash(int x) {
    return lower_bound(t,t+m,x)-t+1;
}

int build(int l,int r) {
    int root = tot++;
    c[root] = 0;
    if(l != r) {
        int mid = (l+r)/2;
        lson[root] = build(l,mid);
        rson[root] = build(mid+1,r);
    }
    return root;
}
int Insert(int root,int pos,int val) {
    int newroot = tot++, tmp = newroot;
    int l = 1, r = max_val;
    c[newroot] = c[root] + val;
    while(l < r) {
        int mid = (l+r)>>1;
        if(pos <= mid) {
            lson[newroot] = tot++;
            rson[newroot] = rson[root];
            newroot = lson[newroot];
            root = lson[root];
            r = mid;
        } else {
            rson[newroot] = tot++;
            lson[newroot] = lson[root];
            newroot = rson[newroot];
            root = rson[root];
            l = mid+1;
        }
        c[newroot] = c[root] + val;
    }
    return tmp;
}
int lowbit(int x) {
    return x&(-x);
}
int use[MAXN];
void add(int x,int pos,int val) {
    while(x <= n) {
        S[x] = Insert(S[x],pos,val);
        x += lowbit(x);
    }
}
int sum(int x) {
    int ret = 0;
    while(x > 0) {
        ret += c[lson[use[x]]];
        x -= lowbit(x);
    }
    return ret;
}
int Query(int right,int k) {
    int l = 1, r = max_val;
    for(int i = right; i ; i -= lowbit(i))
        use[i] = S[i];
    while(l < r) {
        int mid = (l+r)/2;
        int tmp = sum(right) ;
        if(tmp >= k) {
            r = mid;
            for(int i = right; i; i -= lowbit(i))
                use[i] = lson[use[i]];
        } else {
            l = mid+1;
            k -= tmp;
            for(int i = right; i ; i -= lowbit(i))
                use[i] = rson[use[i]];
        }
    }
    return l;
}
void Modify(int x,int p,int d) {
    while(x <= n) {
        S[x] = Insert(S[x],p,d);
        x += lowbit(x);
    }
}
int main() {

#ifdef local
    freopen("testdata.in","r+",stdin);
    freopen("testdata.out","w+",stdout);
#endif // local

    int Tcase;
    scand_d(Tcase);
    for(int k=1; k<=Tcase; k++) {
        printf("Case ");
        out(k);
        printf(":\n");
        scand_d(q);
        int type;
        for(int i = 0; i < q; i++) {
            scand_d(type);
            if(type==1) {
                query[i].kind = 1;
                scand_d(query[i].l),scand_d(query[i].k),scand_d(query[i].r);
                query[i].r++;
                t[m++]=query[i].l;
                t[m++]=query[i].r;
                max_val=max(query[i].k,max_val);
            } else {
                query[i].kind = 2;
                scand_d(query[i].l),scand_d(query[i].k);
                t[m++] = query[i].l;
                max_val=max(query[i].k,max_val);
            }
        }
        Init_hash(m);
        T[0] = build(1,max_val);

        for(int i = 1;i <= n;i++)
            S[i] = T[0];

        for(int i = 0; i < q; i++) {
            if(query[i].kind == 2) {
                int cur_res=Query(Hash(query[i].l),query[i].k);
                out(cur_res);
                printf("\n");
            } else {
                Modify(Hash(query[i].l),query[i].k,1);
                Modify(Hash(query[i].r),query[i].k,-1);
            }
        }
    }
    return 0;
}
