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

const int MAXN = 200100;
const int M = 15600010;
int n, q, m, tot, num_tme;
int a[MAXN], t[MAXN], T[MAXN];
int lson[M], rson[M], c[M];
int max_val;

struct Query {
    int kind, date, val;
    bool operator<(Query query1) {
        if(this->date != query1.date)
            return this->date < query1.date;
        else
            return this->kind > query1.kind;
    }
} query[100100];

void Init_hash(int k) {
    sort(t, t + k);
    n = unique(t, t + k) - t;
}
int Hash(int x) {
    return lower_bound(t, t + m, x) - t + 1;
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
    int l = 1, r = max_val;
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
    int l = 1, r = max_val;
    if(c[root] < k)
        return -1;
    while(l < r) {
        int mid = (l + r) / 2;
        int tmp = c[root] ;
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
        tot = 0, m = 0;
        printf("Case ");
        out(k);
        printf(":\n");
        scand_d(q);
        int type;
        for(int i = 0; i < q; i++) {
            scand_d(type);
            if(type == 1) {
                int cur_start, cur_end, cur_val;
                scand_d(cur_start), scand_d(cur_end), scand_d(cur_val);
                query[++m].date = cur_start, query[m].kind = 3, query[m].val = cur_val;
                query[++m].date = cur_end + 1, query[m].kind = 2, query[m].val = cur_val;
                //t[++num_tme] = cur_start, t[++num_tme] = cur_end;
                max_val = max(cur_val, max_val);
            } else {
                query[++m].kind = 1;
                scand_d(query[m].date), scand_d(query[m].val);
                max_val = max(max_val, query[m].val);
                //t[++num_tme] = query[m].date;
            }
        }
        //Init_hash(num_tme);
        T[0] = build(1, max_val);
        sort(query + 1, query + 1 + m);

        for(int i = 1; i <= m; i++) {
            if(query[i].kind == 3) {
                Insert(T[0], query[i].val, 1);
            } else if(query[i].kind == 2) {
                Insert(T[0], query[i].val, -1);
            } else {
                int cur_res = Query(T[0], query[i].val);
                if(cur_res < 0) {
                    putchar('-');
                    cur_res = abs(cur_res);
                }
                out(cur_res);
                printf("\n");
            }
        }
    }
    return 0;
}
