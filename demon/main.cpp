#include<bits/stdc++.h>
#define local
#define debu
using namespace std;

const int MAXN = 200010;
const int M = MAXN * 80;
int n, q,m, tot;
int a[MAXN], t[MAXN];
int lson[M], rson[M], c[M];
int T[MAXN],tme_buf[MAXN];

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

int q_cnt, tme_cnt;
struct timing {
    int type,date,val;
    bool operator <(timing time1) {
        return this->date<time1.date;
    }
} times[MAXN];

struct que {
    int q_time, k;
} ques[MAXN];

void init() {
    int cur_num;
    tme_cnt=q_cnt=0;
    scand_d(cur_num);
    for(int i=1; i<=cur_num; i++) {
        int cur_type;
        scand_d(cur_type);
        if(cur_type == 1) {
            int start, finish, val;
            scand_d(start),scand_d(val),scand_d(finish);
            times[++tme_cnt].date = start;
            times[tme_cnt].type = 1;
            times[tme_cnt].val = val;
            times[++tme_cnt].date = finish + 1;
            times[tme_cnt].type = 2;
            times[tme_cnt].val = val;
        } else {
            int cur_time, cur_k;
            scand_d(cur_time),scand_d(cur_k);
            ques[++q_cnt].q_time = cur_time;
            ques[q_cnt].k = cur_k;
            times[++tme_cnt].date = cur_time;
            times[tme_cnt].type = 3;
        }
    }
    sort(times + 1, times + 1 + tme_cnt);
    for(int i=1; i<=tme_cnt; i++)
        tme_buf[i]=times[i].date;
    m = unique(tme_buf+1,tme_buf+1+tme_cnt)-tme_buf-1;

}

int build(int l, int r) {
    int root = tot++;
    c[root] = 0;
    if(l != r) {
        int mid = (l + r) >> 1;
        lson[root] = build(l, mid);
        rson[root] = build(mid + 1, r);
    }
    return root;
}
int Hash(int x) {
    return lower_bound(tme_buf + 1, tme_buf + 1 + tme_cnt, x) - tme_buf;
}
int update(int root, int pos, int val) {
    int newroot = tot++, tmp = newroot;
    c[newroot] = c[root] + val;
    int l = 1, r = m;
    while(l < r) {
        int mid = (l + r) >> 1;
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
            l = mid + 1;
        }
        c[newroot] = c[root] + val;
    }
    return tmp;
}
int query(int root, int k) {
    int l = 1, r = m;
    if(c[root]<k)
        return -1;
    while(l < r) {
        int mid = (l + r) >> 1;
        if(c[lson[root]] >= k ) {
            r = mid;
            root = lson[root];
        } else {
            l = mid + 1;
            k -= c[lson[root]];
            root = rson[root];
        }
    }
    return l;
}
int main() {
#ifdef local
    freopen("testdata.in", "r+", stdin);
    freopen("testdata.out", "w+", stdout);
#endif // local

    ios::sync_with_stdio(false);


    int k;
    scand_d(k);
    for(int ii=1; ii<=k; ii++) {
        printf("Case ");
        out(ii);
        printf(":\n");
        tot=0;
        init();
        int cnt1=1;

        T[0]=build(1,1000000+5);

        for(int i = 1; i <=m; i++) {
            T[i]=T[i-1];
            while(Hash(times[cnt1].date)==i) {
                if(times[cnt1].type==1)
                    T[i]=update(T[i],times[cnt1].val,1);
                else if(times[cnt1].type==2)
                    T[i]=update(T[i],times[cnt1].val,-1);
                cnt1++;
            }
        }

        for(int i=1; i<=q_cnt; i++) {
            int num=Hash(ques[i].q_time);
            int cur_res=query(T[num],ques[i].k);
            if(cur_res<0) {
                putchar('-');
                cur_res=abs(cur_res);
            }
            out(cur_res);
            printf("\n");
        }
    }

    return 0;
}






const int MAXN = 60010;
const int M = 2500010;
int n,q,m,tot;
int a[MAXN], t[MAXN];
int T[MAXN], lson[M], rson[M],c[M];
int S[MAXN];
struct Query {
    int kind;
    int l,r,k;
} query[10010];

void Init_hash(int k) {
    sort(t,t+k);
    m = unique(t,t+k) - t;
}
int hash(int x) {
    return lower_bound(t,t+m,x)-t;
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
    int l = 0, r = m-1;
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
int Query(int left,int right,int k) {
    int left_root = T[left-1];
    int right_root = T[right];
    int l = 0, r = m-1;
    for(int i = left-1; i; i -= lowbit(i))
        use[i] = S[i];
    for(int i = right; i ; i -= lowbit(i))
        use[i] = S[i];
    while(l < r) {
        int mid = (l+r)/2;
        int tmp = sum(right) - sum(left-1) + c[lson[right_root]] -c[lson[left_root]];
        if(tmp >= k) {
            r = mid;
            for(int i = left-1; i ; i -= lowbit(i))
                use[i] = lson[use[i]];
            for(int i = right; i; i -= lowbit(i))
                use[i] = lson[use[i]];
            left_root = lson[left_root];
            right_root = lson[right_root];
        } else {
            l = mid+1;
            k -= tmp;
            for(int i = left-1; i; i -= lowbit(i))
                use[i] = rson[use[i]];
            for(int i = right; i ; i -= lowbit(i))
                use[i] = rson[use[i]];
            left_root = rson[left_root];
            right_root = rson[right_root];
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
    int Tcase;
    scanf("%d",&Tcase);
    while(Tcase--) {
        scanf("%d%d",&n,&q);
        tot = 0;
        m = 0;
        for(int i = 1; i <= n; i++) {
            scanf("%d",&a[i]);
            t[m++] = a[i];
        }
        char op[10];
        for(int i = 0; i < q; i++) {
            scanf("%s",op);
            if(op[0] == 'Q') {
                query[i].kind = 0;
                scanf("%d%d%d",&query[i].l,&query[i].r,&query[i].k);
            } else {
                query[i].kind = 1;
                scanf("%d%d",&query[i].l,&query[i].r);
                t[m++] = query[i].r;
            }
        }
        Init_hash(m);
        T[0] = build(0,m-1);
        for(int i = 1; i <= n; i++)
            T[i] = Insert(T[i-1],hash(a[i]),1);
        for(int i = 1; i <= n; i++)
            S[i] = T[0];
        for(int i = 0; i < q; i++) {
            if(query[i].kind == 0)
                printf("%d\n",t[Query(query[i].l,query[i].r,query[i].k)]);
            else {
                Modify(query[i].l,hash(a[query[i].l]),-1);
                Modify(query[i].l,hash(query[i].r),1);
                a[query[i].l] = query[i].r;
            }
        }
    }
    return 0;
}
