#include<bits/stdc++.h>
#define local
#define debu
using namespace std;

template<class T>
inline bool scand_d(T&ret) {
    char c;
    int sgn;
    if(c = getchar(), c == EOF)
        return 0;
    while(c != '-' && (c < '0' || c > '9'))
        c = getchar();
    sgn = (c == '-') ? -1 : 1;
    ret = (c == '-') ? 0 : (c - '0');
    while(c = getchar(), c >= '0' && c <= '9')
        ret = ret * 10 + (c - '0');
    ret *= sgn;
    return 1;
}

inline void out(int x) {
    if(x > 9)
        out(x / 10);
    putchar(x % 10 + '0');
}

const int M = 400100;
int n, q, m, tot, num_tme;
int a[M], t[M], T[M];
int lson[M], rson[M], c[M],ans[M];
int x,x0,n_ans;

struct Query {
    int kind, date, val,id;
    bool operator<(Query query1) {
        if(this->date != query1.date)
            return this->date < query1.date;
        else
            return this->kind < query1.kind;
    }
} query[M];

void Init_hash(int k) {
    sort(t+1, t+1 + k);
    x0 = unique(t+1, t+1 + k) - (t+1);
}
int Hash(int x) {
    return lower_bound(t+1, t+1 + x0, x) - t;
}

int build(int l, int r) {
    int root = tot++;
    c[root] = 0;
    if(l != r) {
        int mid = (l + r) / 2;
        lson[root] = build(l, mid);
        rson[root] = build(mid + 1, r);
    }
    return root;
}
void Insert(int root, int pos, int val) {
    int l = 1, r = x0;
    c[root] += val;
    while(l < r) {
        int mid = (l + r) >> 1;
        if(pos <= mid) {
            root = lson[root];
            r = mid;
        } else {
            root = rson[root];
            l = mid + 1;
        }
        c[root] += val;
    }
}
int Query(int root, int k) {
    int l = 1, r = x0;
    if(c[root] < k)
        return -1;
    while(l < r) {
        int mid = (l + r) / 2;
        int tmp = c[lson[root]] ;
        if(tmp >= k) {
            r = mid;
            root = lson[root];
        } else {
            l = mid + 1;
            k -= tmp;
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

    int Tcase;
    scand_d(Tcase);
    for(int k = 1; k <= Tcase; k++) {
        tot = 0, m = 0,x=0,n_ans=0;
        printf("Case ");
        out(k);
        printf(":\n");
        scand_d(q);
        int type;
        for(int i = 0; i < q; i++) {
            scand_d(type);
            if(type == 1) {
                int cur_start, cur_end, cur_val;
                scand_d(cur_start), scand_d(cur_val), scand_d(cur_end);
                query[++m].date = cur_start, query[m].kind = 1, query[m].val = cur_val;
                query[++m].date = cur_end + 1, query[m].kind = 2, query[m].val = cur_val;
                t[++x]=cur_val;
            } else {
                query[++m].kind = 3;
                query[m].id=++n_ans;
                scand_d(query[m].date), scand_d(query[m].val);
            }
        }
        Init_hash(x);
        T[0] = build(1, x0);
        sort(query + 1, query + 1 + m);

        for(int i = 1; i <= m; i++) {
            if(query[i].kind == 1) {
                Insert(T[0], Hash(query[i].val), 1);
            } else if(query[i].kind == 2) {
                Insert(T[0], Hash(query[i].val), -1);
            } else {
                int cur_res = Query(T[0], Hash(query[i].val));
                ans[query[i].id]=cur_res;
            }
        }

        for(int i=1; i<=n_ans; i++) {
            if(ans[i] < 0) {
                printf("-1\n");
            } else {
                out(t[ans[i]]);
                printf("\n");
            }
        }
    }
    return 0;
}
